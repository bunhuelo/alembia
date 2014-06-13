# Compiler
CC=gcc
# Remove
RM=rm -rf
# Compiler flags
CFLAGS=-Ofast -Wpedantic

# Here we go:
all: alembia

clean:
	$(RM) alembia *.o
	
#install: all
#	cp blpipe /usr/bin/blpipe
	
#uninstall:
#	$(RM) /usr/bin/blpipe
  
#blcipher.o: blcipher.c blcipher.h
#	$(CC) $(CFLAGS) -c blcipher.c
	
#blpipe: blcipher.o blpipe.c blpipe.h
#	$(CC) $(CFLAGS) -o blpipe blcipher.o blpipe.c
  