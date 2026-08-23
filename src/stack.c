#include "cstructs/stack.h"

#include <stdlib.h>
#include <string.h>

void stack_init(stack *s, size_t elem_size) {
    s->data = NULL;
    s->elem_size = elem_size;
    s->len = 0;
    s->cap = 0;
}

int stack_push(stack *s, const void *elem) {
    if (s->len == s->cap) {
        size_t new_cap = s->cap == 0 ? 4 : s->cap * 2;
        unsigned char *new_data = realloc(s->data, new_cap * s->elem_size);
        if (new_data == NULL) {
            return -1;
        }
        s->data = new_data;
        s->cap = new_cap;
    }
    memcpy(s->data + s->len * s->elem_size, elem, s->elem_size);
    s->len++;
    return 0;
}

void stack_pop(stack *s, void *out) {
    s->len--;
    memcpy(out, s->data + s->len * s->elem_size, s->elem_size);
}

void *stack_top(const stack *s) {
    return s->data + (s->len - 1) * s->elem_size;
}

size_t stack_len(const stack *s) {
    return s->len;
}

void stack_free(stack *s) {
    free(s->data);
    s->data = NULL;
    s->len = 0;
    s->cap = 0;
}
