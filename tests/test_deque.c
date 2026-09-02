#include <assert.h>
#include <cstructs/deque.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    deque d;
    deque_init(&d, sizeof(int));

    assert(deque_len(&d) == 0);

    int x = 42;
    deque_push_back(&d, &x);
    assert(deque_len(&d) == 1);
    assert(*(int *)deque_at(&d, 0) == 42);

    x = 10;
    deque_push_front(&d, &x);
    assert(deque_len(&d) == 2);
    assert(*(int *)deque_at(&d, 0) == 10);
    assert(*(int *)deque_at(&d, 1) == 42);

    x = 99;
    deque_push_back(&d, &x);
    assert(deque_len(&d) == 3);
    assert(*(int *)deque_at(&d, 2) == 99);

    int out;
    deque_pop_front(&d, &out);
    assert(out == 10);
    assert(deque_len(&d) == 2);
    assert(*(int *)deque_at(&d, 0) == 42);
    assert(*(int *)deque_at(&d, 1) == 99);

    deque_pop_back(&d, &out);
    assert(out == 99);
    assert(deque_len(&d) == 1);
    assert(*(int *)deque_at(&d, 0) == 42);

    deque_pop_front(&d, &out);
    assert(out == 42);
    assert(deque_len(&d) == 0);

    deque_free(&d);

    deque_init(&d, sizeof(int));
    for (int i = 0; i < 100; i++) {
        if (i % 2 == 0) {
            deque_push_back(&d, &i);
        } else {
            deque_push_front(&d, &i);
        }
    }

    assert(deque_len(&d) == 100);

    for (size_t i = 0; i < deque_len(&d); i++) {
        int *elem = (int *)deque_at(&d, i);
        assert(elem != NULL);
    }

    while (deque_len(&d) > 0) {
        deque_pop_back(&d, &out);
    }
    assert(deque_len(&d) == 0);

    deque_free(&d);

    deque_init(&d, sizeof(int));
    for (int i = 1; i <= 10; i++) {
        deque_push_back(&d, &i);
    }

    for (int i = 1; i <= 10; i++) {
        assert(*(int *)deque_at(&d, i - 1) == i);
    }

    for (int i = 0; i < 10; i++) {
        deque_pop_front(&d, &out);
        assert(out == i + 1);
    }

    deque_free(&d);

    deque_init(&d, sizeof(int));
    for (int i = 1; i <= 10; i++) {
        deque_push_front(&d, &i);
    }

    assert(*(int *)deque_at(&d, 0) == 10);
    assert(*(int *)deque_at(&d, 9) == 1);

    deque_free(&d);

    deque_init(&d, sizeof(double));
    double dx = 3.14;
    deque_push_back(&d, &dx);
    dx = 2.71;
    deque_push_front(&d, &dx);

    double dout;
    deque_pop_front(&d, &dout);
    assert(dout == 2.71);
    deque_pop_front(&d, &dout);
    assert(dout == 3.14);

    deque_free(&d);

    printf("test_deque: ok\n");
    return 0;
}
