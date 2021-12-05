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
LINK_APP_S = src/link_app.S
$(LINK_APP_S): $(script)
	$(script)


SRCs = $(shell find src/ -name "*.[cS]")

# the script to generate link_app.S
script = ./build.sh
MODE := kernel

# compile.mk responsed to comiple src to elf
include $(OS_HOME)/compile.mk

