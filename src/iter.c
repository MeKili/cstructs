#include "cstructs/iter.h"

#include <stdlib.h>
#include <string.h>

int iter_map(const void *src, size_t n, size_t elem_size, int (*transform)(const void *in, void *out), void **out_arr) {
    if (n == 0) {
        *out_arr = NULL;
        return 0;
    }

    unsigned char *result = (unsigned char *)malloc(n * elem_size);
    if (!result) {
        return -1;
    }

    const unsigned char *src_data = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++) {
        if (transform(src_data + i * elem_size, result + i * elem_size) != 0) {
            free(result);
            return -1;
        }
    }

    *out_arr = result;
    return 0;
}

int iter_filter(const void *src, size_t n, size_t elem_size, int (*predicate)(const void *elem), void **out_arr) {
    size_t count = 0;

    for (size_t i = 0; i < n; i++) {
        const unsigned char *elem = (const unsigned char *)src + i * elem_size;
        if (predicate(elem)) {
            count++;
        }
    }

    if (count == 0) {
        *out_arr = NULL;
        return 0;
    }

    unsigned char *result = (unsigned char *)malloc(count * elem_size);
    if (!result) {
        return -1;
    }

    size_t idx = 0;
    const unsigned char *src_data = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++) {
        const unsigned char *elem = src_data + i * elem_size;
        if (predicate(elem)) {
            memcpy(result + idx * elem_size, elem, elem_size);
            idx++;
        }
    }

    *out_arr = result;
    return (int)count;
}

int iter_foreach(const void *arr, size_t n, size_t elem_size, int (*func)(const void *elem)) {
    const unsigned char *data = (const unsigned char *)arr;
    for (size_t i = 0; i < n; i++) {
        if (func(data + i * elem_size) != 0) {
            return -1;
        }
    }
    return 0;
}
