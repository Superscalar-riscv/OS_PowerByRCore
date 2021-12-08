# =================
# mini os 
# =================

# qemu 
BOOTLOADER = ../bootloader/rustsbi-qemu.bin

# kernel config
KERNEL_ENTRY = 0x80200000

Project = $(abspath ../)

# elf name
NAME = os
# source files will compile
SRCs = $(wildcard src/*.[cS] src/syscall/*.[cS] src/trap/*.[cS])#$(shell find src/ -name "*.[cS]" | sort | uniq)

# first make user bin, then run build script to generate link_app.S
LINK_APP_S = src/link_app.S
user-bin:
	$(MAKE) -C ../user build

.PHONY: user-bin

$(LINK_APP_S): user-bin
	./build.sh

have=$(findstring $(LINK_APP_S), $(SRCs))
ifneq ($(have), $(LINK_APP_S))
SRCs += $(LINK_APP_S)
endif

# add link_app.S to clean scope
ALLBUILD += $(LINK_APP_S)

# the type of archive for platform(kernel/user)
MODE := kernel

# compile.mk responsed to comiple src to elf
include ../compile.mk
