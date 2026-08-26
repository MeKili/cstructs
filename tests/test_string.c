#include "cstructs/string.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    /* Test initialization. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_len(&sb) == 0);
        assert(string_builder_data(&sb) == NULL || string_builder_data(&sb)[0] == '\0' || string_builder_len(&sb) == 0);
        string_builder_free(&sb);
        assert(string_builder_len(&sb) == 0);
    }

    /* Test push_char. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_push_char(&sb, 'a') == 0);
        assert(string_builder_len(&sb) == 1);
        assert(string_builder_data(&sb)[0] == 'a');
        string_builder_free(&sb);
    }

    /* Test push_str. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_push_str(&sb, "hello") == 0);
        assert(string_builder_len(&sb) == 5);
        assert(memcmp(string_builder_data(&sb), "hello", 5) == 0);
        string_builder_free(&sb);
    }

    /* Test push_str with NULL. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_push_str(&sb, NULL) == 0);
        assert(string_builder_len(&sb) == 0);
        string_builder_free(&sb);
    }

    /* Test push_bytes. */
    {
        string_builder sb;
        string_builder_init(&sb);
        const char *data = "test\0data";
        assert(string_builder_push_bytes(&sb, data, 9) == 0);
        assert(string_builder_len(&sb) == 9);
        assert(memcmp(string_builder_data(&sb), data, 9) == 0);
        string_builder_free(&sb);
    }

    /* Test push_bytes with zero length. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_push_bytes(&sb, "ignored", 0) == 0);
        assert(string_builder_len(&sb) == 0);
        string_builder_free(&sb);
    }

    /* Test multiple appends. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_push_str(&sb, "Hello") == 0);
        assert(string_builder_push_char(&sb, ' ') == 0);
        assert(string_builder_push_str(&sb, "World") == 0);
        assert(string_builder_len(&sb) == 11);
        assert(memcmp(string_builder_data(&sb), "Hello World", 11) == 0);
        string_builder_free(&sb);
    }

    /* Test repeated appends with growth. */
    {
        string_builder sb;
        string_builder_init(&sb);
        for (int i = 0; i < 100; i++) {
            assert(string_builder_push_char(&sb, 'x') == 0);
        }
        assert(string_builder_len(&sb) == 100);
        for (size_t i = 0; i < 100; i++) {
            assert(string_builder_data(&sb)[i] == 'x');
        }
        string_builder_free(&sb);
    }

    /* Test large string append. */
    {
        string_builder sb;
        string_builder_init(&sb);
        char large[1024];
        memset(large, 'A', sizeof(large));
        assert(string_builder_push_bytes(&sb, large, sizeof(large)) == 0);
        assert(string_builder_len(&sb) == sizeof(large));
        assert(memcmp(string_builder_data(&sb), large, sizeof(large)) == 0);
        string_builder_free(&sb);
    }

    /* Test mixed operations. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_push_char(&sb, '[') == 0);
        assert(string_builder_push_str(&sb, "item1") == 0);
        assert(string_builder_push_bytes(&sb, ", ", 2) == 0);
        assert(string_builder_push_str(&sb, "item2") == 0);
        assert(string_builder_push_char(&sb, ']') == 0);
        const char *expected = "[item1, item2]";
        assert(string_builder_len(&sb) == 14);
        assert(memcmp(string_builder_data(&sb), expected, 14) == 0);
        string_builder_free(&sb);
    }

    /* Test reuse after free. */
    {
        string_builder sb;
        string_builder_init(&sb);
        assert(string_builder_push_str(&sb, "first") == 0);
        string_builder_free(&sb);
        assert(string_builder_len(&sb) == 0);
        assert(string_builder_push_str(&sb, "second") == 0);
        assert(string_builder_len(&sb) == 6);
        assert(memcmp(string_builder_data(&sb), "second", 6) == 0);
        string_builder_free(&sb);
    }

    printf("test_string: ok\n");
    return 0;
}
