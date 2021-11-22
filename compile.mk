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
DST_DIR   = $(WORK_DIR)/build/$(ARCH)


INC_PATH += $(WORK_DIR)/include 
OBJs = $(addprefix $(DST_DIR)/, $(addsuffix .o, $(basename $(SRCs))))

LIB_NAME := libc

LIBs = $(addsuffix -riscv64.a, $(join $(addsuffix /build/, \
	$(addprefix $(OS_HOME)/, $(LIB_NAME))), \
	$(LIB_NAME) ))

ARCHIVE = $(BUILD_DIR)/$(NAME)-$(ARCH).a

LINKAGE = $(OBJs) $(ARCHIVE)

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

$(DST_DIR)/%.o: %.c
	@mkdir -p $(dir $@) 
	@echo + GCC $<
	$(CC) -std=gnu11 $(CFLAGS) -c -o $@ $(realpath $<)

$(DST_DIR)/%.o: %.S
	@mkdir -p $(dir $@) && echo + AS $<
	@$(AS) $(ASFLAGS) -c -o $@ $(realpath $<)

# Rule (archive): objects (`*.o`) -> `ARCHIVE.a` (ar)
$(ARCHIVE): $(OBJS)
	@mkdir -p $(dir $@)
	@echo + AR "->" $(ARCHIVE)
	@ar -rcs $(ARCHIVE) $(OBJS)
	

# ====================
$(LIBS): %:
	@$(MAKE) -s -C $(Project)/$* archive

$(IMAGE).elf: $(OBJs)
	@echo + LD "->" $(IMAGE_REL).elf
	$(LD) $(LDFLAGS) -o $(IMAGE).elf --start-group $(LINKAGE) --end-group

# elf -> bin dump.txt 
build: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

archive: $(ARCHIVE)

# objcopy arguments
# -S: Remove all symbol and relocation information
# --set-section-flags <name>=<flags>: Set section <name>'s properties to <flags>
# -O --output-target <bfdname>: Create an output file in format <bfdname>

clean:
	rm -rf $(BUILD_DIR)
.PHONY: build archive cleam