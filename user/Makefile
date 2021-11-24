# =================
# usr app
# =================

Project = ..
APP_DIR := src/bin
APP = $(basename $(notdir $(shell find src/bin/ -name "*.c")))

BASE_SRC = $(wildcard src/*.c)


all: $(addprefix Makefile., $(APP))
	@echo $(APP) complete!

$(APP): %: Makefile.%

Makefile.%: $(APP_DIR)/%.c 
	@/bin/echo -e "NAME = $*\nSRCs = $< ${BASE_SRC}\nLIBs += libc\ninclude ${Project}/compile.mk" > $@
	-@make -s -f $@ $(MAKECMDGOALS)
	-@rm -f Makefile.$*

test:
	@echo MAKECMDGOALS = $(MAKECMDGOALS)

run-unos: all
	@echo run on qemu-riscv64

clean:
	rm -rf Makefile.* build/

.PHONY: all clean test