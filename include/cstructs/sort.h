#ifndef CSTRUCTS_SORT_H
#define CSTRUCTS_SORT_H

#include <stddef.h>

/* Merge sort: sorts arr in-place (allocates temporary space). */
/* Returns 0 on success, -1 on allocation failure. */
int sort_merge(void *arr, size_t n, size_t elem_size, int (*cmp)(const void *, const void *));

/* Binary search in a sorted array. */
/* Returns 1 if found and sets *out_idx to the index, 0 if not found. */
int sort_bsearch(const void *arr, size_t n, size_t elem_size, const void *key, int (*cmp)(const void *, const void *), size_t *out_idx);

#endif /* CSTRUCTS_SORT_H */
