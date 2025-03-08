.PHONY: all bootloader kernel os clean distclean

all: bootloader kernel os

bootloader:
	$(MAKE) -C bootloader

kernel:
	$(MAKE) -C kernel

os:
	$(MAKE) -C os

clean:
	$(MAKE) -C bootloader clean
	$(MAKE) -C kernel clean
	$(MAKE) -C os clean

distclean:
	$(MAKE) -C bootloader distclean
	$(MAKE) -C kernel distclean
	$(MAKE) -C os distclean