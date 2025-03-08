CC := x86_64-elf-g++
CFLAGS := -ffreestanding -nostdlib -Wall -Wextra -std=c++20
LDFLAGS := -T os.ld
SRCFILES := $(wildcard *.cpp)
OBJ := $(SRCFILES:.cpp=.o)

all: os.bin

os.bin: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.bin

distclean: clean