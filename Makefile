CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=gnu99

all: greencat

clean:
	-rm greencat.o

greencat: greencat.o
