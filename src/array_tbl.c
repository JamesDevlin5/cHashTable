#include "tbl.h"
#include "utils.h"

static const size_t INIT_SIZE = 2;
static const float LOAD_AMT = 0.75f;

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

static size_t hash(tbl_key key) {
    size_t counter = 1;
    char *c = key;
    while (*c) {
        counter += *c;
        c += 1;
    }
    return counter;
}

tbl_val *get(struct hash_tbl *table, tbl_key key) {
    size_t start_idx = hash(key);
    for (size_t idx = start_idx; idx < start_idx + table->n_buckets; idx++) {
        size_t curr_idx = idx % table->n_buckets;
        struct bucket *curr_bucket = (*table->buckets)[curr_idx];
        if (curr_bucket) {
            if (strcmp(curr_bucket->key, key) == 0) {
                // Found the key
                return &curr_bucket->val;
            }
        }
    }
    return NULL;
}

static bool should_grow(struct hash_tbl *table) {
    return (table->n_items / (float)table->n_buckets) >= LOAD_AMT;
}

void put(struct hash_tbl *table, tbl_key key, tbl_val val) {
    // Check if key already present
    tbl_val *lookup_val = get(table, key);
    if (lookup_val) {
        *lookup_val = val;
    } else {
        table->n_items += 1;
        if (should_grow(table)) {
            // Grow the table
            size_t new_size = table->n_buckets * 2;
            // Copy all current values into resized table
            struct hash_tbl *new_tbl = with_size(new_size);
            for (size_t i = 0; i < table->n_buckets; i++) {
                struct bucket *curr_bucket = (*table->buckets)[i];
                if (curr_bucket) {
                    put(new_tbl, curr_bucket->key, curr_bucket->val);
                    free(curr_bucket->key);
                    free(curr_bucket);
                }
            }
            free(table->buckets);
            table->buckets = new_tbl->buckets;
            table->n_buckets = new_tbl->n_buckets;
            // Account for new item
            table->n_items = new_tbl->n_items + 1;
            free(new_tbl);
        }
        // Create new bucket
        struct bucket *new_bucket = malloc(sizeof(struct bucket));
        new_bucket->key = malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(new_bucket->key, key);
        new_bucket->val = val;
        size_t start_idx = hash(key);
        for (size_t idx = start_idx; idx < start_idx + table->n_buckets; idx++) {
            size_t curr_idx = idx % table->n_buckets;
            // Check if null
            if (!(*table->buckets)[curr_idx]) {
                (*table->buckets)[curr_idx] = new_bucket;
                // Exit loop
                return;
            }
        }
    }
}

tbl_val *rm_key(struct hash_tbl *table, tbl_key key) {
    size_t start_idx = hash(key);
    for (size_t idx = start_idx; idx < start_idx + table->n_buckets; idx++) {
        size_t curr_idx = idx % table->n_buckets;
        struct bucket *curr_bucket = (*table->buckets)[curr_idx];
        if (curr_bucket) {
            if (strcmp(curr_bucket->key, key) == 0) {
                // Found the key
                tbl_val *val = malloc(sizeof(tbl_val));
                *val = curr_bucket->val;
                free(curr_bucket->key);
                free(curr_bucket);
                (*table->buckets)[curr_idx] = NULL;
                table->n_items -= 1;
                // TODO: check if we should shrink
                return val;
            }
        }
    }
    return NULL;
}

bool rm(struct hash_tbl *table, tbl_key key, tbl_val val) {
    size_t start_idx = hash(key);
    for (size_t idx = start_idx; idx < start_idx + table->n_buckets; idx++) {
        size_t curr_idx = idx % table->n_buckets;
        struct bucket *curr_bucket = (*table->buckets)[curr_idx];
        if (curr_bucket) {
            if (strcmp(curr_bucket->key, key) == 0 && val == curr_bucket->val) {
                // Found the pair
                free(curr_bucket->key);
                free(curr_bucket);
                (*table->buckets)[curr_idx] = NULL;
                table->n_items -= 1;
                // TODO: check if we should shrink
                return true;
            }
        }
    }
    return false;
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
