.PHONY:clean

CC = gcc
CFLAGS = -Wall -g

HASH_CAL_OBJ = hash_calculate.o
BIN_DIR = /usr/bin

hash_calculate:$(HASH_CAL_OBJ)
	$(CC) $(CFLAGS) -lcrypto $^ -o $@
	rm $(HASH_CAL_OBJ) -f
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

install:
	install -D -m 0755 hash_calculate $BUILDROOT$(BIN_DIR)/hash_calculate

clean:
	rm -f *.o hash_calculate
