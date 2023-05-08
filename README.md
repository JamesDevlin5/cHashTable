# `C` Hash Table

Various implementations of a [Hash Table](https://en.wikipedia.org/wiki/Hash_table) in C.

## Implementations

- [Linear Linked List](#linear-linked-list)
- [Array of Buckets](#array-list)

### Linear Linked List

The hash table is represented as a single pointer to the first element. Every
element then contains a pointer to the next element. The last item is indicated
by a pointer to `null`.

Insertion is *not* very quick; the item is pre-pended to the list but the list is first
searched to see if the key is already present. All searches must occur in linear time,
so these are generally slow.

> The `put` operation first executes a `get` operation

### Array List

The hash table is implemented as a dynamically-sized array. Each item in the
array is a *bucket*.

The keys are mapped, via a hash function, to an integer value. It is possible
that we may encounter a hash collision, where two keys hash to the same
value. We must still be able to insert both keys in this case, but care must be
taken to do it correctly. We have the following two options:

1. Each bucket may be a single key-value pairing, so we must search for a nearby
   empty bucket to use.
1. Each bucket may be a list of key-value pairings, in which case we may simply
   append the new item to this list.

## TODO

- Make a linked-list iterator
  - Get keys
  - Get values
  - Get mappings (key-value pairs)
- Search operations
  - Find key
  - Find value
