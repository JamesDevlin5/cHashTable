
CC = gcc
CFLAGS = -Wall -g -Iinclude

DRIVER = src/driver.c

default: linear

linear: src/linear_tbl.c $(DRIVER)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) linear

.PHONY: clean default
