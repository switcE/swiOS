CC := x86_64-elf-gcc
CFLAGS := -ffreestanding -nostdlib -Wall -Wextra -std=gnu11
LDFLAGS := -T kernel.ld
SRCFILES := $(wildcard *.c)
OBJ := $(SRCFILES:.c=.o)

all: kernel.bin

kernel.bin: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.bin

distclean: clean