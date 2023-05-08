# `C` Hash Table

Various implementations of a [Hash Table](https://en.wikipedia.org/wiki/Hash_table) in C.

## Implementations

- [Linear Linked List](#linear-linked-list)

### Linear Linked List

The hash table is represented as a single pointer to the first element. Every
element then contains a pointer to the next element. The last item is indicated
by a pointer to `null`.

Insertion is very quick, the item is pre-pended to the list. All searches must
occur in linear time, so these are generally slow.

## TODO

- Make a linked-list iterator
  - Get keys
  - Get values
  - Get mappings (key-value pairs)
