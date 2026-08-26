#ifndef CSTRUCTS_STRING_H
#define CSTRUCTS_STRING_H

#include <stddef.h>

/* A growable string builder that efficiently accumulates text. */
typedef struct {
    char *data;
    size_t len;
    size_t cap;
} string_builder;

/* Initialize an empty string builder. */
void string_builder_init(string_builder *sb);

/* Append a single character. Returns 0 on success, -1 on allocation failure. */
int string_builder_push_char(string_builder *sb, char c);

/* Append a null-terminated string. Returns 0 on success, -1 on allocation failure. */
int string_builder_push_str(string_builder *sb, const char *str);

/* Append n bytes from buf. Returns 0 on success, -1 on allocation failure. */
int string_builder_push_bytes(string_builder *sb, const void *buf, size_t n);

/* Get the built string (not null-terminated). Length is string_builder_len(sb). */
const char *string_builder_data(const string_builder *sb);

/* Current length in bytes (not counting null terminator, if any). */
size_t string_builder_len(const string_builder *sb);

/* Free the builder's storage and reset it to the empty state. */
void string_builder_free(string_builder *sb);

#endif /* CSTRUCTS_STRING_H */
