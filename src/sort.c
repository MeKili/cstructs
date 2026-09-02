#include "cstructs/sort.h"

#include <stdlib.h>
#include <string.h>

static void merge(void *arr, size_t left, size_t mid, size_t right, size_t elem_size,
                  unsigned char *tmp, int (*cmp)(const void *, const void *)) {
    unsigned char *a = (unsigned char *)arr;
    size_t i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (cmp(a + i * elem_size, a + j * elem_size) <= 0) {
            memcpy(tmp + k * elem_size, a + i * elem_size, elem_size);
            i++;
        } else {
            memcpy(tmp + k * elem_size, a + j * elem_size, elem_size);
            j++;
        }
        k++;
    }

    while (i <= mid) {
        memcpy(tmp + k * elem_size, a + i * elem_size, elem_size);
        i++;
        k++;
    }

    while (j <= right) {
        memcpy(tmp + k * elem_size, a + j * elem_size, elem_size);
        j++;
        k++;
    }

    memcpy(a + left * elem_size, tmp, (right - left + 1) * elem_size);
}

static int merge_sort_impl(void *arr, size_t left, size_t right, size_t elem_size,
                           unsigned char *tmp, int (*cmp)(const void *, const void *)) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        if (merge_sort_impl(arr, left, mid, elem_size, tmp, cmp) != 0)
            return -1;
        if (merge_sort_impl(arr, mid + 1, right, elem_size, tmp, cmp) != 0)
            return -1;
        merge(arr, left, mid, right, elem_size, tmp, cmp);
    }
    return 0;
}

int sort_merge(void *arr, size_t n, size_t elem_size, int (*cmp)(const void *, const void *)) {
    if (n <= 1)
        return 0;

    unsigned char *tmp = malloc(n * elem_size);
    if (tmp == NULL)
        return -1;

    int result = merge_sort_impl(arr, 0, n - 1, elem_size, tmp, cmp);
    free(tmp);
    return result;
}

int sort_bsearch(const void *arr, size_t n, size_t elem_size, const void *key,
                 int (*cmp)(const void *, const void *), size_t *out_idx) {
    const unsigned char *a = (const unsigned char *)arr;
    size_t left = 0, right = n;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        int cmp_result = cmp(a + mid * elem_size, key);
        if (cmp_result < 0) {
            left = mid + 1;
        } else if (cmp_result > 0) {
            right = mid;
        } else {
            *out_idx = mid;
            return 1;
        }
    }

    *out_idx = left;
    return 0;
}
