<<<<<<< Updated upstream
MAKEFLAGS += -rR
.SUFFIXES:

OUTPUT := bootloader
ARCH := x86_64

QEMUFLAGS := -m 2G
CC := x86_64-elf-gcc
AR := x86_64-elf-ar
OBJCOPY := x86_64-elf-objcopy
CFLAGS := -g -O2 -pipe
CPPFLAGS :=

CFLAGS += -Wall -Wextra -std=gnu11 -nostdinc -ffreestanding -fno-stack-protector \
          -fno-stack-check -fshort-wchar -fPIE -ffunction-sections -fdata-sections

CPPFLAGS := -I /Users/switce/Downloads/nyu-efi-trunk/inc -MMD -MP

LDFLAGS := -nostdlib -pie -z text -z max-page-size=0x1000 -Wl,--gc-sections \
           -T /Users/switce/Downloads/nyu-efi-trunk/src/elf_$(ARCH)_efi.lds

SRCFILES := $(wildcard *.c)
OBJ := $(SRCFILES:.c=.o)
HEADER_DEPS := $(SRCFILES:.c=.d)

all: $(OUTPUT).efi

-include $(HEADER_DEPS)

$(OUTPUT).efi: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(OUTPUT)
	$(OBJCOPY) -O binary $(OUTPUT) $(OUTPUT).efi

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d $(OUTPUT) $(OUTPUT).efi

distclean: clean
	rm -rf nyu-efi
=======
# WIP
>>>>>>> Stashed changes
