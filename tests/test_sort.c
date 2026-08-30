#include "cstructs/sort.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int cmp_int_desc(const void *a, const void *b) {
    return cmp_int(b, a);
}

static int cmp_str(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(void) {
    {
        int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        size_t n = 10;
        assert(sort_merge(arr, n, sizeof(int), cmp_int) == 0);
        assert(arr[0] == 1 && arr[1] == 1 && arr[2] == 2 && arr[3] == 3 && arr[4] == 3);
        assert(arr[5] == 4 && arr[6] == 5 && arr[7] == 5 && arr[8] == 6 && arr[9] == 9);
    }

    {
        int arr[] = {5, 2, 8, 1, 9, 3};
        size_t n = 6;
        assert(sort_merge(arr, n, sizeof(int), cmp_int_desc) == 0);
        assert(arr[0] == 9 && arr[1] == 8 && arr[2] == 5 && arr[3] == 3 && arr[4] == 2 && arr[5] == 1);
    }

    {
        int arr[] = {};
        assert(sort_merge(arr, 0, sizeof(int), cmp_int) == 0);
    }

    {
        int arr[] = {42};
        assert(sort_merge(arr, 1, sizeof(int), cmp_int) == 0);
        assert(arr[0] == 42);
    }

    {
        int arr[] = {1, 2, 3, 4, 5};
        size_t n = 5;
        assert(sort_merge(arr, n, sizeof(int), cmp_int) == 0);
        assert(arr[0] == 1 && arr[1] == 2 && arr[2] == 3 && arr[3] == 4 && arr[4] == 5);
    }

    {
        int arr[] = {5, 4, 3, 2, 1};
        size_t n = 5;
        assert(sort_merge(arr, n, sizeof(int), cmp_int) == 0);
        assert(arr[0] == 1 && arr[1] == 2 && arr[2] == 3 && arr[3] == 4 && arr[4] == 5);
    }

    {
        char strs[4][10] = {"dog", "cat", "bird", "apple"};
        size_t n = 4;
        assert(sort_merge(strs, n, 10, cmp_str) == 0);
        assert(strcmp(strs[0], "apple") == 0);
        assert(strcmp(strs[1], "bird") == 0);
        assert(strcmp(strs[2], "cat") == 0);
        assert(strcmp(strs[3], "dog") == 0);
    }

    {
        int arr[] = {1, 3, 5, 7, 9};
        size_t n = 5;
        size_t idx;
        assert(sort_bsearch(arr, n, sizeof(int), &(int){5}, cmp_int, &idx) == 1);
        assert(idx == 2);
    }

    {
        int arr[] = {1, 3, 5, 7, 9};
        size_t n = 5;
        size_t idx;
        assert(sort_bsearch(arr, n, sizeof(int), &(int){4}, cmp_int, &idx) == 0);
        assert(idx == 2);
    }

    {
        int arr[] = {1, 3, 5, 7, 9};
        size_t n = 5;
        size_t idx;
        assert(sort_bsearch(arr, n, sizeof(int), &(int){0}, cmp_int, &idx) == 0);
        assert(idx == 0);
    }

    {
        int arr[] = {1, 3, 5, 7, 9};
        size_t n = 5;
        size_t idx;
        assert(sort_bsearch(arr, n, sizeof(int), &(int){10}, cmp_int, &idx) == 0);
        assert(idx == 5);
    }

    {
        int arr[] = {};
        size_t idx;
        assert(sort_bsearch(arr, 0, sizeof(int), &(int){5}, cmp_int, &idx) == 0);
        assert(idx == 0);
    }

    {
        int arr[] = {1};
        size_t idx;
        assert(sort_bsearch(arr, 1, sizeof(int), &(int){1}, cmp_int, &idx) == 1);
        assert(idx == 0);
    }

    {
        int arr[] = {1};
        size_t idx;
        assert(sort_bsearch(arr, 1, sizeof(int), &(int){2}, cmp_int, &idx) == 0);
        assert(idx == 1);
    }

    printf("test_sort: ok\n");
    return 0;
}
