#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#ifndef LINKED_LIST_BUF_SIZE
#define LINKED_LIST_BUF_SIZE 4096
#endif // LINKED_LIST_BUF_SIZE

typedef struct _node{
    struct _node* next;
    struct _node* last;
    size_t value;
} node;

node* node_create(size_t value);
void node_free(node* __node);

static void __swap(size_t* l, size_t* l1);
static node* __partition(node* n, node* n1);
static void __quicksort(node* n, node* n1);

bool list_push(node* head, node* __node);
size_t list_pop(node* head);
void list_clear(node* head);
bool list_contains(node* head, size_t value);
void list_print(node* head);
node* list_find_tail(node* head);
void list_sort(node* head);

void list_serialize(node* head, const char* filename);
node* list_deserialize(const char* filename);

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

static node* last_node = NULL;

static void __swap(size_t* l, size_t* l1) {
    size_t temp = *l;
    *l = *l1;
    *l1 = temp;
}

static node* __partition(node* n, node* n1) {
    size_t val = n1->value;
    node* i = n->last;

    for (node* j = n; j != n1; j = j->next) {
        if (j->value <= val) {
            if (i == NULL) {
                i = n;
            } else {
                i = i->next;
            }

            __swap(&i->value, &j->value);
        }
    }
    if (i == NULL) {
        i = n;
    } else {
        i = i->next;
    }
    __swap(&i->value, &n1->value);
    return i;
}

static void __quicksort(node* n, node* n1) {
    if (n1 != NULL && n != n1 && n != n1->next) {
        node* p = __partition(n, n1);
        __quicksort(n, p->last);
        __quicksort(p->next, n1);
    }
}

bool list_push(node* head, node* __node) {
    assert(head != NULL);
    node* current = head;
    while (current != NULL) {
        if (current->next == NULL) {
            __node->last = current;
            current->next = __node;
            last_node = __node;
            return 1;
        }
        current = current->next;
    }
    head = __node;
    return 1;
}

size_t list_pop(node* head) {
    node* temp = head;
    size_t val = temp->value;
    head = head->next;
    free(temp);
    return val;
}

void list_clear(node* head) {
    node* current = head;
    
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

bool list_contains(node* head, size_t value) {
    node* current = head;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void list_print(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%zu", current->value);
        if (current->next == NULL) printf("\n");
        else printf("->");
        current = current->next;
    }
}

node* list_find_tail(node* head) {
    node* current = head;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    return current;
}

void list_sort(node* head) {
    __quicksort(head, list_find_tail(head));
}

void list_serialize(node* head, const char* filename) {
#ifdef __unix__
    FILE* f = fopen(filename, "w+");
    node* current = head;
    while (current != NULL) {
        fprintf(f, "%zu", current->value);
        if (current->next == NULL) fprintf(f, "\n");
        else fprintf(f, "->");
        current = current->next;
    }
    fclose(f);
#endif
}

node* list_deserialize(const char* filename) {
    node* head = node_create(1);
#ifdef __unix__
    FILE* f = fopen(filename, "r");
    char buffer[LINKED_LIST_BUF_SIZE];
    while (!feof(f) && fgets(buffer, LINKED_LIST_BUF_SIZE, f) != NULL) {
        char* split = strtok(buffer, "->");
        while (split != NULL) {
            int i = atoi(split);
            list_push(head, node_create(i));
            printf("%i\n", i);
            split = strtok(NULL, "->");
        }
    }
    fclose(f);
#endif
    return head;
}

#endif // LINKED_LIST_IMPL
#endif // LINKED_LIST_H
