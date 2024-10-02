CC = g++
CFLAGS = -o
TARGETS = thread threadDetach

all: $(TARGETS)

#%: %.c: compila cualquier archivo .c
%: %.c
	$(CC) $(CFLAGS) $@.exe $@.cpp -lpthread

clean:
	rm -f $(TARGETS) *.exe

