#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/char.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <regex>
#include <experimental/filesystem>

namespace{

        namespace fs = std::experimental::filesystem;

        namespace s_tree{

                struct node{

                        struct visitor;
                        struct sorter;
                        struct pruner;

                        explicit node(const fs::path& p):path_(p){}
                        virtual ~node()=default;
                        virtual void accept(visitor&)=0;
                        virtual void bu_accept(visitor&)=0;

                        virtual void sort( sorter& ){}
                        virtual void prune(pruner& ){}
                        virtual bool apply( pruner&)const=0;

                        virtual void stream(std::ostream& ostr)const=0;

                        std::shared_ptr<void>& data(){return data_;}

                        // want to way to pripriotize directory when sorting
                        virtual size_t sort_order()const=0;

                        template<typename T>
                        T& data_as(){
                                assert( data_ && "dereferincing null");
                                return *reinterpret_cast<T*>(data_.get());
                        }
                        template<typename T>
                        const T& data_as()const{
                                assert( data_ && "dereferincing null");
                                return *reinterpret_cast<const T*>(data_.get());
                        }

                        const fs::path& path()const{return path_;}
                private:
                        fs::path path_;
                        std::shared_ptr<void> data_;
                };

                struct file_node;
                struct directory_node;

                struct node::visitor{
                        using file_node = ::s_tree::file_node;
                        using directory_node = ::s_tree::directory_node;

                        virtual ~visitor()=default;


                        virtual void operator()(file_node&){}
                        virtual void operator()(directory_node&){}

                        virtual void begin_children(){};
                        virtual void begin_children_size(size_t n){};
                        virtual void next_child(){};
                        virtual void end_children(){};
                };

                struct node::sorter{
                        using node = ::s_tree::node;

                        virtual ~sorter()=default;

                        virtual bool operator()( 
                                std::shared_ptr<node> left, 
                                std::shared_ptr<node> right)=0;
                };
                struct node::pruner{
                        using file_node = ::s_tree::file_node;
                        using directory_node = ::s_tree::directory_node;

                        virtual ~pruner()=default;


                        // returns true to indicate to prune 
                        virtual bool operator()(const file_node&){return false;}
                        virtual bool operator()(const directory_node&){return false;}
                };
                        

                struct  file_node : public node{
                        file_node(const fs::path& p):node(p){}
                        void accept(visitor& v)final{
                                v(*this);
                        }
                        void bu_accept(visitor& v)final{
                                v(*this);
                        }
                        void stream(std::ostream& ostr)const{
                                ostr << "file_node(" << path().filename().string() << ")";
                        }
                        bool apply( pruner& p)const{
                                return p(*this);
                        }
                        size_t sort_order()const final{return 1;}
                };
                struct  directory_node : public node{
                        directory_node(const fs::path& p):node(p){}
                        void push_child( std::shared_ptr<node> child){
                                children_.push_back( std::move( child ) );
                        }
                        void accept(visitor& v)final{
                                v(*this);
                                v.begin_children();
                                v.begin_children_size(children_.size());
                                for(auto& c : children_ ){
                                        c->accept( v );
                                        v.next_child();
                                }
                                v.end_children();
                        }
                        void bu_accept(visitor& v)final{
                                v.begin_children();
                                v.begin_children_size(children_.size());
                                for(auto& c : children_ ){
                                        c->bu_accept( v );
                                        v.next_child();
                                }
                                v.end_children();
                                v(*this);
                        }
                        void prune( pruner& p)final{
                                std::vector<std::shared_ptr<node> > tmp;
                                for(auto& c : children_ ){
                                        c->prune(p);
                                        if( ! c->apply(p) )
                                                tmp.push_back(c);
                                }
                                children_ = std::move(tmp);
                        }
                        bool apply( pruner& p)const{
                                return p(*this);
                        }
                        void stream(std::ostream& ostr)const{
                                ostr << "directory_node(" << path().filename().string() << ")";
                        }
                        void sort( sorter& s){
                                for( auto& c : children_ )
                                        c->sort( s );

                                using sptr_t = std::shared_ptr<node>;
                                auto aux = [&s](sptr_t l, sptr_t r)->bool{
                                        return s(l,r);
                                };
                                std::sort( children_.rbegin(), children_.rend(), aux );
                        }
                        size_t sort_order()const final{return 0;}
                private:
                        std::vector<std::shared_ptr<node> > children_;
                };

