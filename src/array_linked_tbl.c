#include "tbl.h"
#include "utils.h"

static const size_t INIT_SIZE = 2;
static const float LOAD_AMT = 0.75f;

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

bool is_empty(struct hash_tbl *table) {
    return size(table) == 0;
}

size_t size(struct hash_tbl *table) {
    return table->n_items;
}

void clear(struct hash_tbl *table) {
    if (is_empty(table)) return;
    for (size_t i = 0; i < table->n_buckets; i++) {
        free_list((*table->buckets)[i]);
    }
    // free(table->buckets);
    // TODO: shrink to orig size?
}

bool contains_key(struct hash_tbl *table, tbl_key key) {
    return std_contains_key(table, key);
}

bool contains_item(struct hash_tbl *table, tbl_key key, tbl_val val) {
    return std_contains_item(table, key, val);
}

tbl_val *get(struct hash_tbl *table, tbl_key key) {
    /* TODO */
    return NULL;
}

void put(struct hash_tbl *table, tbl_key key, tbl_val val) {
    /* TODO */
}

tbl_val *rm_key(struct hash_tbl *table, tbl_key key) {
    /* TODO */
    return NULL;
}

bool rm(struct hash_tbl *table, tbl_key key, tbl_val val) {
    /* TODO */
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
            }
            printf("\n");
        } else {
            printf("  <empty>\n");
        }
    }
    printf("\n");
}
