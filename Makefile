.NOTPARALLEL:

include Config.mk

all: circle newlib $(MBEDTLS) derpy2d

build-samples: build-stdlib-samples $(MBEDTLS_SAMPLES)

circle:
	cd libs/circle-stdlib/libs/circle && ./makeall --nosample
	$(MAKE) -C libs/circle-stdlib/libs/circle/addon/SDCard
	$(MAKE) -C libs/circle-stdlib/libs/circle/addon/fatfs
	$(MAKE) -C libs/circle-stdlib/libs/circle/addon/qemu
	cd libs/circle-stdlib/libs/circle/addon/wlan && ./makeall --nosample

newlib:
	CPPFLAGS_FOR_TARGET='$(CPPFLAGS_FOR_TARGET)' \
	CC_FOR_TARGET='$(CC_FOR_TARGET)' \
	CXX_FOR_TARGET='$(CXX_FOR_TARGET)' \
	GCC_FOR_TARGET='$(GCC_FOR_TARGET)' \
	AR_FOR_TARGET='$(AR_FOR_TARGET)' \
	AS_FOR_TARGET='$(AS_FOR_TARGET)' \
	LD_FOR_TARGET='$(LD_FOR_TARGET)' \
	RANLIB_FOR_TARGET='$(RANLIB_FOR_TARGET)' \
	OBJCOPY_FOR_TARGET='$(OBJCOPY_FOR_TARGET)' \
	OBJDUMP_FOR_TARGET='$(OBJDUMP_FOR_TARGET)' \
	$(MAKE) -C $(NEWLIB_BUILD_DIR) && \
	$(MAKE) -C $(NEWLIB_BUILD_DIR) install

derpy2d:
	CPPFLAGS_FOR_TARGET='$(CPPFLAGS_FOR_TARGET)' \
	CC_FOR_TARGET='$(CC_FOR_TARGET)' \
	CXX_FOR_TARGET='$(CXX_FOR_TARGET)' \
	GCC_FOR_TARGET='$(GCC_FOR_TARGET)' \
	AR_FOR_TARGET='$(AR_FOR_TARGET)' \
	AS_FOR_TARGET='$(AS_FOR_TARGET)' \
	LD_FOR_TARGET='$(LD_FOR_TARGET)' \
	RANLIB_FOR_TARGET='$(RANLIB_FOR_TARGET)' \
	OBJCOPY_FOR_TARGET='$(OBJCOPY_FOR_TARGET)' \
	OBJDUMP_FOR_TARGET='$(OBJDUMP_FOR_TARGET)' \
	$(MAKE) -C src/derpy2d

build-stdlib-samples:
	$(MAKE) -C libs/circle-stdlib/samples/01-nosys
	$(MAKE) -C libs/circle-stdlib/samples/02-stdio-hello
	$(MAKE) -C libs/circle-stdlib/samples/03-stdio-fatfs
	$(MAKE) -C libs/circle-stdlib/samples/04-std
	$(MAKE) -C libs/circle-stdlib/samples/05-smoketest

clean-stdlib-samples:
	-$(MAKE) -C libs/circle-stdlib/samples/01-nosys clean
	-$(MAKE) -C libs/circle-stdlib/samples/02-stdio-hello clean
	-$(MAKE) -C libs/circle-stdlib/samples/03-stdio-fatfs clean
	-$(MAKE) -C libs/circle-stdlib/samples/04-std clean
	-$(MAKE) -C libs/circle-stdlib/samples/05-smoketest clean

MBEDTLS_INCLUDE = -I../../../include -I../../circle/include
MBED_DEFINE = -DMBEDTLS_CONFIG_FILE='<circle-mbedtls/config-circle-mbedtls.h>'

mbedtls:
	CC=$(CC) \
	CFLAGS="$(ARCH) -fsigned-char -ffreestanding -O2 -Wno-parentheses -g $(MBEDTLS_INCLUDE) $(MBED_DEFINE)" \
	$(MAKE) -C libs/circle-stdlib/libs/mbedtls/library && \
	$(MAKE) -C libs/circle-stdlib/src/circle-mbedtls

build-mbedtls-samples:
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/01-https-client1
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/02-https-client2
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/03-https-server1
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/04-https-server2
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/05-https-client3
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/06-webclient
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/07-mqttclient

clean-mbedtls-samples:
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/01-https-client1 clean
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/02-https-client2 clean
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/03-https-server1 clean
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/04-https-server2 clean
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/05-https-client3 clean
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/06-webclient clean
	$(MAKE) -C libs/circle-stdlib/samples/mbedtls/07-mqttclient clean

clean: clean-stdlib-samples clean-mbedtls-samples
	-cd libs/circle-stdlib/libs/circle && ./makeall --nosample PREFIX=$(TOOLPREFIX) clean
	-$(MAKE) -C libs/circle-stdlib/libs/circle/addon/SDCard PREFIX=$(TOOLPREFIX) clean
	-$(MAKE) -C libs/circle-stdlib/libs/circle/addon/fatfs PREFIX=$(TOOLPREFIX) clean
	-$(MAKE) -C libs/circle-stdlib/libs/circle/addon/qemu PREFIX=$(TOOLPREFIX) clean
	-cd libs/circle-stdlib/libs/circle/addon/wlan && ./makeall --nosample PREFIX=$(TOOLPREFIX) clean
	-$(MAKE) -C $(NEWLIB_BUILD_DIR) clean
	-test -n "$(NEWLIB_INSTALL_DIR)" && rm -rf "$(NEWLIB_INSTALL_DIR)"/*
	-$(MAKE) -C libs/circle-stdlib/libs/mbedtls/library clean
	-$(MAKE) -C libs/circle-stdlib/src/circle-mbedtls clean
	-$(MAKE) -C src/derpy2d clean

mrproper: clean
	-rm -f Config.mk
	-rm -rf libs/circle-stdlib/build/circle-newlib/*
	-rm -rf build/derpy2d/*
