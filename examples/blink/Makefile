NAME=main
OBJECTS=$(NAME).o

INCLUDES = ~/ti/gcc/include

DEVICE  = msp430g2553
CC      = msp430-elf-gcc
GDB     = msp430-elf-gdb
CFLAGS = -I $(INCLUDES) -mmcu=$(DEVICE) -O0 -g
LFLAGS = -L $(INCLUDES)

all: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $? -o $(NAME).out

install: all
	mspdebug rf2500 "prog $(NAME).out"

debug: all
	mspdebug rf2500 gdb &

gdb:
	rm -f gdb.cmd
	printf "file $(NAME).out\ntarget remote localhost:2000\nbreak main\nload $(NAME).out\nc\n" >> gdb.cmd
	$(GDB) -x gdb.cmd
	rm -f gdb.cmd

clean: 
	rm -f *.o *.out
