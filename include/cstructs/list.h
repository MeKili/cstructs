#ifndef CSTRUCTS_LIST_H
#define CSTRUCTS_LIST_H

#include <stddef.h>

/* A generic singly-linked list that stores fixed-size elements by value. */
typedef struct list_node {
    unsigned char *data;
    struct list_node *next;
} list_node;

typedef struct {
    list_node *head;
    size_t elem_size;
    size_t len;
} list;

/* Initialise an empty list for elements of `elem_size` bytes. */
void list_init(list *l, size_t elem_size);

/* Prepend a copy of `*elem` to the front of the list. Returns 0 on success, -1 on allocation
 * failure. */
int list_prepend(list *l, const void *elem);

/* Append a copy of `*elem` to the back of the list. Returns 0 on success, -1 on allocation failure.
 */
int list_append(list *l, const void *elem);

/* Remove and return the first element. Behaviour is undefined if `list_len(l) == 0`. */
void list_pop_front(list *l, void *out);

/* Return a pointer to element `i`. Behaviour is undefined if `i >= list_len(l)`. */
void *list_at(const list *l, size_t i);

/* Number of elements currently stored. */
size_t list_len(const list *l);

/* Free the list's storage and reset it to the empty state. */
void list_free(list *l);

#endif /* CSTRUCTS_LIST_H */
