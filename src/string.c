#include "cstructs/string.h"

#include <stdlib.h>
#include <string.h>

void string_builder_init(string_builder *sb) {
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

static int ensure_capacity(string_builder *sb, size_t needed) {
    if (sb->len + needed <= sb->cap) {
        return 0;
    }
    size_t new_cap = sb->cap == 0 ? 16 : sb->cap;
    while (new_cap < sb->len + needed) {
        new_cap *= 2;
    }
    char *new_data = realloc(sb->data, new_cap);
    if (new_data == NULL) {
        return -1;
    }
    sb->data = new_data;
    sb->cap = new_cap;
    return 0;
}

int string_builder_push_char(string_builder *sb, char c) {
    if (ensure_capacity(sb, 1) != 0) {
        return -1;
    }
    sb->data[sb->len] = c;
    sb->len++;
    return 0;
}

int string_builder_push_str(string_builder *sb, const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t str_len = strlen(str);
    if (ensure_capacity(sb, str_len) != 0) {
        return -1;
    }
    memcpy(sb->data + sb->len, str, str_len);
    sb->len += str_len;
    return 0;
}

int string_builder_push_bytes(string_builder *sb, const void *buf, size_t n) {
    if (n == 0) {
        return 0;
    }
    if (ensure_capacity(sb, n) != 0) {
        return -1;
    }
    memcpy(sb->data + sb->len, buf, n);
    sb->len += n;
    return 0;
}

const char *string_builder_data(const string_builder *sb) { return sb->data; }

size_t string_builder_len(const string_builder *sb) { return sb->len; }

void string_builder_free(string_builder *sb) {
    free(sb->data);
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}
