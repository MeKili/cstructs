#include "../include/cstructs/list.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    /* Test empty list initialization. */
    {
        list l;
        list_init(&l, sizeof(int));
        assert(list_len(&l) == 0);
        list_free(&l);
    }

    /* Test append and length. */
    {
        list l;
        list_init(&l, sizeof(int));

        int val = 42;
        assert(list_append(&l, &val) == 0);
        assert(list_len(&l) == 1);

        val = 100;
        assert(list_append(&l, &val) == 0);
        assert(list_len(&l) == 2);

        list_free(&l);
    }

    /* Test prepend and access. */
    {
        list l;
        list_init(&l, sizeof(int));

        int val = 1;
        list_append(&l, &val);
        val = 2;
        list_append(&l, &val);
        val = 3;
        list_prepend(&l, &val);

        assert(list_len(&l) == 3);
        assert(*(int *)list_at(&l, 0) == 3);
        assert(*(int *)list_at(&l, 1) == 1);
        assert(*(int *)list_at(&l, 2) == 2);

        list_free(&l);
    }

    /* Test pop_front. */
    {
        list l;
        list_init(&l, sizeof(int));

        int vals[] = {10, 20, 30};
        for (int i = 0; i < 3; i++) {
            list_append(&l, &vals[i]);
        }

        int out;
        list_pop_front(&l, &out);
        assert(out == 10);
        assert(list_len(&l) == 2);

        list_pop_front(&l, &out);
        assert(out == 20);
        assert(list_len(&l) == 1);

        list_pop_front(&l, &out);
        assert(out == 30);
        assert(list_len(&l) == 0);

        list_free(&l);
    }

    /* Test with struct elements. */
    {
        typedef struct {
            int x;
            int y;
        } point;

        list l;
        list_init(&l, sizeof(point));

        point p1 = {1, 2};
        point p2 = {3, 4};
        point p3 = {5, 6};

        list_append(&l, &p1);
        list_append(&l, &p2);
        list_prepend(&l, &p3);

        assert(list_len(&l) == 3);

        point *pt = (point *)list_at(&l, 0);
        assert(pt->x == 5 && pt->y == 6);

        pt = (point *)list_at(&l, 1);
        assert(pt->x == 1 && pt->y == 2);

        pt = (point *)list_at(&l, 2);
        assert(pt->x == 3 && pt->y == 4);

        list_free(&l);
    }

    /* Test free resets. */
    {
        list l;
        list_init(&l, sizeof(int));

        int val = 99;
        list_append(&l, &val);
        assert(list_len(&l) == 1);

        list_free(&l);
        assert(list_len(&l) == 0);

        /* Can reuse after free. */
        val = 77;
        list_append(&l, &val);
        assert(list_len(&l) == 1);
        assert(*(int *)list_at(&l, 0) == 77);

        list_free(&l);
    }

    printf("test_list: ok\n");
    return 0;
}
