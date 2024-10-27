CC = gcc
CFLAGS = -o
TARGETS = p pInit read

all: $(TARGETS)
%: %.c
	$(CC) $(CFLAGS) $@.exe $@.c
clean:
	rm -f $(TARGETS) *.exe


