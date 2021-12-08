

NAME = libc
SRCs = $(shell find src/ -name "*.c")

LIB_MODE ?= kernel
ifeq ($(LIB_MODE), kernel)
CFLAGS += -D__KERNEL__
endif

default: archive
.PHONY: default 


# compile 
include ../compile.mk
