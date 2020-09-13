#
# Makefile
#

include ../../Config.mk

CIRCLEHOME = ../../libs/circle-stdlib/libs/circle
NEWLIBDIR = ../../libs/circle-stdlib/install/$(NEWLIB_ARCH)

OBJS	= main.o kernel.o

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I ../../include -I ../../libs/circle-stdlib/include -std=c++11
LIBS := "$(NEWLIBDIR)/lib/libm.a" "$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
  	$(CIRCLEHOME)/lib/usb/libusb.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/addon/fatfs/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  	$(CIRCLEHOME)/lib/net/libnet.a \
  	$(CIRCLEHOME)/lib/sched/libsched.a \
  	$(CIRCLEHOME)/lib/libcircle.a \
	../../src/derpy2d/libderpy2d.a

-include $(DEPS)

# CIRCLE_STDLIB_DIR = ../../libs/circle-stdlib
#
# MBEDTLS_DIR ?= $(CIRCLE_STDLIB_DIR)/libs/mbedtls
# NEWLIBDIR   ?= $(CIRCLE_STDLIB_DIR)/install/$(NEWLIB_ARCH)
# CIRCLEHOME  ?= $(CIRCLE_STDLIB_DIR)/libs/circle
# DERPY2D  ?= ../../src/derpy2d
#
# OBJS	= main.o kernel.o
#
# INCLUDE += \
# 	   -I $(CIRCLE_STDLIB_DIR)/include \
# 	   -I $(NEWLIBDIR)/include \
# 	   -I $(MBEDTLS_DIR)/include \
# 	   -I ../../include
#
# include $(CIRCLEHOME)/Rules.mk
#
# CFLAGS += -DMBEDTLS_CONFIG_FILE='<circle-mbedtls/config-circle-mbedtls.h>'
# CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I ../../include
# LIBS := "$(NEWLIBDIR)/lib/libm.a" "$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
#  	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
#   	$(CIRCLEHOME)/lib/usb/libusb.a \
#  	$(CIRCLEHOME)/lib/input/libinput.a \
#  	$(CIRCLEHOME)/addon/fatfs/libfatfs.a \
#  	$(CIRCLEHOME)/lib/fs/libfs.a \
#   	$(CIRCLEHOME)/lib/net/libnet.a \
#   	$(CIRCLEHOME)/lib/sched/libsched.a \
# 	$(CIRCLEHOME)/addon/qemu/libqemusupport.a \
#   	$(CIRCLEHOME)/lib/libcircle.a \
#   	$(DERPY2D)/libderpy.a
#
#
#
# -include $(DEPS)
#
