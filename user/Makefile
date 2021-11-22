# =================
# usr app
# =================

Project = ..
APP_DIR := src/bin
APPs = $(basename $(notdir $(shell find tests/. -name "*.c")))

all: $(addprefix Makefile., $(ALL))
	@echo "" $(ALL)

$(APPs): %: Makefile.%

Makefile.%: $(APP_DIR)/%.c 
	@/bin/echo -e "NAME = $*\nSRCs = $<\nLIBs += libc\ninclude $${Project}/compile.mk" > $@
	-@make -s -f $@ $(MAKECMDGOALS)
	-@rm -f Makefile.$*


clean:
	rm -rf Makefile.* build/

.PHONY: all clean