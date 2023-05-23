#include <stdio.h>

#define LINKED_LIST_IMPL
#include "linkedlist.h"

int main() {
    list_push(node_create(1));
    list_push(node_create(15));
    list_push(node_create(5));
    list_push(node_create(4));
    printf("%i\n", list_contains(14));
    list_print();
    list_clear();
    list_print();
    return 0;
}