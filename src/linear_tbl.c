#include "tbl.h"
#include "utils.h"

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

size_t size(struct hash_tbl *table) {
    size_t count = 0;
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
    return std_contains_key(table, key);
}

bool contains_item(struct hash_tbl *table, tbl_key key, tbl_val val) {
    return std_contains_item(table, key, val);
}

static bool same_key(tbl_key key1, tbl_key key2) {
    return strcmp(key1, key2) == 0;
}

/*
 * Performs a linear search, checking each element one-by-one
 */
tbl_val *get(struct hash_tbl *table, tbl_key key) {
    struct list_node *node = table->head;
    while (node) {
        if (same_key(node->key, key)) {
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
    // If key is already in list, update that value
    tbl_val *lookup_val = get(table, key);
    if (lookup_val) {
        *lookup_val = val;
    } else {
        // Otherwise make a new node to store the information
        struct list_node *node = malloc(sizeof(struct list_node));
        // Creates a copy of the key to store
        tbl_key new_key = malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(new_key, key);
        node->key = new_key;
        node->val = val;
        // Prepends new node
        node->next = table->head;
        table->head = node;
    }
}

/*
 * Checks if only the keys are identical
 */
static bool key_pred(tbl_key search_key, tbl_val search_val,
                     tbl_key cmp_key, tbl_val cmp_val) {
    return same_key(search_key, cmp_key);
}

/*
 * Checks if both the key and value are identical
 */
static bool item_pred(tbl_key search_key, tbl_val search_val,
                      tbl_key cmp_key, tbl_val cmp_val) {
    return same_key(search_key, cmp_key) && search_val == cmp_val;
}

/*
 * Searches the list and removes the first item that the predicate function returns true for
 */
static tbl_val *rm_pred(struct hash_tbl *table,
                        tbl_key search_key, tbl_val search_val,
                        bool (*pred)(tbl_key, tbl_val, tbl_key, tbl_val)) {
    if (is_empty(table)) {
        return NULL;
    } else if (pred(search_key, search_val, table->head->key,
                    table->head->val)) {
        // If it's the first key
        struct list_node *node = table->head;
        table->head = node->next;
        tbl_val *val = malloc(sizeof(tbl_val));
        *val = node->val;
        free_node(node);
        return val;
    } else {
        // Search list (not the first item)
        struct list_node *prev = table->head;
        struct list_node *curr = prev->next;
        while (curr) {
            if (pred(search_key, search_val, curr->key, curr->val)) {
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

tbl_val *rm_key(struct hash_tbl *table, tbl_key key) {
    return rm_pred(table, key, 0, key_pred);
}

bool rm(struct hash_tbl *table, tbl_key key, tbl_val val) {
    tbl_val *lookup_val = rm_pred(table, key, val, item_pred);
    if (lookup_val) {
        free(lookup_val);
        return true;
    }
    return false;
}

void display(struct hash_tbl *table) {
    printf("  > %ld items\n", size(table));
    int i = 1;
    struct list_node *curr = table->head;
    while (curr) {
        printf("%2d: \t%s  = %d\n", i, curr->key, curr->val);
        curr = curr->next;
        i += 1;
    }
    printf("\n");
}
