# =================
# mini os 
# =================

ARCH = riscv64
WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
DST_DIR   = $(WORK_DIR)/build/$(ARCH)

IMAGE_REL = build/minios
IMAGE = $(abspath $(IMAGE_REL))

# qemu 
BOOTLOADER = ./bootloader/rustsbi-qemu.bin
KERNEL_ENTRY = 0x80200000


# Cross Compilers
include riscv64.mk
AS        = $(CROSS_COMPILE)gcc
CC        = $(CROSS_COMPILE)gcc
CXX       = $(CROSS_COMPILE)g++
LD        = $(CROSS_COMPILE)ld
OBJDUMP   = $(CROSS_COMPILE)objdump
OBJCOPY   = $(CROSS_COMPILE)objcopy

INC_PATH += $(WORK_DIR)/os/include 
SRCs = $(shell find os/src/ -name "*.[cS]")
OBJS = $(addprefix $(DST_DIR)/, $(addsuffix .o, $(basename $(SRCs))))
LINKAGE = $(OBJS)

# -Wall 输出较多的警告讯息，以便找出程式的错误
# -ffreestanding : 允许重新定义标准库里已经有的函数
# -g : debug info
# -I: 
# -mcmodel: TODO: 
# -march 
CFLAGS += -ffreestanding -g -Wall -I$(INC_PATH) -mcmodel=medany -march=rv64g
ASFLAGS  += -MMD -I$(INC_PATH)

# -T FILE, --script FILE      Read linker script
# -melf64lriscv : TODO:
LDFLAGS += -T ./linker.ld -melf64lriscv



# ====================
# compile rule
# ====================
$(DST_DIR)/%.o: %.c
	mkdir -p $(dir $@) 
	@echo + GCC $<
	$(CC) -std=gnu11 $(CFLAGS) -c -o $@ $(realpath $<)

$(DST_DIR)/%.o: %.S
	@mkdir -p $(dir $@) && echo + AS $<
	@$(AS) $(ASFLAGS) -c -o $@ $(realpath $<)

# ====================

$(IMAGE).elf: $(OBJS)
	@echo $(OBJS)
	@echo + LD "->" $(IMAGE_REL).elf
	$(LD) $(LDFLAGS) -o $(IMAGE).elf --start-group $(LINKAGE) --end-group

# generate bin dump.txt 
image: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

# objcopy arguments
# -S: Remove all symbol and relocation information
# --set-section-flags <name>=<flags>: Set section <name>'s properties to <flags>
# -O --output-target <bfdname>: Create an output file in format <bfdname>

# TODO: 
run: image
	@qemu-system-riscv64 --machine virt -nographic -bios $(BOOTLOADER) -device \
		loader,file=$(IMAGE).bin,addr=$(KERNEL_ENTRY)

gdb: image


clean:
	-rm -rf $(BUILD_DIR) 

.PHONY: run gdb image clean