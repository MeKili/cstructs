#ifndef CSTRUCTS_VEC_H
#define CSTRUCTS_VEC_H

#include <stddef.h>

/* A generic dynamic array that stores fixed-size elements by value. */
typedef struct {
    unsigned char *data;
    size_t elem_size;
    size_t len;
    size_t cap;
} vec;

/* Initialise an empty vector for elements of `elem_size` bytes. */
void vec_init(vec *v, size_t elem_size);

/* Append a copy of `*elem` to the vector. Returns 0 on success, -1 on allocation failure. */
int vec_push(vec *v, const void *elem);

/* Return a pointer to element `i`. Behaviour is undefined if `i >= vec_len(v)`. */
void *vec_at(const vec *v, size_t i);

/* Number of elements currently stored. */
size_t vec_len(const vec *v);

/* Free the vector's storage and reset it to the empty state. */
void vec_free(vec *v);

#endif /* CSTRUCTS_VEC_H */
