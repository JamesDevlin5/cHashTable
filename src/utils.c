#include "utils.h"

bool std_contains_key(struct hash_tbl *table, tbl_key key) {
    return get(table, key) != NULL;
}

bool std_contains_item(struct hash_tbl *table, tbl_key key, tbl_val val) {
    tbl_val *item_val = get(table, key);
    if (item_val) {
        return *item_val == val;
    }
    return false;
}

size_t hash(tbl_key key) {
    size_t counter = 1;
    char *c = key;
    while (*c) {
        counter += *c;
        c += 1;
    }
    return counter;
}
