# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/02 19:17:05 by abelov            #+#    #+#              #
#    Updated: 2025/08/02 19:17:05 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN_DIR			= bin
OBJCOPY			= objcopy
OBJDUMP			= objdump
TARGET			= hw

RMFLAGS			= -r

SRCS			:= src/hw.asm
OBJS			= $(SRCS:%.S=$(BIN_DIR)/%.o)

.PRECIOUS: $(BIN_DIR)/%.o
$(BIN_DIR)/%.o: src/%.asm
		@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
		nasm -f elf -F dwarf -g -o $@ $<

.PRECIOUS: $(BIN_DIR)/%.elf
$(BIN_DIR)/%.elf: $(BIN_DIR)/%.o
		@ld -m elf_i386 -t -o $@.debug $<
		@ld -m elf_i386 -St -o $@ $<

all: $(TARGET)

$(TARGET): $(BIN_DIR)/$(TARGET).elf
		cp $< $@
		$(OBJDUMP) -wh $@

clean:
		@if [ -d $(BIN_DIR) ]; then $(RM) $(RMFLAGS) $(BIN_DIR); fi

fclean: clean
		@if [ -f $(TARGET).bin ]; then $(RM) $(RMFLAGS) $(TARGET); fi

re: fclean
		+$(MAKE) all

.PHONY: all clean fclean re

