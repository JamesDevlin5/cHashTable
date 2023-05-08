#include "tbl.h"

/*
 * Each node contains a mapping and a link to the next node in the list
 */
struct list_node {
    tbl_key key;
    tbl_val val;
    struct list_node *next;
};

/*
 * Frees the node and it's contents (but not the next node)
 */
static void free_node(struct list_node *node) {
    free(node->key);
    free(node);
}

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
    table->head = NULL;
    while (curr) {
        next = curr->next;
        free_node(curr);
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
    // tbl_val *lookup_val = get(table, )
    // TODO: check to see if the key is already in the table?
    struct list_node *node = malloc(sizeof(struct list_node));
    /* Creates a copy of the key to store */
    tbl_key new_key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(new_key, key);
    node->key = new_key;
    node->val = val;
    node->next = table->head;
    table->head = node;
}

tbl_val *rm_key(struct hash_tbl *table, tbl_key key) {
    // Check if it's the first key
    if (is_empty(table)) {
        return NULL;
    } else if (strcmp(table->head->key, key) == 0) {
        struct list_node *node = table->head;
        table->head = node->next;
        tbl_val *val = malloc(sizeof(tbl_val));
        *val = node->val;
        free_node(node);
        return val;
    } else {
        struct list_node *prev = table->head;
        struct list_node *curr = prev->next;
        while (curr) {
            if (strcmp(curr->key, key) == 0) {
                prev->next = curr->next;
                tbl_val *val = malloc(sizeof(tbl_val));
                *val = curr->val;
                free_node(curr);
                return val;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return NULL;
}

bool rm(struct hash_tbl *table, tbl_key key, tbl_val val) {
    /* TODO */
    return false;
}
