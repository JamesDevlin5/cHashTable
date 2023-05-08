#include "tbl.h"
#include "utils.h"

static const size_t INIT_SIZE = 16;

struct bucket {
    tbl_key key;
    tbl_val val;
};

struct hash_tbl {
    // Ptr to an Array of buckets
    struct bucket *(*buckets)[];
    size_t n_buckets;
    size_t n_items;
};

/*
 * Creates a new hash table with the specified number of buckets
 * > For resizing and creating anew
 */
static struct hash_tbl *with_size(size_t n_buckets) {
    struct hash_tbl *table = malloc(sizeof(struct hash_tbl));
    table->buckets = malloc(sizeof(struct bucket *) * n_buckets);
    for (size_t i = 0; i < n_buckets; i++) {
        (*table->buckets)[i] = NULL;
    }
    table->n_buckets = n_buckets;
    table->n_items = 0;
    return table;
}

struct hash_tbl *new(void) {
    return with_size(INIT_SIZE);
}

bool is_empty(struct hash_tbl *table) {
    return size(table) == 0;
}

size_t size(struct hash_tbl *table) {
    return table->n_items;
}

void clear(struct hash_tbl *table) {
    // if (table->n_items == 0) return;
    // Free all individual buckets
    for (size_t i = 0; i < table->n_buckets; i++) {
        struct bucket *bucket = (*table->buckets)[i];
        if (bucket) {
            free(bucket->key);
            free(bucket);
        }
    }
    // Free the table of buckets
    free(*table->buckets);
    // Just make a new table and take its contents
    struct hash_tbl *new_tbl = new ();
    table->buckets = new_tbl->buckets;
    table->n_buckets = new_tbl->n_buckets;
    table->n_items = new_tbl->n_items;
    // And clean up the new table we just created (but not its contents we took)
    free(new_tbl);
}

bool contains_key(struct hash_tbl *table, tbl_key key) {
    return std_contains_key(table, key);
}

bool contains_item(struct hash_tbl *table, tbl_key key, tbl_val val) {
    return std_contains_item(table, key, val);
}

tbl_val *get(struct hash_tbl *table, tbl_key key) {
    // TODO
}

void put(struct hash_tbl *table, tbl_key key, tbl_val val) {
    // TODO
}

tbl_val *rm_key(struct hash_tbl *table, tbl_key key) {
    // TODO
}

bool rm(struct hash_tbl *table, tbl_key key, tbl_val val) {
    // TODO
}

void display(struct hash_tbl *table) {
    printf("  > %ld items  //  %ld capacity\n", size(table), table->n_buckets);
    for (size_t i = 0; i < table->n_buckets; i++) {
        printf("%2ld: \t", i);
        struct bucket *bucket = (*table->buckets)[i];
        if (bucket) {
            printf("%s  \t=  %d\n", bucket->key, bucket->val);
        } else {
            printf("  <empty>\n");
        }
    }
    printf("\n");
}
