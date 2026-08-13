#include "cstructs/vec.h"

#include <stdlib.h>
#include <string.h>

void vec_init(vec *v, size_t elem_size) {
    v->data = NULL;
    v->elem_size = elem_size;
    v->len = 0;
    v->cap = 0;
}

int vec_push(vec *v, const void *elem) {
    if (v->len == v->cap) {
        size_t new_cap = v->cap == 0 ? 4 : v->cap * 2;
        unsigned char *new_data = realloc(v->data, new_cap * v->elem_size);
        if (new_data == NULL) {
            return -1;
        }
        v->data = new_data;
        v->cap = new_cap;
    }
    memcpy(v->data + v->len * v->elem_size, elem, v->elem_size);
    v->len++;
    return 0;
}

void *vec_at(const vec *v, size_t i) {
    return v->data + i * v->elem_size;
}

size_t vec_len(const vec *v) {
    return v->len;
}

void vec_free(vec *v) {
    free(v->data);
    v->data = NULL;
    v->len = 0;
    v->cap = 0;
}
