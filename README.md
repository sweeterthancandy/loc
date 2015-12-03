# loc
small C++ program to print the lines of code in a directory

for examples
        ./loc --max-depth 1 ~/repo/linux_linus

         18964455 linux_linus
            \_____ 11708964 drivers
            \_____ 2581444 arch
            \_____ 1155204 fs
            \_____ 907059 sound
            \_____ 902847 net
            \_____ 732807 include
            \_____ 248257 kernel
            \_____ 217342 tools
            \_____ 111628 mm
            \_____ 108112 lib
            \_____ 89836 crypto
            \_____ 75471 security
            \_____ 44634 scripts
            \_____ 37979 block
            \_____ 11532 virt
            \_____ 9028 samples
            \_____ 8914 ipc
            \_____ 8658 Documentation
            \_____ 3678 init
            \_____ 623 usr
            \_____ 281 firmware
            \_____ 157 certs


        ./loc --max-depth 1 ~/boost_1_59_0/boost_1_59_0/boost

         2049233 boost
            \____ 170318 phoenix
            \____ 158844 mpl
            \____ 141023 spirit
            \____ 117797 geometry
            \____ 114905 fusion
            \____ 104361 math
            \____ 98764 numeric
            \____ 82293 graph
            \____ 70401 asio
            \____ 42641 interprocess
            \____ 39345 log
            \____ 39177 preprocessor
            \____ 37771 proto
            \____ 37374 intrusive
            \____ 37033 thread
            \____ 35957 container
            \____ 34255 polygon
            \____ 32321 multiprecision
            \____ 25453 xpressive
            \____ 24225 regex
            \____ 21990 units
            \____ 21326 wave
            \____ 20965 range
            \____ 19956 python
            \____ 19882 test
            \____ 19337 date_time
            \____ 18755 msm
            \____ 18068 iostreams
            \____ 17579 icl
            \____ 17324 multi_index
            \____ 15250 gil
            \____ 14692 bimap
            \____ 14649 type_traits
            \____ 14601 random
            \____ 14250 accumulators
            \____ 13464 lambda
            \____ 13234 algorithm
            \____ 12494 function_types
            \____ 11604 smart_ptr
            \____ 11097 mpi
            \____ 10549 type_erasure
            \____ 10487 archive
            \____ 10465 chrono
            \____ 9763 atomic
            \____ 9406 serialization
            \____ 9011 config
            \____ 8529 property_tree
            \____ 8154 locale
            \____ 8059 unordered
            \____ 7536 ptr_container
            \____ 7284 heap
            \____ 7138 variant
            \____ 7072 coroutine
            \____ 6761 detail
            \____ 6365 move
            \____ 6254 predef
            \____ 6012 bind
            \____ 5912 signals2
            \____ 5588 circular_buffer
            \____ 5247 statechart
            \____ 5245 parameter
            \____ 5128 iterator
            \____ 4292 local_function
            \____ 4285 ratio
            \____ 4275 typeof
            \____ 3640 flyweight
            \____ 3495 pending
            \____ 3464 lockfree
            \____ 3435 format
            \____ 3297 tti
            \____ 3197 sort
            \____ 3183 multi_array
            \____ 3115 property_map
            \____ 3111 functional
            \____ 2942 program_options
            \____ 2831 filesystem
            \____ 2655 utility
            \____ 2637 function
            \____ 2620 pool
            \____ 2588 lexical_cast
            \____ 2500 exception
            \____ 2417 tr1
            \____ 2008 endian
            \____ 1995 signals
            \____ 1939 dynamic_bitset
            \____ 1938 assign
            \____ 1881 core
            \____ 1723 optional
            \____ 1679 uuid
            \____ 1609 align
            \____ 1572 tuple
            \____ 1445 context
            \____ 1349 convert
            \____ 1080 coroutine2
            \____ 1048 system
            \____ 994 integer
            \____ 975 type_index
            \____ 814 logic
            \____ 629 io
            \____ 509 concept
            \____ 228 concept_check
            \____ 185 timer
