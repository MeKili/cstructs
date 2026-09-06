#include "cstructs/iter.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int double_int(const void *in, void *out) {
    int val = *(const int *)in;
    *(int *)out = val * 2;
    return 0;
}

int is_even(const void *elem) {
    return (*(const int *)elem) % 2 == 0;
}

int count_func(const void *elem) {
    (void)elem;
    return 0;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = 5;
    size_t elem_size = sizeof(int);

    {
        void *mapped = NULL;
        assert(iter_map(arr, n, elem_size, double_int, &mapped) == 0);
        assert(mapped != NULL);

        int *result = (int *)mapped;
        assert(result[0] == 2);
        assert(result[1] == 4);
        assert(result[2] == 6);
        assert(result[3] == 8);
        assert(result[4] == 10);

        free(mapped);
    }

    {
        void *filtered = NULL;
        int count = iter_filter(arr, n, elem_size, is_even, &filtered);
        assert(count == 2);
        assert(filtered != NULL);

        int *result = (int *)filtered;
        assert(result[0] == 2);
        assert(result[1] == 4);

        free(filtered);
    }

    {
        void *empty_map = NULL;
        assert(iter_map(NULL, 0, elem_size, double_int, &empty_map) == 0);
        assert(empty_map == NULL);
    }

    {
        void *empty_filter = NULL;
        int count = iter_filter(NULL, 0, elem_size, is_even, &empty_filter);
        assert(count == 0);
        assert(empty_filter == NULL);
    }

    {
        assert(iter_foreach(arr, n, elem_size, count_func) == 0);
    }

    printf("test_iter: ok\n");
    return 0;
}
