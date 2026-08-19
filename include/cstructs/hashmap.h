#ifndef CSTRUCTS_HASHMAP_H
#define CSTRUCTS_HASHMAP_H

#include <stddef.h>

/* A hash map that stores fixed-size values by key (string). Uses open chaining for collisions. */
typedef struct hashmap_entry {
    char *key;
    unsigned char *value;
    struct hashmap_entry *next;
} hashmap_entry;

typedef struct {
    hashmap_entry **buckets;
    size_t buckets_count;
    size_t elem_size;
    size_t count;
} hashmap;

/* Initialise an empty hash map for values of `elem_size` bytes. */
void hashmap_init(hashmap *hm, size_t elem_size);

/* Insert or update a key-value pair. Returns 0 on success, -1 on allocation failure. */
int hashmap_set(hashmap *hm, const char *key, const void *value);

/* Retrieve the value for `key` into `out`. Returns 0 if found, -1 if not found. */
int hashmap_get(const hashmap *hm, const char *key, void *out);

/* Delete the entry for `key`. Returns 0 if found and deleted, -1 if not found. */
int hashmap_delete(hashmap *hm, const char *key);

/* Number of key-value pairs currently stored. */
size_t hashmap_len(const hashmap *hm);

/* Free the hash map's storage and reset it to the empty state. */
void hashmap_free(hashmap *hm);

#endif /* CSTRUCTS_HASHMAP_H */
