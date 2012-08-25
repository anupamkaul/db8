PLATFORM   	:= linux-x86
ARCH_CFLAGS	:= -I$(LUNA_STAGING)/include -DMOJ_LINUX $(shell pkg-config --cflags glib-2.0) $(shell pkg-config --cflags luna-service2) -fno-strict-aliasing
ARCH_LDFLAGS := -L$(LUNA_STAGING)/lib -Wl,-rpath-link $(LUNA_STAGING)/lib

INCLUDES := \
	-I$(LUNA_STAGING)/include \
	-I/usr/local/BerkeleyDB.4.8/include \
	$(INCLUDES)

include build/Makefile.inc
