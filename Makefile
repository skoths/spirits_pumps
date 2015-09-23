CC=gcc
CFLAGS=-Wall -DRPI_PULLUP -g
OBJS=spirits_pumps.o io_23s17.o

all: spirits_pumps 

spirits_pumps: $(OBJS)

install:
	sudo chown root:root spirits_pumps
	sudo chmod u+s spirits_pumps

clean:
	rm -rf *.o
	rm -rf spirits_pumps
