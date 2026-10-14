# SPDX-License-Identifier: GPL-3.0-or-later
AMIGA_CXX ?= m68k-amigaos-g++

.PHONY: all clean
all: program

program: main.cpp
	$(AMIGA_CXX) -m68020 -O0 -g -ffreestanding -fno-exceptions -fno-rtti \
		-fno-threadsafe-statics -fno-omit-frame-pointer \
		-fdebug-prefix-map=$(CURDIR)=. -nostdlib -Wl,-e,_entry main.cpp -o $@

clean:
	rm -f program
