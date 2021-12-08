# =================
# mini os 
# =================

# qemu 
BOOTLOADER = ../bootloader/rustsbi-qemu.bin

# kernel config
KERNEL_ENTRY = 0x80200000

# elf name
NAME = os

# source files will compile
# first make user bin, then run build script to generate link_app.S
LINK_APP_S = src/link_app.S
$(LINK_APP_S):
	$(MAKE) -C ../user build
	./build.sh

SRCs = $(shell find src/ -name "*.[cS]")

have = $(findstring $(LINK_APP_S), $(SRCs))
ifeq ($(have), $(LINK_APP_S))
# SRCs += $(LINK_APP_S)
endif

# the type of archive for platform(kernel/user)
MODE := kernel

# compile.mk responsed to comiple src to elf
include ../compile.mk
