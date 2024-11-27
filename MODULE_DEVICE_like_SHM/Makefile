obj-m += chardev.o
CC = gcc
CFLAGS = -o
TARGETS = p pInit read

all: $(TARGETS)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
%: %.c
	$(CC) $(CFLAGS) $@.exe $@.c
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f $(TARGETS) *.exe
