#ifndef HASH_TABLE_UTILS_H
#define HASH_TABLE_UTILS_H

#include "tbl.h"

/*
 * Standard check to see if the table contains the key, by executing a `get` operation
 * and checking whether the result was found.
 */
bool std_contains_key(struct hash_tbl *, tbl_key key);

/*
 * Standard check to see if the table contains the key-value mapping, by executing
 * a `get` operation and checking whether the result matches the supplied value.
 */
bool std_contains_item(struct hash_tbl *, tbl_key key, tbl_val val);

/*
 * Calculate the numeric hash representation of the key
 */
size_t hash(tbl_key key);

#endif
