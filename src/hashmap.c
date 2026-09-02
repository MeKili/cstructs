#include "../include/cstructs/hashmap.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUCKETS 16

/* Simple FNV-1a hash function. */
static size_t hash_key(const char *key) {
    size_t hash = 2166136261u;
    for (const unsigned char *p = (const unsigned char *)key; *p; p++) {
        hash ^= *p;
        hash *= 16777619u;
    }
    return hash;
}

/* Ensure buckets are allocated (lazy allocation). */
static int ensure_buckets(hashmap *hm) {
    if (hm->buckets)
        return 0;

    hm->buckets_count = INITIAL_BUCKETS;
    hm->buckets = calloc(INITIAL_BUCKETS, sizeof(hashmap_entry *));
    return hm->buckets ? 0 : -1;
}

void hashmap_init(hashmap *hm, size_t elem_size) {
    hm->buckets = NULL;
    hm->buckets_count = 0;
    hm->elem_size = elem_size;
    hm->count = 0;
}

int hashmap_set(hashmap *hm, const char *key, const void *value) {
    if (ensure_buckets(hm) != 0)
        return -1;

    size_t idx = hash_key(key) % hm->buckets_count;
    hashmap_entry *entry = hm->buckets[idx];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            memcpy(entry->value, value, hm->elem_size);
            return 0;
        }
        entry = entry->next;
    }

    /* Key not found, insert new entry. */
    entry = malloc(sizeof(hashmap_entry));
    if (!entry)
        return -1;

    entry->key = malloc(strlen(key) + 1);
    if (!entry->key) {
        free(entry);
        return -1;
    }

    entry->value = malloc(hm->elem_size);
    if (!entry->value) {
        free(entry->key);
        free(entry);
        return -1;
    }

    strcpy(entry->key, key);
    memcpy(entry->value, value, hm->elem_size);
    entry->next = hm->buckets[idx];
    hm->buckets[idx] = entry;
    hm->count++;

    return 0;
}

int hashmap_get(const hashmap *hm, const char *key, void *out) {
    if (!hm->buckets)
        return -1;

    size_t idx = hash_key(key) % hm->buckets_count;
    hashmap_entry *entry = hm->buckets[idx];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            memcpy(out, entry->value, hm->elem_size);
            return 0;
        }
        entry = entry->next;
    }

    return -1;
}

int hashmap_delete(hashmap *hm, const char *key) {
    if (!hm->buckets)
        return -1;

    size_t idx = hash_key(key) % hm->buckets_count;
    hashmap_entry *entry = hm->buckets[idx];
    hashmap_entry *prev = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                hm->buckets[idx] = entry->next;
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            hm->count--;
            return 0;
        }
        prev = entry;
        entry = entry->next;
    }

    return -1;
}

size_t hashmap_len(const hashmap *hm) { return hm->count; }

void hashmap_free(hashmap *hm) {
    if (!hm->buckets)
        return;

    for (size_t i = 0; i < hm->buckets_count; i++) {
        hashmap_entry *entry = hm->buckets[i];
        while (entry) {
            hashmap_entry *next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
    }

    free(hm->buckets);
    hm->buckets = NULL;
    hm->buckets_count = 0;
    hm->count = 0;
}
