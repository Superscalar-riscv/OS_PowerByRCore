# =================
# compile make rule
# =================


# Cross Compilers
CROSS_COMPILE = riscv64-unknown-elf-
AS        = $(CROSS_COMPILE)gcc
CC        = $(CROSS_COMPILE)gcc
CXX       = $(CROSS_COMPILE)g++
LD        = $(CROSS_COMPILE)ld
OBJDUMP   = $(CROSS_COMPILE)objdump
OBJCOPY   = $(CROSS_COMPILE)objcopy


ARCH = riscv64
WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
DST_DIR  ?= $(WORK_DIR)/build/$(ARCH)

IMAGE_REL = build/$(NAME)-$(ARCH)
IMAGE = $(abspath $(IMAGE_REL))

ifdef LIB_MODE
DST_DIR := $(BUILD_DIR)/$(ARCH)-$(LIB_MODE)
endif

OBJs = $(addprefix $(DST_DIR)/, $(addsuffix .o, $(basename $(SRCs))))

LIB_NAME := libc

LIBs = $(addsuffix -riscv64.a, $(join $(addsuffix /build/, \
	$(addprefix $(OS_HOME)/, $(LIB_NAME))), \
	$(LIB_NAME)-$(MODE) ))

test:
	echo $(LIBs)

ARCHIVE = $(BUILD_DIR)/$(NAME)-$(LIB_MODE)-riscv64.a

LINKAGE = $(OBJs) $(LIBs)

INC_PATH += $(WORK_DIR)/include $(addsuffix /include/, $(addprefix $(OS_HOME)/, $(LIB_NAME)))
INCFLAGS += $(addprefix -I, $(INC_PATH))
# -Wall 输出较多的警告讯息，以便找出程式的错误
# -ffreestanding : 允许重新定义标准库里已经有的函数
# -g : debug info
# -I : 
# -mcmodel : TODO: 
# -march 
CFLAGS += -ffreestanding -g -Wall $(INCFLAGS) -mcmodel=medany -march=rv64g
CXXFLAGS +=  $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS  += -MMD -I$(INC_PATH)

# -T FILE, --script FILE      Read linker script
# -melf64lriscv : TODO:
LDFLAGS += -T ./linker.ld -melf64lriscv

default: build
# ====================
# compile rule

$(DST_DIR)/%.o: %.c
	@mkdir -p $(dir $@) 
	@echo + GCC $<
	$(CC) -std=gnu11 $(CFLAGS) -c -o $@ $(realpath $<)

### Rule (compile): a single `.cpp` -> `.o` (g++)
$(DST_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@) && echo + CXX $<
	@$(CXX) -std=c++17 $(CXXFLAGS) -c -o $@ $(realpath $<)

$(DST_DIR)/%.o: %.S
	@mkdir -p $(dir $@) && echo + AS $<
	@$(AS) $(ASFLAGS) -c -o $@ $(realpath $<)

# Rule (archive): objects (`*.o`) -> `ARCHIVE.a` (ar)
$(ARCHIVE): $(OBJs)
	@mkdir -p $(dir $@)
	@echo + AR "->" $(notdir $(ARCHIVE)) 
	@ar -rcs $(ARCHIVE) $(OBJs)


# ====================
$(LIB_NAME): %:
	$(MAKE) -s -C $(OS_HOME)/$* LIB_MODE=$(MODE) archive

$(IMAGE).elf: $(OBJs) $(LIB_NAME)
	@echo + LD "->" $(IMAGE_REL).elf 
	@$(LD) $(LDFLAGS) -o $(IMAGE).elf --start-group $(LINKAGE) --end-group

# objcopy arguments
# -S: Remove all symbol and relocation information
# --set-section-flags <name>=<flags>: Set section <name>'s properties to <flags>
# -O --output-target <bfdname>: Create an output file in format <bfdname>

# elf -> bin dump.txt 
build: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

archive: $(ARCHIVE)

user_bin: 
	make -C ../user/ build

# run os on 
run: build user_bin
	@echo -e "\033[32m run os on qemu-system-riscv64 \033[0m"
	@qemu-system-riscv64 --machine virt -nographic -bios $(BOOTLOADER) -device \
		loader,file=$(IMAGE).bin,addr=$(KERNEL_ENTRY)

debug: build
	@tmux new-session -d \
		"qemu-system-riscv64 -machine virt -nographic -bios $(BOOTLOADER) -device loader,file=$(IMAGE).bin,addr=$(KERNEL_ENTRY) -s -S" && \
		tmux split-window -h "riscv64-unknown-elf-gdb -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'" && \
		tmux -2 attach-session -d

# run usr program on qemu-riscv64
run-unos: build
	@echo "\033[32m run user elf on qemu-riscv64 \033[0m"
	@qemu-riscv64 $(IMAGE).elf

clean:
	rm -rf $(BUILD_DIR) $(OS_HOME)/libc/build


.PHONY: build debug archive cleam $(LIB_NAME) run-unos user_bin