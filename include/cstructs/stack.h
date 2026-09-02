#ifndef CSTRUCTS_STACK_H
#define CSTRUCTS_STACK_H

#include <stddef.h>

/* A generic stack (LIFO) that stores fixed-size elements by value. */
typedef struct {
    unsigned char *data;
    size_t elem_size;
    size_t len;
    size_t cap;
} stack;

/* Initialise an empty stack for elements of `elem_size` bytes. */
void stack_init(stack *s, size_t elem_size);

/* Push a copy of `*elem` onto the stack. Returns 0 on success, -1 on allocation failure. */
int stack_push(stack *s, const void *elem);

/* Pop and return the top element into `*out`. Behaviour is undefined if `stack_len(s) == 0`. */
void stack_pop(stack *s, void *out);

/* Return a pointer to the top element without removing it. Behaviour is undefined if `stack_len(s)
 * == 0`. */
void *stack_top(const stack *s);

/* Number of elements currently stored. */
size_t stack_len(const stack *s);

/* Free the stack's storage and reset it to the empty state. */
void stack_free(stack *s);

#endif /* CSTRUCTS_STACK_H */
