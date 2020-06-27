# Makefile
BINARY=sha3
OBJS=keccak-tiny-unrolled.o main.o 
DIST=sha3_roy
CC=gcc -std=c99
CFLAGS=
LIBS= 
LDFLAGS=
INCLUDES=
$(BINARY): $(OBJS)
	$(CC) $(LDFLAGS) -o $(BINARY) $(OBJS) $(LIBS)		
.c.o:	input.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@		
clean:
	rm -rf $(DIST)-*.txz $(OBJS) $(BINARY) *~ 		
dist: clean
	cd ..; \
	tar cfvJ $(DIST)/$(DIST)-`date -u "+%Y%m%d%H%M00"`.txz $(DIST)/*
