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

    printf("test_vec: ok\n");
    return 0;
}
