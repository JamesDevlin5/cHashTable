
CC = gcc
CFLAGS = -Wall -g -Iinclude

DRIVER = src/driver.c
UTILS  = src/utils.c

default: array

array: src/array_tbl.c $(DRIVER) $(UTILS)
	$(CC) $(CFLAGS) $^ -o $@

linear: src/linear_tbl.c $(DRIVER) $(UTILS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@$(RM) -v linear array

.PHONY: clean default
