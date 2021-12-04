

NAME = libc
SRCs = $(shell find src/ -name "*.c")


default: archive
.PHONY: default 

LIB_MODE = $(MODE)
ifeq ($(MODE), KERNEL)
CFLAGS += -D__KERNEL__
endif

# compile 
include $(OS_HOME)/compile.mk
