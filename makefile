CC=gcc
CFLAGS=-std=gnu99 -Wpedantic

%: %.o
%: %.c

holes: holes.o utils.o
	$(CC) $(CFLAGS) holes.o utils.o -o holes

clean:
	rm holes *.o

%.o: %.c holes.h
	$(CC) -c $(CLFAGS) $< -o $@