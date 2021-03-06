# Compiler
CC=gcc
# Remove
RM=rm -rf
# Compiler flags
CFLAGS=-Ofast -Wpedantic

# Here we go:
all: alembiapipe test

clean:
	$(RM) *.o *.gch
	$(RM) alembia
	$(RM) test
	
#install: all
#	cp blpipe /usr/bin/blpipe
	
#uninstall:
#	$(RM) /usr/bin/blpipe
  
#blcipher.o: blcipher.c blcipher.h
#	$(CC) $(CFLAGS) -c blcipher.c
	
#blpipe: blcipher.o blpipe.c blpipe.h
#	$(CC) $(CFLAGS) -o blpipe blcipher.o blpipe.c
  
test: test.c pbox.o sbox_alpha.o sbox_bravo.o ale.o toolkit.o mbia.o
	$(CC) $(CFLAGS) -o test test.c pbox.o sbox_alpha.o sbox_bravo.o ale.o toolkit.o mbia.o
	
pbox.o: pbox.c pbox.h
	$(CC) $(CFLAGS) -c pbox.c
	
sbox_alpha.o: sbox_alpha.c sbox_alpha.h
	$(CC) $(CFLAGS) -c sbox_alpha.c
	
sbox_bravo.o: sbox_bravo.c sbox_bravo.h
	$(CC) $(CFLAGS) -c sbox_bravo.c
	
toolkit.o: toolkit.c toolkit.h
	$(CC) $(CFLAGS) -c toolkit.c
	
ale.o: ale.c ale.h #toolkit.o sbox_alpha.o sbox_bravo.o pbox.o
	$(CC) $(CFLAGS) -c ale.c
	
mbia.o: mbia.c mbia.h #toolkit.o sbox_alpha.o sbox_bravo.o pbox.o
	$(CC) $(CFLAGS) -c mbia.c
	
alembiapipe: alembiapipe.c alembiapipe.h pbox.o sbox_alpha.o sbox_bravo.o ale.o mbia.o toolkit.o
	$(CC) $(CFLAGS) -o alembia alembiapipe.c pbox.o sbox_alpha.o sbox_bravo.o ale.o mbia.o toolkit.o
	
	