                struct  node_handle{
                        node_handle( std::shared_ptr<node> impl):impl_(std::move(impl)){}
                        void sort(node::sorter& s){
                                impl_->sort( s );
                        }
                        void accept(node::visitor& v){
                                impl_->accept( v );
                        }
                        void bu_accept(node::visitor& v){
                                impl_->bu_accept( v );
                        }
                        void prune(node::pruner& p){
                                impl_->prune(p);
                        }
                private:
                        std::shared_ptr<node> impl_;
                };

                struct tree_maker{
                        using filter_t = std::function<bool(const std::string&)>;

                        tree_maker( filter_t file_filter = [](const std::string&)->bool{return true;})
                                : file_filter_(std::move(file_filter))
                        {}
                        std::shared_ptr<node> make_impl(const fs::directory_entry& de){
                                try{
                                        switch( de.status().type() ){
                                                case fs::file_type::regular:
                                                        if( file_filter_( de.path().string() ) )
                                                                return std::make_shared<file_node>(de.path());
                                                        return std::shared_ptr<node>();
                                                case fs::file_type::directory:
                                                        {
                                                                auto tmp = std::make_shared<directory_node>(de.path());
                                                                for(fs::directory_iterator di(de.path()),de;di!=de;++di){
                                                                        if( auto child_maybe = this->make_impl( *di ) ){
                                                                                tmp->push_child( std::move( child_maybe ) );
                                                                        }
                                                                }
                                                                return tmp;
                                                        }
                                                default:
                                                        break;
                                        }
                                } catch( const std::exception& e){
                                        // ignore it
                                }
                                return std::shared_ptr<node>();
                        }
                        node_handle make(const fs::directory_entry& de){
                                auto tmp = this->make_impl(de);
                                if( ! tmp )
                                        BOOST_THROW_EXCEPTION(std::domain_error("not a valid directory entry"));
                                return tmp;
                        }
                private:
                        size_t count_{0};
                        filter_t file_filter_;
                };

        }
        struct accumulator{
                void operator()(const accumulator& acc){
                        files_ += acc.files_;
                        lines_ += acc.lines_;
                }
                void operator()(size_t n){
                        ++files_;
                        lines_ += n;
                }
                size_t files()const{return files_;}
                size_t lines()const{return lines_;}

                friend std::ostream& operator<<(std::ostream& ostr, const accumulator& acc){
                        return ostr << "{" << acc.files() << "," << acc.lines() << "}"; 
                }
        private:
                size_t files_{0};
                size_t lines_{0};
        };

        /*
         * an attibute is both atomic for a single file,
         * and as some semantics for accumulatings over 
         * other directries and files for directories
         *
         * and attribute can be formatted as a single line or multiple lines
         * 
         * ie can have
         *
         *      123 dir 
         *       \------- 100 filea
         *       \-------  20 fileb
         *       \-------   3 filec
         *
         *       dir 
         *       |   3 - files
         *       |   123 - lines
         *       |
         *       \------- 100 filea
         *       \-------  20 fileb
         *       \-------   3 filec
         
         *       dir 
         *       |   3 - files
         *       |   123 - lines
         *       |
         *       \------- filea
         *       |         100 - lines
         *       |
         *       \------- fileb
         *       |         20 - lines
         *       |
         *       \------- filec
         *                  3 - lines
         *
         *
         *       etc
         *      
         *
         *
         */
        namespace attr{
                struct attribute{
                        struct visitor;
                        virtual ~attribute()=default;
                        virtual void apply(visitor&)const=0;
                };
                struct attribute::visitor{
                        virtual ~visitor()=default;
                        virtual void put_string(const std::string&)=0;
                        virtual void put_lines(const std::vector<std::string>&)=0;
                };
        }


