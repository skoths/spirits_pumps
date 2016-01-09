CC=gcc
CFLAGS=-Wall -g
OBJS=spirits_pumps.o i2c.o io_23017.o

all: spirits_pumps 

spirits_pumps: $(OBJS)

install:
	sudo chown root:root spirits_pumps
	sudo chmod u+s spirits_pumps

clean:
	rm -rf *.o
	rm -rf spirits_pumps
