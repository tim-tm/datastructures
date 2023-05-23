#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node{
    struct _node* next;
    struct _node* last;
    size_t value;
} node;

node* node_create(size_t value);
void node_free(node* __node);

bool list_push(node* __node);
void list_clear();
bool list_contains(size_t value);
void list_print();

#ifdef LINKED_LIST_IMPL

node* node_create(size_t value) {
    node* node = malloc(sizeof(node));
    node->value = value;
    return node;
}

void node_free(node* __node) {
    if (__node->next != NULL) {
        free(__node->next);
    }
    if (__node->last != NULL) {
        free(__node->last);
    }
    free(__node);
}

static node* first_node = NULL;

bool list_push(node* __node) {
    node* current = first_node;
    while (current != NULL) {
        if (current->next == NULL) {
            __node->last = current;
            current->next = __node;
            return 1;
        }
        current = current->next;
    }
    first_node = __node;
    return 1;
}

void list_clear() {
    node* current = first_node;
    
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    first_node = NULL;
}

bool list_contains(size_t value) {
    node* current = first_node;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void list_print() {
    node* current = first_node;
    while (current != NULL) {
        printf("%zu", current->value);
        if (current->next == NULL) printf("\n");
        else printf("->");
        current = current->next;
    }
}

#endif // LINKED_LIST_IMPL
#endif // LINKED_LIST_H