        namespace aux{

                //struct tree_printer{
                        //void push
                //private:
                        //std::vector<std::shared_ptr<child> > stack_;
                //};

                struct pretty_printer : s_tree::node::visitor{

                        struct color_formatter{
                                static std::string color_red(const std::string& s){
                                        return "\033[0;36m" + s + "\033[0;m";
                                }
                                static std::string color_purple(const std::string& s){
                                        return "\033[0;35m" + s + "\033[0;m";
                                }
                                static std::string color_blue(const std::string& s){
                                        return "\033[0;34m" + s + "\033[0;m";
                                }
                        };

                        struct runtime_policy{
                                runtime_policy(bool use_color , bool print_files , size_t max_depth  )
                                        : use_color_(use_color)
                                        , print_files_(print_files)
                                        , max_depth_(max_depth)
                                {
                                }
                                std::string format_file(const std::string& s){
                                        if( use_color_ )
                                                return color_formatter::color_red(s);
                                        return s;
                                }
                                std::string format_dir(const std::string& s){
                                        if( use_color_ )
                                                return color_formatter::color_purple(s);
                                        return s;
                                }
                                std::string format_number(const std::string& s){
                                        if( use_color_)
                                                return color_formatter::color_blue(s);
                                        return s;
                                }
                                bool print_files()const{return print_files_;}
                                size_t max_depth()const{return max_depth_;}
                        private:
                                const bool use_color_;
                                const bool print_files_;
                                const size_t max_depth_;
                        };

                        template<typename... Args>
                        pretty_printer(Args&&... args):
                                policy_(std::forward<Args>(args)...)
                        { }
                        ~pretty_printer(){
                        }
                        void put_line_(const std::string& line){
                                if( stack_.size() ){
                                        std::for_each( stack_.begin(), std::prev(stack_.end()),
                                                [this](format_data& fd){
                                                        fd.print(std::cout);
                                        });
                                        stack_.back().print_alt(std::cout);
                                }
                                std::cout << line << "\n";
                        }
                        void operator()( file_node& fn)final{
                                if( stack_.size() > policy_.max_depth() )
                                        return;
                                if( not policy_.print_files())
                                        return;

                                std::stringstream sstr;
                                        
                                auto lines = fn.data_as<accumulator>().lines();
                                sstr << " " << 
                                        policy_.format_number(
                                                boost::lexical_cast<std::string>(
                                                        fn.data_as<accumulator>().lines()))
                                        << " ";
                                sstr << 
                                        policy_.format_file(fn.path().filename().string());

                                put_line_(sstr.str());
                                   
                        }
                        void operator()(directory_node& dn)final{
                                if( not ( stack_.size() > policy_.max_depth() ) ){
                                        auto lines = dn.data_as<accumulator>().lines();
                                        std::stringstream sstr, sstr2;
                                        sstr << " " << dn.data_as<accumulator>().lines() << " ";
                                        size_t size = sstr.str().size();

                                        sstr2 << 
                                                policy_.format_number(sstr.str()) << 
                                                policy_.format_dir(dn.path().filename().string());

                                        put_line_(sstr2.str());
                                        stack_.emplace_back(size);
                                } else{
                                        stack_.emplace_back(0);
                                }
                        }
                        virtual void begin_children_size(size_t n)final{
                                stack_.back().finalize(n);
                        }
                        virtual void end_children()final{
                                stack_.pop_back();
                        }
                        virtual void next_child()final{
                                stack_.back().next();
                        }
                private:

                        struct angle_c_traits{
                                using hor_c = boost::mpl::char_<'_'>;
                                using vert_c = boost::mpl::char_<'|'>;
                                using br_c = boost::mpl::char_<'\\'>;
                        };
                        struct straight_c_traits{
                                using hor_c = boost::mpl::char_<'_'>;
                                using vert_c = boost::mpl::char_<'|'>;
                                using br_c = boost::mpl::char_<'|'>;
                        };
                        
