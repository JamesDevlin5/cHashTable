#include "tbl.h"
#include "utils.h"

static const size_t INIT_SIZE = 16;
static const float GROW_AMT = 0.75f;
static const float SHRINK_AMT = 1 - GROW_AMT;

/*
 * Linked-list node containing the key-value pairing and a ptr to the next item
 */
struct list_node {
    tbl_key key;
    tbl_val val;
    struct list_node *next;
};

struct hash_tbl {
    struct list_node *(*buckets)[];
    size_t n_buckets;
    size_t n_items;
};

/*
 * Frees the node and it's contents (but not the next node)
 */
static void free_node(struct list_node *node) {
    free(node->key);
    free(node);
}

/*
 * Frees a single linked-bucket
 */
static void free_list(struct list_node *list) {
    struct list_node *tmp;
    while (list) {
        tmp = list->next;
        free_node(list);
        list = tmp;
    }
}

struct hash_tbl *new(void) {
    struct hash_tbl *table = malloc(sizeof(struct hash_tbl));
    table->buckets = malloc(sizeof(struct list_node *) * INIT_SIZE);
    for (size_t i = 0; i < INIT_SIZE; i++) {
        (*table->buckets)[i] = NULL;
    }
    table->n_buckets = INIT_SIZE;
    table->n_items = 0;
    return table;
}

bool is_empty(struct hash_tbl *table) { return size(table) == 0; }

size_t size(struct hash_tbl *table) { return table->n_items; }

void clear(struct hash_tbl *table) {
    if (is_empty(table)) return;
    for (size_t i = 0; i < table->n_buckets; i++) {
        free_list((*table->buckets)[i]);
        (*table->buckets)[i] = NULL;
    }
    table->n_items = 0;
    // free(table->buckets);
    // TODO: shrink to orig size?
}

bool contains_key(struct hash_tbl *table, tbl_key key) {
    return std_contains_key(table, key);
}

bool contains_item(struct hash_tbl *table, tbl_key key, tbl_val val) {
    return std_contains_item(table, key, val);
}

static struct list_node *get_bucket(struct hash_tbl *table, tbl_key key) {
    size_t idx = hash(key) % table->n_buckets;
    return (*table->buckets)[idx];
}

tbl_val *get(struct hash_tbl *table, tbl_key key) {
    struct list_node *node = get_bucket(table, key);
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return &node->val;
        } else {
            node = node->next;
        }
    }
    return NULL;
}

/*
 * Resizes the table, to be a greater/smaller number of buckets
 */
static void resize(struct hash_tbl *table, size_t n_buckets) {
    /* TODO */
}

/*
 * Checks if the table has reached the threshold to grow in size,
 * and executes the resize operation if it is deemed necessary.
 */
static void maybe_grow(struct hash_tbl *table) {
    if ((table->n_items / (float) table->n_buckets) >= GROW_AMT) {
        resize(table, table->n_buckets * 2);
    }
}

/*
 * Checks if the table has reached the threshold to shrink in size,
 * and executes the resize operation if it is deemed necessary.
 */
static void maybe_shrink(struct hash_tbl *table) {
    if ((table->n_items / (float) table->n_buckets) <= SHRINK_AMT) {
        resize(table, table->n_buckets / 2);
    }
}

void put(struct hash_tbl *table, tbl_key key, tbl_val val) {
    tbl_val *lookup_val = get(table, key);
    if (lookup_val) {
        // key already in table
        *lookup_val = val;
    } else {
        size_t idx = hash(key) % table->n_buckets;
        struct list_node *node = malloc(sizeof(struct list_node));
        node->key = malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(node->key, key);
        node->val = val;
        // prepend new node
        node->next = (*table->buckets)[idx];
        (*table->buckets)[idx] = node;
        table->n_items += 1;
        maybe_grow(table);
    }
}

tbl_val *rm_key(struct hash_tbl *table, tbl_key key) {
    size_t idx = hash(key) % table->n_buckets;
    struct list_node *curr = (*table->buckets)[idx];
    if (!curr) {
        // Bucket is empty
        return NULL;
    } else if (strcmp(curr->key, key) == 0) {
        // Head has key
        tbl_val *lookup_val = malloc(sizeof(tbl_val));
        *lookup_val = curr->val;
        struct list_node *tmp = curr->next;
        free_node(curr);
        (*table->buckets)[idx] = tmp;
        table->n_items -= 1;
        // check if we should shrink
        maybe_shrink(table);
        return lookup_val;
    } else {
        // Check if body has key
        struct list_node *prev = curr;
        curr = curr->next;
        while (curr) {
            if (strcmp(curr->key, key) == 0) {
                tbl_val *lookup_val = malloc(sizeof(tbl_val));
                *lookup_val = curr->val;
                prev->next = curr->next;
                free_node(curr);
                table->n_items -= 1;
                // check if we should shrink
                maybe_shrink(table);
                return lookup_val;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return NULL;
}

bool rm(struct hash_tbl *table, tbl_key key, tbl_val val) {
    size_t idx = hash(key) % table->n_buckets;
    struct list_node *curr = (*table->buckets)[idx];
    if (!curr) {
        // Bucket is empty
        return false;
    } else if (strcmp(curr->key, key) == 0 && curr->val == val) {
        // Head has target
        struct list_node *tmp = curr->next;
        free_node(curr);
        (*table->buckets)[idx] = tmp;
        table->n_items -= 1;
        // check if we should shrink
        maybe_shrink(table);
        return true;
    } else {
        // Check if body has key
        struct list_node *prev = curr;
        curr = curr->next;
        while (curr) {
            if (strcmp(curr->key, key) == 0 && curr->val == val) {
                prev->next = curr->next;
                free_node(curr);
                table->n_items -= 1;
                // check if we should shrink
                maybe_shrink(table);
                return true;
            } else {
                curr = curr->next;
            }
        }
    }
    return false;
}

void display(struct hash_tbl *table) {
    printf("  > %ld items  //  %ld capacity\n", size(table), table->n_buckets);
    for (size_t i = 0; i < table->n_buckets; i++) {
        printf("%2ld: \t", i);
        struct list_node *bucket = (*table->buckets)[i];
        if (bucket) {
            printf("%s  =  %d", bucket->key, bucket->val);
            struct list_node *curr = bucket->next;
            while (curr) {
                printf(",\t%s  =  %d", curr->key, curr->val);
                curr = curr->next;
            }
            printf("\n");
        } else {
            printf("  <empty>\n");
        }
    }
    printf("\n");
}
