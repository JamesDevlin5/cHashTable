#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
 * Define types of table key/value items
 */
typedef char *tbl_key;
typedef int tbl_val;

// Forward declaration
struct hash_tbl;

/*
 * Create a new (empty) table
 */
struct hash_tbl *new(void);

/*
 * Checks if there are no elements in the table
 */
bool is_empty(struct hash_tbl *);

/*
 * Gets the number of elements in the table
 */
int size(struct hash_tbl *);
/*
 * Removes all elements from the table
 */
void clear(struct hash_tbl *);
/*
 * Copies all elements in the table and returns the new table
 */
// struct hash_tbl *clone(struct hash_tbl *);

/*
 * True if the key is present in the table with any value
 */
bool contains_key(struct hash_tbl *, tbl_key key);
/*
 * True if the key is present in the table and its value is equal to the one
 * supplied
 */
bool contains_item(struct hash_tbl *, tbl_key key, tbl_val val);

/*
 * Gets a pointer to the value mapped to the supplied key within the table
 * > nullptr if key is not present in the table
 * > ptr allows for direct modification of the key's mapped value
 */
tbl_val *get(struct hash_tbl *, tbl_key key);
/*
 * Stores the supplied key in the table with the provided value mapping
 */
void put(struct hash_tbl *, tbl_key key, tbl_val val);

/*
 * Removes the key and its mapping to any value from the table
 * Returns the value that the key was mapped to, or nullptr if the key was not
 * in the table
 */
tbl_val *rm_key(struct hash_tbl *, tbl_key key);
/*
 * Removes the key-value mapping from the table if it exists within the table
 * Returns true if the mapping was removed, false if it was not present in the
 * table
 */
bool rm(struct hash_tbl *, tbl_key key, tbl_val val);

#endif
