# Makefile
# Reseni IJC-DU1, Makefile, 12.3.2021
# Autor: Lucie Svobodova, xsvobo1x, FIT

CC = gcc
EXEC = primes primes-i steg-decode
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2
LDFLAGS = -lm

all: $(EXEC)

# kompilace primes, primes-i
# kompilace s makry 
primes: primes.o error.o eratosthenes.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

primes.o: primes.c primes.h bitset.h

eratosthenes.o: eratosthenes.c primes.h bitset.h 

error.o: error.c error.h

# kompilace s inline funkcemi
primes-i: primes-i.o error.o eratosthenes-i.o bitset.o
	$(CC) $(CFLAGS) $(LDFLAGS) -DUSE_INLINE $^ -o $@

primes-i.o: primes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c $^ -o $@

eratosthenes-i.o: eratosthenes.c primes.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@
	                

# kompilace steg-decode
steg-decode: steg-decode.o eratosthenes.o error.o ppm.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

steg-decode.o: steg-decode.c primes.h error.h bitset.h ppm.h

ppm.o: ppm.c error.h ppm.h

clean:
	rm $(EXEC) *.o

run: primes primes-i
	./primes
	./primes-i
