
CC = gcc
CFLAGS = -Wall -g -Iinclude

DRIVER = src/driver.c
UTILS  = src/utils.c

default: linear

linear: src/linear_tbl.c $(DRIVER) $(UTILS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) linear

.PHONY: clean default
