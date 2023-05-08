#include <assert.h>
#include <stdio.h>

#include "tbl.h"

int main(void) {
    struct hash_tbl *table = new();

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

    put(table, "a", 'a');
    put(table, "b", 'b');
    put(table, "c", 'c');
    put(table, "d", 'd');
    put(table, "e", 'e');
    put(table, "f", 'f');
    put(table, "g", 'g');
    put(table, "h", 'h');
    put(table, "i", 'i');
    put(table, "j", 'j');
    put(table, "k", 'k');
    put(table, "l", 'l');
    put(table, "m", 'm');
    put(table, "n", 'n');
    put(table, "o", 'o');
    put(table, "p", 'p');
    put(table, "q", 'q');
    put(table, "r", 'r');
    put(table, "s", 's');
    put(table, "t", 't');
    put(table, "u", 'u');
    put(table, "v", 'v');
    put(table, "w", 'w');
    put(table, "x", 'x');
    put(table, "y", 'y');
    put(table, "z", 'z');
    put(table, "A", 'A');
    put(table, "B", 'B');
    put(table, "C", 'C');
    put(table, "D", 'D');
    put(table, "E", 'E');
    put(table, "F", 'F');
    put(table, "G", 'G');
    put(table, "H", 'H');
    put(table, "I", 'I');
    put(table, "J", 'J');
    put(table, "K", 'K');
    put(table, "L", 'L');
    put(table, "M", 'M');
    put(table, "N", 'N');
    put(table, "O", 'O');
    put(table, "P", 'P');
    put(table, "Q", 'Q');
    put(table, "R", 'R');
    put(table, "S", 'S');
    put(table, "T", 'T');
    put(table, "U", 'U');
    put(table, "V", 'V');
    put(table, "W", 'W');
    put(table, "X", 'X');
    put(table, "Y", 'Y');
    put(table, "Z", 'Z');

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
    assert(size(table) == 56);

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
    clear(table);
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
