#include <stdio.h>

#define LINKED_LIST_IMPL
#include "linkedlist.h"

int main() {
    node* head = node_create(1);
    list_push(head, node_create(15));
    list_push(head, node_create(5));
    list_push(head, node_create(4));
    printf("%i\n", list_contains(head, 14));
    list_print(head);
    list_sort(head);
    list_serialize(head, "test.txt");
    list_print(head);
    list_clear(head);

    //node* shead = list_deserialize("test.txt");
    //list_print(shead);
    //list_clear(shead);
    return 0;
}