# loc
small C++ program to print the lines of code in a directory

for examples
        ./loc --max-depth 2 /store/repo/linus
         20,653,728 linus
             \______ 12,850,773 drivers
             |           \______ 2,868,391 net
             |           \______ 1,638,560 gpu
             |           \______ 1,082,237 media
             |           \______ 889,512 scsi
             |           \______ 771,947 staging
             |           \______ 484,147 usb
             |           \______ 360,290 infiniband
             |           \______ 327,422 video
             |           \______ 255,853 pinctrl
             |           \______ 222,948 clk
             |           \______ 210,282 tty
             |           \______ 187,262 input
             |           \______ 185,054 isdn
             |           \______ 148,934 acpi
             |           \______ 148,029 mtd
             |           \______ 140,380 iio
             |           \______ 130,439 hwmon
             |           \______ 122,327 block
             |           \______ 121,897 s390
             |           \______ 118,821 misc
             |           \______ 112,878 md
             |           \______ 104,383 dma
             |           \______ 103,426 crypto
             |           \______ 98,528 mfd
             |           \______ 93,075 char
             |           \______ 90,469 mmc
             |           \______ 87,180 ata
             |           \______ 86,690 pci
             |           \______ 75,777 hid
             |           \______ 75,510 i2c
             |           \______ 69,424 spi
             |           \______ 66,226 regulator
             |           \______ 65,473 rtc
             |           \______ 65,208 platform
             |           \______ 62,210 power
             |           \______ 59,391 target
             |           \______ 55,654 watchdog
             |           \______ 52,439 gpio
             |           \______ 45,699 edac
             |           \______ 44,303 iommu
             |           \______ 42,094 atm
             |           \______ 41,027 base
             |           \______ 39,424 ide
             |           \______ 35,592 message
             |           \______ 34,113 cpufreq
             |           \______ 31,080 soc
             |           \______ 29,756 thermal
             |           \______ 28,314 phy
             |           \______ 27,731 firmware
             |           \______ 27,205 pcmcia
             |           \______ 27,002 irqchip
             |           \______ 26,670 xen
             |           \______ 26,617 leds
             |           \______ 26,554 nfc
             |           \______ 23,359 macintosh
             |           \______ 22,868 nvme
             |           \______ 22,630 bluetooth
             |           \______ 19,909 clocksource
             |           \______ 19,193 hwtracing
             |           \______ 16,297 pwm
             |           \______ 16,154 rapidio
             |           \______ 15,074 firewire
             |           \______ 14,963 memory
             |           \______ 13,331 parport
             |           \______ 13,012 vfio
             |           \______ 12,613 parisc
             |           \______ 12,417 of
             |           \______ 12,338 uwb
             |           \______ 11,755 nvdimm
             |           \______ 10,833 extcon
             |           \______ 10,714 w1
             |           \______ 10,664 bus
             |           \______ 10,108 hv
             |           \______ 9,919 vme
             |           \______ 9,400 ntb
             |           \______ 9,350 ssb
             |           \______ 9,112 memstick
             |           \______ 8,628 pnp
             |           \______ 8,193 vhost
             |           \______ 7,938 mailbox
             |           \______ 7,118 hsi
             |           \______ 6,710 remoteproc
             |           \______ 6,149 bcma
             |           \______ 5,835 ps3
             |           \______ 5,804 devfreq
             |           \______ 5,589 cpuidle
             |           \______ 5,148 virtio
             |           \______ 4,627 cdrom
             |           \______ 4,581 sbus
             |           \______ 4,510 lightnvm
             |           \______ 4,380 sh
             |           \______ 4,301 lguest
             |           \______ 4,252 thunderbolt
             |           \______ 4,067 android
             |           \______ 3,773 fpga
             |           \______ 3,592 uio
             |           \______ 3,471 dma-buf
             |           \______ 3,311 nvmem
             |           \______ 3,258 reset
             |           \______ 3,090 rpmsg
             |           \______ 2,992 oprofile
             |           \______ 2,492 perf
             |           \______ 2,335 ipack
             |           \______ 2,271 ptp
             |           \______ 2,268 powercap
             |           \______ 1,954 pps
             |           \______ 1,789 auxdisplay
             |           \______ 1,728 fmc
             |           \______ 1,650 spmi
             |           \______ 1,487 hwspinlock
             |           \______ 1,482 idle
             |           \______ 1,226 nubus
             |           \______ 1,178 mcb
             |           \______ 1,073 amba
             |           \______ 977 dax
             |           \______ 936 virt
             |           \______ 889 zorro
             |           \______ 871 connector
             |           \______ 843 sn
             |           \______ 816 sfi
             |           \______ 814 vlynq
             |           \______ 626 eisa
             |           \______ 581 dca
             |           \______ 513 dio
             |           \______ 393 accessibility
             |           \______ 312 tc
             |           \______ 85 ras
             \______ 2,697,383 arch
             |           \_____ 465,023 arm
             |           \_____ 391,083 mips
             |           \_____ 362,155 powerpc
             |           \_____ 321,501 x86
             |           \_____ 115,230 cris
             |           \_____ 107,330 blackfin
             |           \_____ 96,694 sparc
             |           \_____ 86,680 sh
             |           \_____ 83,181 arm64
             |           \_____ 83,001 ia64
             |           \_____ 80,480 s390
             |           \_____ 62,249 m68k
             |           \_____ 61,351 tile
             |           \_____ 53,490 alpha
             |           \_____ 53,335 metag
             |           \_____ 49,526 parisc
             |           \_____ 27,212 mn10300
             |           \_____ 24,772 xtensa
             |           \_____ 24,468 um
             |           \_____ 20,988 avr32
             |           \_____ 20,348 m32r
             |           \_____ 20,221 arc
             |           \_____ 18,972 frv
             |           \_____ 13,792 microblaze
             |           \_____ 12,273 unicore32
             |           \_____ 9,236 hexagon
             |           \_____ 8,363 nios2
             |           \_____ 7,789 c6x
             |           \_____ 6,391 openrisc
             |           \_____ 6,104 score
             |           \_____ 4,145 h8300
             \______ 1,198,229 fs
             |           \_____ 124,812 btrfs
             |           \_____ 123,050 xfs
             |           \_____ 94,843 ocfs2
             |           \_____ 71,596 nfs
             |           \_____ 60,648 nls
             |           \_____ 54,310 cifs
             |           \_____ 49,258 ext4
             |           \_____ 37,221 ubifs
             |           \_____ 35,297 nfsd
             |           \_____ 32,947 jfs
             |           \_____ 32,307 reiserfs
             |           \_____ 29,365 ntfs
             |           \_____ 29,003 gfs2
             |           \_____ 24,682 f2fs
             |           \_____ 23,153 nilfs2
             |           \_____ 22,792 ceph
             |           \_____ 18,416 jffs2
             |           \_____ 17,501 dlm
             |           \_____ 14,042 proc
             |           \_____ 14,002 afs
             |           \_____ 12,369 hfsplus
             |           \_____ 11,171 udf
             |           \_____ 10,861 fuse
             |           \_____ 10,299 ecryptfs
             |           \_____ 10,159 orangefs
             |           \_____ 9,598 ext2
             |           \_____ 8,668 jbd2
             |           \_____ 7,748 lockd
             |           \_____ 7,737 fat
             |           \_____ 7,363 ufs
             |           \_____ 6,764 ncpfs
             |           \_____ 6,744 9p
             |           \_____ 6,513 hpfs
             |           \_____ 6,285 exofs
             |           \_____ 5,967 hfs
             |           \_____ 5,852 fscache
             |           \_____ 5,802 squashfs
             |           \_____ 5,641 quota
             |           \_____ 4,764 cachefiles
             |           \_____ 4,503 notify
             |           \_____ 4,462 overlayfs
             |           \_____ 3,928 affs
             |           \_____ 3,870 isofs
             |           \_____ 3,652 configfs
             |           \_____ 3,636 autofs4
             |           \_____ 3,556 kernfs
             |           \_____ 3,382 befs
             |           \_____ 3,336 coda
             |           \_____ 3,120 pstore
             |           \_____ 2,894 sysv
             |           \_____ 2,734 freevxfs
             |           \_____ 2,615 adfs
             |           \_____ 2,428 minix
             |           \_____ 1,963 debugfs
             |           \_____ 1,783 omfs
             |           \_____ 1,720 crypto
             |           \_____ 1,526 hostfs
             |           \_____ 1,395 sysfs
             |           \_____ 1,365 hugetlbfs
             |           \_____ 1,292 qnx6
             |           \_____ 1,140 efs
             |           \_____ 1,125 bfs
             |           \_____ 1,089 romfs
             |           \_____ 722 qnx4
             |           \_____ 695 cramfs
             |           \_____ 640 tracefs
             |           \_____ 617 efivarfs
             |           \_____ 603 ramfs
             |           \_____ 598 devpts
             |           \_____ 550 exportfs
             |           \_____ 471 openpromfs
             |           \_____ 428 nfs_common
             \______ 997,733 sound
             |          \____ 468,178 soc
             |          \____ 273,710 pci
             |          \____ 44,813 core
             |          \____ 40,009 isa
             |          \____ 39,822 oss
             |          \____ 38,150 usb
             |          \____ 21,615 firewire
             |          \____ 19,747 drivers
             |          \____ 8,676 ppc
             |          \____ 7,450 aoa
             |          \____ 6,299 hda
             |          \____ 5,922 sparc
             |          \____ 4,885 synth
             |          \____ 4,373 i2c
             |          \____ 2,710 mips
             |          \____ 2,603 pcmcia
             |          \____ 2,382 arm
             |          \____ 1,934 atmel
             |          \____ 1,250 spi
             |          \____ 1,198 sh
             |          \____ 1,188 parisc
             \______ 966,561 net
             |          \____ 93,735 netfilter
             |          \____ 92,670 ipv4
             |          \____ 64,589 ipv6
             |          \____ 63,967 mac80211
             |          \____ 54,798 bluetooth
             |          \____ 50,744 core
             |          \____ 43,548 sunrpc
             |          \____ 39,636 sched
             |          \____ 38,028 wireless
             |          \____ 37,212 sctp
             |          \____ 35,177 batman-adv
             |          \____ 31,613 irda
             |          \____ 20,508 bridge
             |          \____ 19,222 nfc
             |          \____ 18,731 tipc
             |          \____ 17,398 ceph
             |          \____ 15,289 rds
             |          \____ 13,663 rxrpc
             |          \____ 13,481 dccp
             |          \____ 12,081 openvswitch
             |          \____ 11,829 llc
             |          \____ 11,792 xfrm
             |          \____ 11,455 atm
             |          \____ 10,674 decnet
             |          \____ 8,806 ieee802154
             |          \____ 8,161 netlabel
             |          \____ 7,316 l2tp
             |          \____ 7,261 vmw_vsock
             |          \____ 6,736 ax25
             |          \____ 6,219 9p
             |          \____ 5,702 caif
             |          \____ 5,301 can
             |          \____ 4,891 packet
             |          \____ 4,882 rose
             |          \____ 4,786 x25
             |          \____ 4,624 iucv
             |          \____ 4,329 mac802154
             |          \____ 4,132 phonet
             |          \____ 4,089 dsa
             |          \____ 4,068 netlink
             |          \____ 4,062 netrom
             |          \____ 3,872 key
             |          \____ 3,704 ncsi
             |          \____ 3,687 unix
             |          \____ 3,433 appletalk
             |          \____ 2,974 6lowpan
             |          \____ 2,949 8021q
             |          \____ 2,790 ipx
             |          \____ 2,597 hsr
             |          \____ 2,540 kcm
             |          \____ 2,454 802
             |          \____ 2,220 mpls
             |          \____ 2,044 wimax
             |          \____ 2,012 rfkill
             |          \____ 1,986 dcb
             |          \____ 1,694 lapb
             |          \____ 1,158 qrtr
             |          \____ 1,132 switchdev
             |          \____ 538 dns_resolver
             |          \____ 521 ethernet
             |          \____ 510 strparser
             |          \____ 203 l3mdev
             \______ 823,134 include
             |          \____ 403,777 linux
             |          \____ 129,401 uapi
             |          \____ 76,870 net
             |          \____ 32,884 dt-bindings
             |          \____ 23,254 trace
             |          \____ 22,826 sound
             |          \____ 20,109 media
             |          \____ 19,229 drm
             |          \____ 15,535 scsi
             |          \____ 13,413 video
             |          \____ 11,685 acpi
             |          \____ 11,243 asm-generic
             |          \____ 10,248 rdma
             |          \____ 8,403 xen
             |          \____ 7,575 crypto
             |          \____ 6,765 soc
             |          \____ 3,327 math-emu
             |          \____ 2,386 target
             |          \____ 1,668 pcmcia
             |          \____ 591 kvm
             |          \____ 580 keys
             |          \____ 448 misc
             |          \____ 323 ras
             |          \____ 233 rxrpc
             |          \____ 186 clocksource
             |          \____ 175 memory
             \______ 302,822 tools
             |          \____ 160,942 perf
             |          \____ 57,556 testing
             |          \____ 21,358 lib
             |          \____ 18,266 power
             |          \____ 7,200 usb
             |          \____ 5,124 include
             |          \____ 5,004 objtool
             |          \____ 4,069 arch
             |          \____ 3,755 virtio
             |          \____ 3,420 lguest
             |          \____ 2,907 vm
             |          \____ 2,310 iio
             |          \____ 2,190 hv
             |          \____ 1,982 thermal
             |          \____ 1,720 net
             |          \____ 1,483 firewire
             |          \____ 1,058 build
             |          \____ 853 gpio
             |          \____ 558 spi
             |          \____ 550 accounting
             |          \____ 340 laptop
             |          \____ 82 cgroup
             |          \____ 63 leds
             |          \____ 32 pcmcia
             \______ 271,835 kernel
             |          \____ 50,325 trace
             |          \____ 31,186 sched
             |          \____ 19,287 time
             |          \____ 14,862 events
             |          \____ 14,092 rcu
             |          \____ 14,089 locking
             |          \____ 9,703 irq
             |          \____ 9,417 power
             |          \____ 9,333 bpf
             |          \____ 8,538 debug
             |          \____ 3,607 printk
             |          \____ 2,167 gcov
             |          \____ 1,066 livepatch
             \______ 120,725 mm
             |          \____ 1,720 kasan
             \______ 114,691 lib
             |          \____ 34,535 fonts
             |          \____ 3,963 mpi
             |          \____ 3,880 raid6
             |          \____ 3,297 xz
             |          \____ 2,595 zlib_deflate
             |          \____ 1,833 zlib_inflate
             |          \____ 1,482 lz4
             |          \____ 1,246 842
             |          \____ 709 reed_solomon
             |          \____ 606 lzo
             \______ 95,373 crypto
             |         \____ 3,978 asymmetric_keys
             |         \____ 1,987 async_tx
             \______ 77,996 security
             |         \____ 24,437 selinux
             |         \____ 12,136 tomoyo
             |         \____ 11,088 keys
             |         \____ 9,096 smack
             |         \____ 8,907 apparmor
             |         \____ 7,018 integrity
             |         \____ 490 yama
             |         \____ 190 loadpin
             \______ 48,466 scripts
             |         \____ 21,636 kconfig
             |         \____ 9,666 dtc
             |         \____ 4,897 mod
             |         \____ 2,586 gcc-plugins
             |         \____ 974 genksyms
             |         \____ 485 basic
             |         \____ 294 selinux
             \______ 40,732 block
             |         \____ 5,824 partitions
             \______ 19,059 samples
             |         \____ 8,737 bpf
             |         \____ 2,031 mic
             |         \____ 1,507 vfio-mdev
             |         \____ 911 v4l
             |         \____ 723 kfifo
             |         \____ 703 seccomp
             |         \____ 654 trace_events
             |         \____ 479 mei
             |         \____ 464 uhid
             |         \____ 451 connector
             |         \____ 435 kobject
             |         \____ 404 configfs
             |         \____ 294 timers
             |         \____ 289 kprobes
             |         \____ 281 auxdisplay
             |         \____ 181 hidraw
             |         \____ 102 rpmsg
             |         \____ 92 livepatch
             |         \____ 91 blackfin
             |         \____ 90 hw_breakpoint
             |         \____ 60 kdb
             |         \____ 56 trace_printk
             |         \____ 24 watchdog
             \______ 14,289 virt
             |         \____ 14,022 kvm
             |         \____ 267 lib
             \______ 8,961 ipc
             \______ 3,698 init
             \______ 623 usr
             \______ 281 firmware
             \______ 244 certs
             \______ 120 Documentation
                      \__ 120 usb


