#include "cstructs/vec.h"

#include <assert.h>
#include <stdio.h>

static int cmp_int(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    return val_a - val_b;
}

int main(void) {
    vec v;
    vec_init(&v, sizeof(int));
    assert(vec_len(&v) == 0);

    for (int i = 0; i < 100; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(vec_len(&v) == 100);

    for (int i = 0; i < 100; i++) {
        assert(*(int *)vec_at(&v, (size_t)i) == i);
    }

    int popped;
    for (int i = 99; i >= 0; i--) {
        vec_pop(&v, &popped);
        assert(popped == i);
        assert(vec_len(&v) == (size_t)i);
    }

    /* Test clear and reuse. */
    for (int i = 0; i < 50; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(vec_len(&v) == 50);
    size_t cap_before_clear = vec_capacity(&v);
    vec_clear(&v);
    assert(vec_len(&v) == 0);
    assert(vec_capacity(&v) == cap_before_clear);

    /* After clear, can reuse without reallocation. */
    for (int i = 0; i < 50; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(vec_len(&v) == 50);

    vec_free(&v);
    assert(vec_len(&v) == 0);
    assert(vec_capacity(&v) == 0);

    /* Test vec_remove. */
    for (int i = 0; i < 10; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(vec_len(&v) == 10);

    /* Remove from middle: [0,1,2,3,4,5,6,7,8,9] -> [0,1,2,4,5,6,7,8,9] */
    assert(vec_remove(&v, 3) == 0);
    assert(vec_len(&v) == 9);
    assert(*(int *)vec_at(&v, 3) == 4);
    assert(*(int *)vec_at(&v, 4) == 5);

    /* Remove from start. */
    assert(vec_remove(&v, 0) == 0);
    assert(vec_len(&v) == 8);
    assert(*(int *)vec_at(&v, 0) == 1);

    /* Remove from end. */
    assert(vec_remove(&v, 7) == 0);
    assert(vec_len(&v) == 7);

    /* Test invalid remove. */
    assert(vec_remove(&v, 7) == -1);
    assert(vec_remove(&v, 100) == -1);
    assert(vec_len(&v) == 7);

    /* Remove all remaining elements. */
    for (int i = 0; i < 7; i++) {
        assert(vec_remove(&v, 0) == 0);
        assert(vec_len(&v) == (size_t)(6 - i));
    }

    vec_free(&v);

    /* Test vec_insert. */
    vec_init(&v, sizeof(int));

    /* Insert into empty vector. */
    int val = 10;
    assert(vec_insert(&v, 0, &val) == 0);
    assert(vec_len(&v) == 1);
    assert(*(int *)vec_at(&v, 0) == 10);

    /* Insert at beginning: [10] -> [5, 10] */
    val = 5;
    assert(vec_insert(&v, 0, &val) == 0);
    assert(vec_len(&v) == 2);
    assert(*(int *)vec_at(&v, 0) == 5);
    assert(*(int *)vec_at(&v, 1) == 10);

    /* Insert in middle: [5, 10] -> [5, 7, 10] */
    val = 7;
    assert(vec_insert(&v, 1, &val) == 0);
    assert(vec_len(&v) == 3);
    assert(*(int *)vec_at(&v, 0) == 5);
    assert(*(int *)vec_at(&v, 1) == 7);
    assert(*(int *)vec_at(&v, 2) == 10);

    /* Insert at end: [5, 7, 10] -> [5, 7, 10, 15] */
    val = 15;
    assert(vec_insert(&v, 3, &val) == 0);
    assert(vec_len(&v) == 4);
    assert(*(int *)vec_at(&v, 3) == 15);

    /* Insert multiple times to test reallocation. */
    for (int i = 0; i < 10; i++) {
        int x = 20 + i;
        assert(vec_insert(&v, vec_len(&v), &x) == 0);
    }
    assert(vec_len(&v) == 14);

    /* Test invalid insert. */
    assert(vec_insert(&v, 15, &val) == -1);
    assert(vec_insert(&v, 100, &val) == -1);
    assert(vec_len(&v) == 14);

    vec_free(&v);

    /* Test vec_first and vec_last. */
    vec_init(&v, sizeof(int));
    for (int i = 0; i < 10; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(*(int *)vec_first(&v) == 0);
    assert(*(int *)vec_last(&v) == 9);

    /* With single element. */
    vec_clear(&v);
    val = 42;
    assert(vec_push(&v, &val) == 0);
    assert(*(int *)vec_first(&v) == 42);
    assert(*(int *)vec_last(&v) == 42);

    /* After removal. */
    vec_remove(&v, 0);
    val = 5;
    assert(vec_push(&v, &val) == 0);
    val = 10;
    assert(vec_push(&v, &val) == 0);
    assert(*(int *)vec_first(&v) == 5);
    assert(*(int *)vec_last(&v) == 10);

    vec_free(&v);

    /* Test vec_reverse. */
    vec_init(&v, sizeof(int));
    for (int i = 0; i < 5; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    vec_reverse(&v);
    assert(vec_len(&v) == 5);
    assert(*(int *)vec_at(&v, 0) == 4);
    assert(*(int *)vec_at(&v, 1) == 3);
    assert(*(int *)vec_at(&v, 2) == 2);
    assert(*(int *)vec_at(&v, 3) == 1);
    assert(*(int *)vec_at(&v, 4) == 0);

    /* Reverse again should restore original order. */
    vec_reverse(&v);
    assert(*(int *)vec_at(&v, 0) == 0);
    assert(*(int *)vec_at(&v, 1) == 1);
    assert(*(int *)vec_at(&v, 2) == 2);
    assert(*(int *)vec_at(&v, 3) == 3);
    assert(*(int *)vec_at(&v, 4) == 4);

    /* Reverse single element. */
    vec_clear(&v);
    int single = 42;
    assert(vec_push(&v, &single) == 0);
    vec_reverse(&v);
    assert(*(int *)vec_at(&v, 0) == 42);

    /* Reverse empty vector. */
    vec_clear(&v);
    vec_reverse(&v);
    assert(vec_len(&v) == 0);

    vec_free(&v);

    /* Test vec_reserve. */
    vec_init(&v, sizeof(int));
    assert(vec_len(&v) == 0);
    assert(vec_capacity(&v) == 0);

    /* Reserve space for 50 elements. */
    assert(vec_reserve(&v, 50) == 0);
    assert(vec_capacity(&v) == 50);
    assert(vec_len(&v) == 0);

    /* Add elements without triggering reallocation. */
    size_t cap_after_reserve = vec_capacity(&v);
    for (int i = 0; i < 50; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(vec_len(&v) == 50);
    assert(vec_capacity(&v) == cap_after_reserve);

    /* Reserve with smaller capacity is no-op. */
    assert(vec_reserve(&v, 30) == 0);
    assert(vec_capacity(&v) == cap_after_reserve);

    /* Reserve with exact capacity is no-op. */
    assert(vec_reserve(&v, cap_after_reserve) == 0);
    assert(vec_capacity(&v) == cap_after_reserve);

    /* Add more elements to trigger growth. */
    int x = 50;
    assert(vec_push(&v, &x) == 0);
    assert(vec_len(&v) == 51);

    vec_free(&v);

    /* Test vec_shrink_to_fit. */
    vec_init(&v, sizeof(int));

    /* Push 10 elements, then remove 5. */
    for (int i = 0; i < 10; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(vec_len(&v) == 10);
    size_t cap_before = vec_capacity(&v);
    assert(cap_before >= 10);

    for (int i = 0; i < 5; i++) {
        int dummy;
        vec_pop(&v, &dummy);
    }
    assert(vec_len(&v) == 5);
    assert(vec_capacity(&v) == cap_before); /* Capacity unchanged. */

    /* Shrink to fit. */
    assert(vec_shrink_to_fit(&v) == 0);
    assert(vec_len(&v) == 5);
    assert(vec_capacity(&v) == 5);

    /* Verify remaining elements are intact. */
    for (int i = 0; i < 5; i++) {
        assert(*(int *)vec_at(&v, i) == i);
    }

    /* Shrink when already fit (no-op). */
    assert(vec_shrink_to_fit(&v) == 0);
    assert(vec_capacity(&v) == 5);

    vec_free(&v);

    /* Shrink empty vector. */
    vec_init(&v, sizeof(int));
    for (int i = 0; i < 20; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    vec_clear(&v);
    assert(vec_len(&v) == 0);
    assert(vec_capacity(&v) >= 20);
    assert(vec_shrink_to_fit(&v) == 0);
    assert(vec_len(&v) == 0);
    assert(vec_capacity(&v) == 0);

    vec_free(&v);

    /* Test vec_swap. */
    vec_init(&v, sizeof(int));
    for (int i = 0; i < 5; i++) {
        assert(vec_push(&v, &i) == 0);
    }
    assert(vec_len(&v) == 5);

    /* Swap two elements. */
    assert(vec_swap(&v, 0, 4) == 0);
    assert(*(int *)vec_at(&v, 0) == 4);
    assert(*(int *)vec_at(&v, 4) == 0);
    assert(*(int *)vec_at(&v, 1) == 1);
    assert(*(int *)vec_at(&v, 2) == 2);
    assert(*(int *)vec_at(&v, 3) == 3);

    /* Swap adjacent elements. */
    assert(vec_swap(&v, 1, 2) == 0);
    assert(*(int *)vec_at(&v, 1) == 2);
    assert(*(int *)vec_at(&v, 2) == 1);

    /* Swap same index (no-op). */
    assert(vec_swap(&v, 2, 2) == 0);
    assert(*(int *)vec_at(&v, 2) == 1);

    /* Invalid indices. */
    assert(vec_swap(&v, 0, 5) == -1);
    assert(vec_swap(&v, 5, 0) == -1);
    assert(vec_swap(&v, 5, 5) == -1);
    assert(vec_len(&v) == 5);

    /* Verify state is unchanged after failed swaps. */
    assert(*(int *)vec_at(&v, 0) == 4);
    assert(*(int *)vec_at(&v, 4) == 0);

    vec_free(&v);

    /* Test swap on single element. */
    vec_init(&v, sizeof(int));
    int elem = 99;
    assert(vec_push(&v, &elem) == 0);
    assert(vec_swap(&v, 0, 0) == 0);
    assert(*(int *)vec_at(&v, 0) == 99);

    vec_free(&v);

    /* Test vec_index_of. */
    vec_init(&v, sizeof(int));
    for (int i = 0; i < 10; i++) {
        assert(vec_push(&v, &i) == 0);
    }

    /* Find element in the middle. */
    int search_val = 5;
    assert(vec_index_of(&v, &search_val, cmp_int) == 5);

    /* Find first element. */
    search_val = 0;
    assert(vec_index_of(&v, &search_val, cmp_int) == 0);

    /* Find last element. */
    search_val = 9;
    assert(vec_index_of(&v, &search_val, cmp_int) == 9);

    /* Element not found. */
    search_val = 100;
    assert(vec_index_of(&v, &search_val, cmp_int) == (size_t)-1);

    /* Negative search value. */
    search_val = -5;
    assert(vec_index_of(&v, &search_val, cmp_int) == (size_t)-1);

    /* Test with duplicates (finds first). */
    vec_clear(&v);
    int vals[] = {1, 2, 3, 2, 4};
    for (int i = 0; i < 5; i++) {
        assert(vec_push(&v, &vals[i]) == 0);
    }
    search_val = 2;
    assert(vec_index_of(&v, &search_val, cmp_int) == 1);

    /* Test on empty vector. */
    vec_clear(&v);
    search_val = 0;
    assert(vec_index_of(&v, &search_val, cmp_int) == (size_t)-1);

    vec_free(&v);

    printf("test_vec: ok\n");
    return 0;
}
