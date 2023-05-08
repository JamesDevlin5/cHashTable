#include <assert.h>
#include <stdio.h>

#include "tbl.h"

int main(void) {
    struct hash_tbl *table = new ();

    /* --- Ensure the empty table doesn't fail any operations --- */
    assert(is_empty(table));
    assert(!contains_key(table, "Hello, World!"));
    assert(!contains_item(table, "C is awesome", 100));
    clear(table);

    assert(get(table, "one") == NULL);
    assert(get(table, "two") == NULL);
    assert(get(table, "three") == NULL);
    assert(get(table, "four") == NULL);
    assert(get(table, "five") == NULL);

    /* --- Populate the table with some values --- */
    put(table, "one", 1);
    put(table, "two", 2);
    put(table, "three", 3);
    put(table, "four", 4);
    put(table, "five", 5);

    /* --- Ensure behavior has changed --- */
    assert(contains_key(table, "one"));
    assert(contains_key(table, "two"));
    assert(contains_key(table, "three"));
    assert(contains_key(table, "four"));
    assert(contains_key(table, "five"));

    assert(!is_empty(table));

    assert(*get(table, "one") == 1);
    assert(*get(table, "two") == 2);
    assert(*get(table, "three") == 3);
    assert(*get(table, "four") == 4);
    assert(*get(table, "five") == 5);

    put(table, "one", 3);
    put(table, "two", -2);
    display(table);

    assert(contains_item(table, "one", 3));
    assert(!contains_item(table, "one", 1));
    assert(contains_item(table, "two", -2));
    assert(!contains_item(table, "two", 2));

    assert(!rm(table, "one", 2));
    assert(!rm(table, "one", 30));
    assert(!rm(table, "one", 4));
    assert(!rm(table, "one", 5));
    assert(!rm(table, "one", 6));

    // assert(rm(table, "one", 1));
    // assert(*rm_key(table, "one") == 1);
    assert(rm_key(table, "one"));
    assert(!rm_key(table, "one"));
    assert(size(table) == 4);

    assert(!contains_item(table, "one", 1));
    assert(!contains_item(table, "two", 1));
    assert(contains_item(table, "two", -2));
    assert(contains_item(table, "three", 3));
    assert(contains_item(table, "four", 4));
    assert(!contains_item(table, "five", 1));
    assert(contains_item(table, "five", 5));

    assert(rm(table, "five", 5));
    assert(rm(table, "four", 4));
    assert(!rm(table, "three", 2));
    tbl_val *val = rm_key(table, "three");
    assert(*val == 3);
    free(val);
    assert(rm(table, "two", -2));
    assert(is_empty(table));

    put(table, "test", 0);
    put(table, "test2", -1);
    assert(!is_empty(table));
    // display(table);
    clear(table);
    assert(is_empty(table));
    // display(table);
    free(table);

    printf("Tests Passed!\n");
    return 0;
}
