#
# Makefile
#

include ../../Config.mk

CIRCLE_STDLIB_DIR = ../../libs/circle-stdlib

NEWLIBDIR   ?= $(CIRCLE_STDLIB_DIR)/install/$(NEWLIB_ARCH)
CIRCLEHOME  ?= $(CIRCLE_STDLIB_DIR)/libs/circle

CPP	= $(CXX_FOR_TARGET)

OBJS	= st7735.o vec.o matrix.o aabb.o image.o graphics.o color.o assets.o

OPTIMIZE ?= -O2

INCLUDE	+= -I $(CIRCLEHOME)/include -I $(CIRCLEHOME)/addon -I $(CIRCLEHOME)/app/lib \
	   -I $(CIRCLEHOME)/addon/vc4 -I $(CIRCLEHOME)/addon/vc4/interface/khronos/include

AFLAGS	+= $(ARCH) $(DEFINE) $(INCLUDE) $(OPTIMIZE)
CFLAGS	+= $(ARCH) -Wall -fsigned-char -ffreestanding $(DEFINE) $(INCLUDE) $(OPTIMIZE) -g
CPPFLAGS+= $(CFLAGS) -std=c++14

INCLUDE += \
	   -I $(CIRCLE_STDLIB_DIR)/include \
	   -I $(NEWLIBDIR)/include \
	   -I ../../include

LIBS := "$(NEWLIBDIR)/lib/libm.a" "$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
  	$(CIRCLEHOME)/lib/usb/libusb.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/addon/fatfs/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  	$(CIRCLEHOME)/lib/net/libnet.a \
  	$(CIRCLEHOME)/lib/sched/libsched.a \
  	$(CIRCLEHOME)/lib/libcircle.a

%.o: %.cpp
	@echo "  CPP   $@"
	@$(CPP) $(CPPFLAGS) $(INCLUDE) -c -o $@ $<

libderpy2d.a: $(OBJS)
	@echo "  AR    $@"
	@rm -f $@
	@$(AR) cr $@ $(OBJS)

clean:
	rm -f *.d *.o *.a *.elf *.lst *.img *.hex *.cir *.map *~
