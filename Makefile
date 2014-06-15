# Compiler
CC=gcc
# Remove
RM=rm -rf
# Compiler flags
CFLAGS=-Ofast -Wpedantic

# Here we go:
all: alembia

clean:
	$(RM) test *.o *.gch
#	$(RM) alembia
	
#install: all
#	cp blpipe /usr/bin/blpipe
	
#uninstall:
#	$(RM) /usr/bin/blpipe
  
#blcipher.o: blcipher.c blcipher.h
#	$(CC) $(CFLAGS) -c blcipher.c
	
#blpipe: blcipher.o blpipe.c blpipe.h
#	$(CC) $(CFLAGS) -o blpipe blcipher.o blpipe.c
  
test: test.c pbox.o sbox_alpha.o sbox_bravo.o ale.o toolkit.o
	$(CC) $(CFLAGS) -o test test.c pbox.o sbox_alpha.o sbox_bravo.o ale.o toolkit.o
	
pbox.o: pbox.c pbox.h
	$(CC) $(CFLAGS) -c pbox.c
	
sbox_alpha.o: sbox_alpha.c sbox_alpha.h
	$(CC) $(CFLAGS) -c sbox_alpha.c
	
sbox_bravo.o: sbox_bravo.c sbox_bravo.h
	$(CC) $(CFLAGS) -c sbox_bravo.c
	
toolkit.o: toolkit.c toolkit.h
	$(CC) $(CFLAGS) -c toolkit.c
	
ale.o: ale.c ale.h
	$(CC) $(CFLAGS) -c ale.c
	
	