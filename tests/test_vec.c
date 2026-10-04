#include "cstructs/vec.h"

#include <assert.h>
#include <stdio.h>

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

    printf("test_vec: ok\n");
    return 0;
}
