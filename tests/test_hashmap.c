#include "../include/cstructs/hashmap.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Test empty hashmap initialization. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));
        assert(hashmap_len(&hm) == 0);
        hashmap_free(&hm);
    }

    /* Test set and get with integers. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        int val = 42;
        assert(hashmap_set(&hm, "answer", &val) == 0);
        assert(hashmap_len(&hm) == 1);

        int out = 0;
        assert(hashmap_get(&hm, "answer", &out) == 0);
        assert(out == 42);

        hashmap_free(&hm);
    }

    /* Test multiple keys. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        int vals[] = {1, 2, 3, 4, 5};
        const char *keys[] = {"a", "b", "c", "d", "e"};

        for (int i = 0; i < 5; i++) {
            assert(hashmap_set(&hm, keys[i], &vals[i]) == 0);
        }
        assert(hashmap_len(&hm) == 5);

        for (int i = 0; i < 5; i++) {
            int out = 0;
            assert(hashmap_get(&hm, keys[i], &out) == 0);
            assert(out == vals[i]);
        }

        hashmap_free(&hm);
    }

    /* Test update existing key. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        int val = 10;
        assert(hashmap_set(&hm, "key", &val) == 0);
        assert(hashmap_len(&hm) == 1);

        int out = 0;
        assert(hashmap_get(&hm, "key", &out) == 0);
        assert(out == 10);

        val = 20;
        assert(hashmap_set(&hm, "key", &val) == 0);
        assert(hashmap_len(&hm) == 1);

        out = 0;
        assert(hashmap_get(&hm, "key", &out) == 0);
        assert(out == 20);

        hashmap_free(&hm);
    }

    /* Test get non-existent key. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        int val = 99;
        hashmap_set(&hm, "exists", &val);

        int out = 0;
        assert(hashmap_get(&hm, "missing", &out) == -1);

        hashmap_free(&hm);
    }

    /* Test delete. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        int val = 100;
        hashmap_set(&hm, "key1", &val);
        val = 200;
        hashmap_set(&hm, "key2", &val);
        assert(hashmap_len(&hm) == 2);

        assert(hashmap_delete(&hm, "key1") == 0);
        assert(hashmap_len(&hm) == 1);

        int out = 0;
        assert(hashmap_get(&hm, "key1", &out) == -1);
        assert(hashmap_get(&hm, "key2", &out) == 0);
        assert(out == 200);

        hashmap_free(&hm);
    }

    /* Test delete non-existent key. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        assert(hashmap_delete(&hm, "missing") == -1);

        hashmap_free(&hm);
    }

    /* Test with struct values. */
    {
        typedef struct {
            int x;
            int y;
        } point;

        hashmap hm;
        hashmap_init(&hm, sizeof(point));

        point p1 = {1, 2};
        assert(hashmap_set(&hm, "p1", &p1) == 0);

        point p2 = {3, 4};
        assert(hashmap_set(&hm, "p2", &p2) == 0);

        point out = {0, 0};
        assert(hashmap_get(&hm, "p1", &out) == 0);
        assert(out.x == 1 && out.y == 2);

        out.x = 0;
        out.y = 0;
        assert(hashmap_get(&hm, "p2", &out) == 0);
        assert(out.x == 3 && out.y == 4);

        hashmap_free(&hm);
    }

    /* Test collision handling (multiple keys with potential hash collisions). */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        for (int i = 0; i < 32; i++) {
            char key[16];
            snprintf(key, sizeof(key), "key_%d", i);
            assert(hashmap_set(&hm, key, &i) == 0);
        }
        assert(hashmap_len(&hm) == 32);

        for (int i = 0; i < 32; i++) {
            char key[16];
            snprintf(key, sizeof(key), "key_%d", i);
            int out = 0;
            assert(hashmap_get(&hm, key, &out) == 0);
            assert(out == i);
        }

        hashmap_free(&hm);
    }

    /* Test free resets. */
    {
        hashmap hm;
        hashmap_init(&hm, sizeof(int));

        int val = 55;
        hashmap_set(&hm, "key", &val);
        assert(hashmap_len(&hm) == 1);

        hashmap_free(&hm);
        assert(hashmap_len(&hm) == 0);

        /* Can reuse after free. */
        val = 77;
        assert(hashmap_set(&hm, "new", &val) == 0);
        assert(hashmap_len(&hm) == 1);

        int out = 0;
        assert(hashmap_get(&hm, "new", &out) == 0);
        assert(out == 77);

        hashmap_free(&hm);
    }

    /* Test with longer keys and values. */
    {
        typedef struct {
            int id;
            char name[64];
        } record;

        hashmap hm;
        hashmap_init(&hm, sizeof(record));

        record r1 = {1, "Alice"};
        assert(hashmap_set(&hm, "user_alice_very_long_key", &r1) == 0);

        record r2 = {2, "Bob"};
        assert(hashmap_set(&hm, "user_bob_very_long_key", &r2) == 0);

        record out = {0, ""};
        assert(hashmap_get(&hm, "user_alice_very_long_key", &out) == 0);
        assert(out.id == 1);
        assert(strcmp(out.name, "Alice") == 0);

        hashmap_free(&hm);
    }

    printf("test_hashmap: ok\n");
    return 0;
}
