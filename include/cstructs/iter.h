#ifndef CSTRUCTS_ITER_H
#define CSTRUCTS_ITER_H

#include <stddef.h>

/* Iterator helpers for generic containers. */

/* Apply a transformation function to each element of an array, producing a new array.
 * Returns 0 on success, -1 on allocation failure or transform function error.
 * The transform function should return 0 on success, -1 on error. */
int iter_map(const void *src, size_t n, size_t elem_size, int (*transform)(const void *in, void *out), void **out_arr);

/* Filter elements of an array based on a predicate function, producing a new array.
 * Returns the count of elements in the new array on success, or -1 on allocation failure.
 * The predicate function should return non-zero (true) to include an element. */
int iter_filter(const void *src, size_t n, size_t elem_size, int (*predicate)(const void *elem), void **out_arr);

/* Apply a function to each element for side effects (e.g., printing).
 * Returns 0 on success, -1 if the function returns -1 for any element. */
int iter_foreach(const void *arr, size_t n, size_t elem_size, int (*func)(const void *elem));

#endif /* CSTRUCTS_ITER_H */