                        using c_traits = angle_c_traits;

                        struct format_data{
                                std::string make_(char c, char a){
                                        std::string tmp;
                                        tmp += std::string((indent_-1)/2,' ');
                                        tmp += c;
                                        tmp += std::string(indent_-tmp.size(),a);
                                        return tmp;
                                }
                                format_data(size_t indent):indent_(indent){
                                        auto sz = indent_;
                                }
                                void finalize(size_t num_children){
                                        num_children_ = num_children;

                                }
                                void print_alt(std::ostream& ostr){
                                        if( indent_ )
                                                ostr << make_(c_traits::br_c(), c_traits::hor_c());
                                }
                                void print(std::ostream& ostr){
                                        if( indent_ ){
                                                if( idx_ != num_children_ -1 ){
                                                        ostr << make_(c_traits::vert_c(), ' ');
                                                } else{
                                                        ostr << std::string(indent_,' ');
                                                }
                                        }
                                }
                                void next(){
                                        ++idx_;
                                        assert( idx_ <= num_children_ );
                                }
                        private:
                                size_t idx_{0}; // child index
                                size_t num_children_; // number of children
                                const size_t indent_; // lengh of indent
                        };
                        std::list<format_data> stack_;
                        runtime_policy policy_;
                };
                struct file_observer{
                        size_t operator()(std::istream& ostr){
                                size_t lines = 0;
                                for(std::string line; std::getline( ostr, line ) ; ++lines);
                                return lines;
                        }
                };
                struct word_count_visitor : s_tree::node::visitor{
                        explicit word_count_visitor(boost::asio::io_service& io)
                                :io_(io)
                        {}

                        void operator()( file_node& fn)final{
                                io_.post([&fn]()mutable{
                                        std::ifstream fstr(fn.path().string());
                                        if( ! fstr.is_open() ){
                                                std::cout << "unable to open " << fn.path().string() << "\n";
                                                return;
                                        }
                                        file_observer fo;
                                        auto asptr = std::make_shared<accumulator>();
                                        asptr->operator()(fo(fstr));
                                        fn.data() = asptr;
                                });
                        }
                private:
                        boost::asio::io_service& io_;
                };
                
                struct tally_visitor : s_tree::node::visitor{
                        explicit tally_visitor(boost::asio::io_service& io):io_(io){
                                begin_children();
                        }
                        void operator()( file_node& fn)final{
                                stack_.back()->operator()( fn.data_as<accumulator>() );
                        }
                        void operator()(directory_node& dn)final{
                                auto aptr = stack_.back();
                                stack_.pop_back();
                                dn.data() = aptr;
                                
                                stack_.back()->operator()( *aptr );
                        }
                        void begin_children()final{
                                stack_.emplace_back(std::make_shared<accumulator>());
                        }
                private:
                        boost::asio::io_service& io_;

                        std::vector<std::shared_ptr<accumulator> > stack_;
                };
                
                struct lines_sorter : s_tree::node::sorter{
                        bool operator()(
                                std::shared_ptr<node> left,
                                std::shared_ptr<node> right)final
                        {
                                // type, lines, name
                                if( left->sort_order() != right->sort_order() )
                                         return left->sort_order() > right->sort_order();
                                if( left->data_as<accumulator>().lines()
                                 != right->data_as<accumulator>().lines() )
                                         return left->data_as<accumulator>().lines() 
                                              < right->data_as<accumulator>().lines() ;
                                return left->path().string() < right->path().string();
                        }
                };
                
