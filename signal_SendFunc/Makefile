CC = gcc
CFLAGS = -o
TARGETS = signal receive

all: $(TARGETS)

#%: %.c: compila cualquier archivo .c
%: %.c
	$(CC) $(CFLAGS) $@.exe $@.c

clean:
	rm -f $(TARGETS) *.exe

