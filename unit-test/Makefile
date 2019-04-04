# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/28 16:44:43 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/03/28 16:48:59 by mhouppin    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SOURCES := $(wildcard asm_codes/*.s)
OBJECTS := $(patsubst asm_codes/%.s,../cores/%.cor,${SOURCES})

all: $(OBJECTS)

../cores/%.cor: asm_codes/%.s
	../asm/asm $< -o $@

clean:
	rm -f $(OBJECTS)

re: clean all

.PHONY: all clean re
