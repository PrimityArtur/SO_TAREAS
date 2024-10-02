GCC = gcc
FLAGS = -o
TARGETS = mq_rcv mq_send p

all: $(TARGETS)

% : %.c
	$(GCC) $(FLAGS) $@.exe $@.c

clean : 
	rm -f $(TARGETS).exe
