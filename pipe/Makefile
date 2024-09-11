CC = gcc
CFLAGS = -o
TARGETS = pipe

all: $(TARGETS)
#%: %.c: compila cualquier archivo .c
%: %.c
	$(CC) $(CFLAGS) $@.exe $@.c

clean:
	rm -f $(TARGETS) *.exe


