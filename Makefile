
CC = gcc
CFLAGS = -Wall -g -Iinclude

DRIVER = src/driver.c
UTILS  = src/utils.c

default: array_linked

array_linked: src/array_linked_tbl.c $(DRIVER) $(UTILS)
	$(CC) $(CFLAGS) $^ -o $@

array: src/array_tbl.c $(DRIVER) $(UTILS)
	$(CC) $(CFLAGS) $^ -o $@

linear: src/linear_tbl.c $(DRIVER) $(UTILS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@$(RM) -v linear array array_linked

.PHONY: clean default
