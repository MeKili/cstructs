#include "cstructs/stack.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    stack s;
    stack_init(&s, sizeof(int));
    assert(stack_len(&s) == 0);

    /* Push elements and verify top. */
    for (int i = 0; i < 50; i++) {
        assert(stack_push(&s, &i) == 0);
        assert(stack_len(&s) == (size_t)(i + 1));
        assert(*(int *)stack_top(&s) == i);
    }

    /* Pop all elements and verify LIFO order. */
    for (int i = 49; i >= 0; i--) {
        int val;
        assert(*(int *)stack_top(&s) == i);
        stack_pop(&s, &val);
        assert(val == i);
        assert(stack_len(&s) == (size_t)i);
    }
    assert(stack_len(&s) == 0);

    /* Test with larger elements (structs). */
    struct pair {
        int x;
        int y;
    } p;

    stack s2;
    stack_init(&s2, sizeof(struct pair));

    for (int i = 0; i < 20; i++) {
        p.x = i;
        p.y = i * 2;
        assert(stack_push(&s2, &p) == 0);
    }
    assert(stack_len(&s2) == 20);

    for (int i = 19; i >= 0; i--) {
        struct pair out;
        stack_pop(&s2, &out);
        assert(out.x == i);
        assert(out.y == i * 2);
    }

    stack_free(&s2);
    assert(stack_len(&s2) == 0);

    stack_free(&s);
    assert(stack_len(&s) == 0);

    printf("test_stack: ok\n");
    return 0;
}
