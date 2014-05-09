#
# Makefile for busy-wait IO library
#
XCC     = gcc
AS	= as
AR	= ar
CFLAGS  = -c -fPIC -Wall -I. -I../include -mcpu=arm920t -msoft-float
# -g: include hooks for gdb
# -c: only compile
# -mcpu=arm920t: generate code for the 920t architecture
# -fpic: emit position-independent code
# -Wall: report all warnings
# -msoft-float: use software for floating point

ASFLAGS	= -mcpu=arm920t -mapcs-32
# -mapcs-32: always create a complete stack frame

ARFLAGS = rcs

all:  libbwio.a libclock.a libio.a libparser.a libcontroller.a libbuffer.a

bwio.s: bwio.c 
	$(XCC) -S $(CFLAGS) bwio.c

bwio.o: bwio.s
	$(AS) $(ASFLAGS) -o bwio.o bwio.s

libbwio.a: bwio.o
	$(AR) $(ARFLAGS) $@ bwio.o
	mv $@ ../lib/.

clock.s: clock.c 
	$(XCC) -S $(CFLAGS) clock.c

clock.o: clock.s
	$(AS) $(ASFLAGS) -o clock.o clock.s

libclock.a: clock.o
	$(AR) $(ARFLAGS) $@ clock.o
	mv $@ ../lib/.

io.s: io.c 
	$(XCC) -S $(CFLAGS) io.c

io.o: io.s
	$(AS) $(ASFLAGS) -o io.o io.s

libio.a: io.o
	$(AR) $(ARFLAGS) $@ io.o
	mv $@ ../lib/.

parser.s: parser.c 
	$(XCC) -S $(CFLAGS) parser.c

parser.o: parser.s
	$(AS) $(ASFLAGS) -o parser.o parser.s

libparser.a: parser.o
	$(AR) $(ARFLAGS) $@ parser.o
	mv $@ ../lib/.

controller.s: controller.c 
	$(XCC) -S $(CFLAGS) controller.c

controller.o: controller.s
	$(AS) $(ASFLAGS) -o controller.o controller.s

libcontroller.a: controller.o
	$(AR) $(ARFLAGS) $@ controller.o
	mv $@ ../lib/.

buffer.s: buffer.c 
	$(XCC) -S $(CFLAGS) buffer.c

buffer.o: buffer.s
	$(AS) $(ASFLAGS) -o buffer.o buffer.s

libbuffer.a: buffer.o
	$(AR) $(ARFLAGS) $@buffer.o
	mv $@ ../lib/.

clean:
	-rm -f *.s *.a *.o