                struct empty_pruner : s_tree::node::pruner{
                        bool operator()(const file_node& fn)final{
                                return fn.data_as<accumulator>().lines() == 0;
                        }
                        bool operator()(const directory_node& dn)final{
                                return dn.data_as<accumulator>().lines() == 0;
                        }
                };

#if 0
                struct cout_visitor : s_tree::node::visitor{
                        void operator()( file_node& fn)final{
                                for(size_t i=0;i!=depth_*2;++i)
                                        std::cout << " ";
                                fn.stream(std::cout);
                                //std::cout << " " << fn.data().get();
                                std::cout << " " << *reinterpret_cast<data_type*>(fn.data().get());
                                std::cout << "\n";
                        }
                        void operator()(directory_node& dn)final{
                                //if( depth_ < 3 )
                                {
                                        for(size_t i=0;i!=depth_*2;++i)
                                                std::cout << " ";
                                        dn.stream(std::cout);
                                        //std::cout << " " << dn.data().get();
                                        using data_type = accumulator;
                                        std::cout << " " << *reinterpret_cast<data_type*>(dn.data().get());
                                        std::cout << "\n";
                                }
                        }
                        virtual void begin_children()final{
                                ++depth_;
                        }
                        virtual void end_children()final{
                                --depth_;
                        }
                private:
                        size_t depth_{0};
                };
#endif

        }
}



int main(int argc, char** argv){
        try{

                namespace po = boost::program_options;

                bool help;

                po::options_description desc;
                desc.add_options()
                        ("max-depth",po::value<size_t>()->default_value(-1),"maximum depth")
                        ("color",po::value<bool>()->default_value(false)->implicit_value(true),"coloring policy")
                        ("print-files",po::value<bool>()->default_value(false)->implicit_value(true),"file print policy")
                        ("root",po::value<std::string>()->default_value("."),"root")
                        ("file-regex",po::value<std::string>()->default_value(
                                        R"__(\.(hpp|cpp|h|c|cc|hxx|cxx)$)__"
                                ),"regular expression for files")
                        ("file-black-list-regex",po::value<std::string>()->default_value(
                                        R"__((CMakeFiles))__"
                                ),"regular expression for files")
                        ("help",po::value<bool>(&help)->default_value(false)->implicit_value(true),
                         "print this message")

                        ;

                po::positional_options_description p;
                p.add("root",-1);

                po::variables_map vm;
                po::store( 
                        po::command_line_parser(argc,argv)
                                .options(desc)
                                .positional(p)
                                .run()
                       , vm 
                );

                if( help ){
                        std::cout << desc << "\n";
                        return EXIT_SUCCESS;
                }


                fs::directory_entry head_de( vm["root"].as<std::string>() );


                std::regex file_rgx{vm["file-regex"].as<std::string>()};
                std::regex file_blacklist{vm["file-black-list-regex"].as<std::string>()};

                auto cpp_filter = [&file_rgx, &file_blacklist](const std::string& path)->bool{
                        // blacklist
                        if( std::regex_search( path, file_blacklist)  )
                                return false;
                        return std::regex_search( path, file_rgx );
                };

                auto filter_debugger = [&cpp_filter](const std::string& path)->bool{
                        auto res = cpp_filter(path);
                        std::cout << path << " => " << res << "\n";
                        return res;
                };

                s_tree::tree_maker maker(cpp_filter);
                auto h = maker.make(head_de);
                
                boost::asio::io_service io;

                aux::word_count_visitor wcv(io);
                h.accept(wcv);

                #if 0
                std::vector<std::thread> tg;
                for( size_t i=0;i!=std::thread::hardware_concurrency() * 2 ; ++ i)
                        tg.emplace_back( [&io](){io.run();});
                boost::for_each( tg, std::mem_fn(&std::thread::join));
                #endif
                io.run();
                std::cerr << "done word counting\n";

                aux::tally_visitor tv(io);
                h.bu_accept( tv );
                io.run();
                std::cerr << "done tallying counting\n";

                aux::lines_sorter ls;
                h.sort( ls );

                aux::empty_pruner ep;
                h.prune(  ep );

                aux::pretty_printer pp(
                        vm["color"].as<bool>(),
                        vm["print-files"].as<bool>(),
                        vm["max-depth"].as<size_t>());
                h.accept( pp );


        } catch( const std::exception& e){
                std::cerr 
                        << "Caught exception: "
                        << boost::diagnostic_information(e)
                        ;
                return EXIT_FAILURE;
        }
}
