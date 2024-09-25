GCC = gcc
FLAGS = -o
TARGETS = fork pp
FILES = output

all: $(TARGETS)
% : %.c
	$(GCC) $(FLAGS) $@.exe $@.c  
	
clean:
	rm -f $(TARGETS) *.exe $(FILES) *.txt
