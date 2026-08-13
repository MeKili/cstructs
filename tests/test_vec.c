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

    vec_free(&v);
    assert(vec_len(&v) == 0);

    printf("test_vec: ok\n");
    return 0;
}