And to see individual files

        ./loc --print-files /store/repo/llvm_git/include/llvm
         240,955 llvm
            \____ 38,629 CodeGen
            |       \____ 3,290 GlobalISel
            |       |       \___ 698 RegisterBankInfo.h
            |       |       \___ 645 RegBankSelect.h
            |       |       \___ 581 MachineIRBuilder.h
            |       |       \___ 441 IRTranslator.h
            |       |       \___ 213 LegalizerInfo.h
            |       |       \___ 205 CallLowering.h
            |       |       \___ 113 LegalizerHelper.h
            |       |       \___ 99 RegisterBank.h
            |       |       \___ 65 Legalizer.h
            |       |       \___ 63 InstructionSelector.h
            |       |       \___ 53 InstructionSelect.h
            |       |       \___ 43 Utils.h
            |       |       \___ 39 GISelAccessor.h
            |       |       \___ 32 Types.h
            |       \____ 1,363 PBQP
            |       |       \___ 662 Graph.h
            |       |       \___ 286 Math.h
            |       |       \___ 221 ReductionRules.h
            |       |       \___ 132 CostAllocator.h
            |       |       \___ 62 Solution.h
            |       \____ 81 MIRParser
            |       |     \__ 81 MIRParser.h
            |       \____ 2,281 SelectionDAGNodes.h
            |       \____ 1,484 SelectionDAG.h
            |       \____ 1,305 MachineInstr.h
            |       \____ 1,089 MachineRegisterInfo.h
            |       \____ 1,052 BasicTTIImpl.h
            |       \____ 1,041 MachineScheduler.h
            |       \____ 928 ISDOpcodes.h
            |       \____ 915 LiveInterval.h
            |       \____ 909 MachineFunction.h
            |       \____ 893 DIE.h
            |       \____ 850 MachineBasicBlock.h
            |       \____ 798 MachineOperand.h
            |       \____ 771 ScheduleDAG.h
            |       \____ 720 MachineValueType.h
            ...
