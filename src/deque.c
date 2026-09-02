#include <cstructs/deque.h>
#include <stdlib.h>
#include <string.h>

void deque_init(deque *d, size_t elem_size) {
    d->data = NULL;
    d->elem_size = elem_size;
    d->len = 0;
    d->cap = 0;
    d->front = 0;
}

static int deque_grow(deque *d) {
    size_t new_cap = d->cap == 0 ? 8 : d->cap * 2;
    unsigned char *new_data = malloc(new_cap * d->elem_size);
    if (!new_data)
        return -1;

    if (d->len > 0) {
        size_t first_part = d->cap - d->front;
        if (d->len <= first_part) {
            memcpy(new_data, d->data + d->front * d->elem_size, d->len * d->elem_size);
        } else {
            memcpy(new_data, d->data + d->front * d->elem_size, first_part * d->elem_size);
            memcpy(new_data + first_part * d->elem_size, d->data,
                   (d->len - first_part) * d->elem_size);
        }
    }

    free(d->data);
    d->data = new_data;
    d->cap = new_cap;
    d->front = 0;
    return 0;
}

int deque_push_front(deque *d, const void *elem) {
    if (d->len == d->cap && deque_grow(d) == -1)
        return -1;

    d->front = (d->front + d->cap - 1) % d->cap;
    memcpy(d->data + d->front * d->elem_size, elem, d->elem_size);
    d->len++;
    return 0;
}

int deque_push_back(deque *d, const void *elem) {
    if (d->len == d->cap && deque_grow(d) == -1)
        return -1;

    size_t back_idx = (d->front + d->len) % d->cap;
    memcpy(d->data + back_idx * d->elem_size, elem, d->elem_size);
    d->len++;
    return 0;
}

void deque_pop_front(deque *d, void *out) {
    memcpy(out, d->data + d->front * d->elem_size, d->elem_size);
    d->front = (d->front + 1) % d->cap;
    d->len--;
}

void deque_pop_back(deque *d, void *out) {
    size_t back_idx = (d->front + d->len - 1) % d->cap;
    memcpy(out, d->data + back_idx * d->elem_size, d->elem_size);
    d->len--;
}

void *deque_at(const deque *d, size_t i) {
    size_t idx = (d->front + i) % d->cap;
    return d->data + idx * d->elem_size;
}

size_t deque_len(const deque *d) { return d->len; }

void deque_free(deque *d) {
    free(d->data);
    d->data = NULL;
    d->len = 0;
    d->cap = 0;
    d->front = 0;
}
