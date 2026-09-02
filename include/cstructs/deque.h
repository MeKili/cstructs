#ifndef CSTRUCTS_DEQUE_H
#define CSTRUCTS_DEQUE_H

#include <stddef.h>

/* A generic double-ended queue (deque) for fixed-size elements. */
typedef struct {
    unsigned char *data;
    size_t elem_size;
    size_t len;
    size_t cap;
    size_t front;
} deque;

/* Initialize an empty deque for elements of `elem_size` bytes. */
void deque_init(deque *d, size_t elem_size);

/* Push a copy of `*elem` to the front. Returns 0 on success, -1 on allocation failure. */
int deque_push_front(deque *d, const void *elem);

/* Push a copy of `*elem` to the back. Returns 0 on success, -1 on allocation failure. */
int deque_push_back(deque *d, const void *elem);

/* Pop from the front into `*out`. Behaviour is undefined if `deque_len(d) == 0`. */
void deque_pop_front(deque *d, void *out);

/* Pop from the back into `*out`. Behaviour is undefined if `deque_len(d) == 0`. */
void deque_pop_back(deque *d, void *out);

/* Return a pointer to element at index `i`. Behaviour is undefined if `i >= deque_len(d)`. */
void *deque_at(const deque *d, size_t i);

/* Number of elements currently stored. */
size_t deque_len(const deque *d);

/* Free the deque's storage and reset it to the empty state. */
void deque_free(deque *d);

#endif /* CSTRUCTS_DEQUE_H */
