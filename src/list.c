#include "../include/cstructs/list.h"
#include <stdlib.h>
#include <string.h>

void list_init(list *l, size_t elem_size)
{
    l->head = NULL;
    l->elem_size = elem_size;
    l->len = 0;
}

int list_prepend(list *l, const void *elem)
{
    list_node *node = malloc(sizeof(list_node));
    if (!node)
        return -1;

    node->data = malloc(l->elem_size);
    if (!node->data) {
        free(node);
        return -1;
    }

    memcpy(node->data, elem, l->elem_size);
    node->next = l->head;
    l->head = node;
    l->len++;

    return 0;
}

int list_append(list *l, const void *elem)
{
    list_node *node = malloc(sizeof(list_node));
    if (!node)
        return -1;

    node->data = malloc(l->elem_size);
    if (!node->data) {
        free(node);
        return -1;
    }

    memcpy(node->data, elem, l->elem_size);
    node->next = NULL;
    l->len++;

    if (!l->head) {
        l->head = node;
    } else {
        list_node *curr = l->head;
        while (curr->next)
            curr = curr->next;
        curr->next = node;
    }

    return 0;
}

void list_pop_front(list *l, void *out)
{
    list_node *node = l->head;
    memcpy(out, node->data, l->elem_size);
    l->head = node->next;
    free(node->data);
    free(node);
    l->len--;
}

void *list_at(const list *l, size_t i)
{
    list_node *curr = l->head;
    while (i > 0) {
        curr = curr->next;
        i--;
    }
    return curr->data;
}

size_t list_len(const list *l)
{
    return l->len;
}

void list_free(list *l)
{
    list_node *curr = l->head;
    while (curr) {
        list_node *next = curr->next;
        free(curr->data);
        free(curr);
        curr = next;
    }
    l->head = NULL;
    l->len = 0;
}
