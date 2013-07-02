
CC=clang
RM=rm -Rf

CFLAGS=-ggdb -x c -std=c99 -c -Wall -Wextra -Werror -pedantic-errors

SRCROOT=lib/src
INCROOT=lib/include
TSTROOT=lib/test

OBJROOT=build

VPATH=$(SRCROOT):$(INCROOT):$(TSTROOT):$(OBJROOT)

.PHONY: all clean

all: pngpack

clean:
	$(RM) $(OBJROOT)/*.o
	$(RM) pngpack

memblk.o: memblk.c memblk.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

pack.o: pack.c pack.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

main.o: main.c main.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

pngpack: main.o memblk.o pack.o
	$(CC) -o $(@) -lz  $(OBJROOT)/main.o $(OBJROOT)/memblk.o $(OBJROOT)/pack.o
