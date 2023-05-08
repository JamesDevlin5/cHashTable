#include "tbl.h"

/*
 * Each node contains a mapping and a link to the next node in the list
 */
struct list_node {
    tbl_key key;
    tbl_val val;
    struct list_node *next;
};

struct hash_tbl {
    struct list_node *head;
};

struct hash_tbl *new(void) {
    struct hash_tbl *tbl = malloc(sizeof(struct hash_tbl));
    tbl->head = NULL;
    return tbl;
}

bool is_empty(struct hash_tbl *table) {
    return table->head == NULL;
}

int size(struct hash_tbl *table) {
    int count = 0;
    struct list_node *node = table->head;
    while (node) {
        count += 1;
        node = node->next;
    }
    return count;
}

void clear(struct hash_tbl *table) {
    struct list_node *curr = table->head;
    struct list_node *next = NULL;
    while (curr) {
        next = curr->next;
        free(curr->key);
        // NOTE: mapping's value is not freed
        // free(curr->val);
        free(curr);
        curr = next;
    }
}

/* TODO
struct hash_tbl *clone(struct hash_tbl *source) {
    return NULL;
} */

bool contains_key(struct hash_tbl *table, tbl_key key) {
    return get(table, key) != NULL;
}

bool contains_item(struct hash_tbl *table, tbl_key key, tbl_val val) {
    tbl_val *item_val = get(table, key);
    if (item_val) {
        return *item_val == val;
    }
    return false;
}

/*
 * Performs a linear search, checking each element one-by-one
 */
tbl_val *get(struct hash_tbl *table, tbl_key key) {
    struct list_node *node = table->head;
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
 * Places new nodes at the beginning of the list
 */
void put(struct hash_tbl *table, tbl_key key, tbl_val val) {
    // TODO: check to see if the key is already in the table?
    struct list_node *node = malloc(sizeof(struct list_node));
    node->key = key;
    node->val = val;
    node->next = table->head;
    table->head = node;
}

tbl_val *rm_key(struct hash_tbl *table, tbl_key key) {
    /* TODO */
    return NULL;
}

bool rm(struct hash_tbl *table, tbl_key key, tbl_val val) {
    /* TODO */
    return false;
}
