# =================
# usr app
# =================

Project = $(abspath ../)
APP_DIR := src/bin
APP = $(basename $(notdir $(shell find src/bin/ -name "*.c")))

BASE_SRC = $(wildcard src/*.c)

all: $(addprefix Makefile., $(APP))
	@echo -e "\033[32m $(APP) complete!\033[0m"

$(APP): %: Makefile.%

Makefile.%: $(APP_DIR)/%.c 
	@/bin/echo -e "NAME = $*\nSRCs = $< ${BASE_SRC}\nLIBs += libc\nMODE=user\ninclude ${Project}/compile.mk" > $@
	-@make -s -f $@ $(MAKECMDGOALS)
	-@rm -f Makefile.$*

test:
	@echo MAKECMDGOALS = $(MAKECMDGOALS)

build: all
	@echo -e "\033[32m build user bin \033[0m"

run: all
	@echo run on qemu-riscv64

clean:
	rm -rf Makefile.* build/

.PHONY: all clean test