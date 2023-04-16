#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_SIZE 256
#define TABLE_SIZE 10

typedef struct Person {
    char name[MAX_NAME_SIZE];
    int age;
    struct Person* next;
} Person;

Person* hash_table[TABLE_SIZE];

unsigned int hash(char* name) {
    int length = strlen(name);
    unsigned int hash = 0;
    for (int i = 0; i < length; i++) {
        hash += name[i];
        hash = (hash * name[i]) % TABLE_SIZE;
    }
    return hash;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] != NULL) {
            printf("\t%s - %i\n", hash_table[i]->name, hash_table[i]->age);
            Person* next = hash_table[i];
            while (next != NULL) {
                printf("%s - ", next->name);
                next = next->next;
            }
            printf("\n");
        }
    }
}

bool insert_hash_table(Person* person) {
    if (person == NULL) return false;
    
    int index = hash(person->name);
    person->next = hash_table[index];
    hash_table[index] = person;
    return true;
}

Person* find_hash_table(char* name) {
    int index = hash(name);
    Person* tmp = hash_table[index];
    while (tmp != NULL && !strncmp(tmp->name, name, MAX_NAME_SIZE)) {
        tmp = tmp->next;
    }
    return tmp;
}

Person* delete_hash_table(char* name) {
    int index = hash(name);
    Person* tmp = hash_table[index];
    Person* prev = NULL;
    while (tmp != NULL && !strncmp(tmp->name, name, MAX_NAME_SIZE)) {
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    
    if (prev == NULL) {
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return tmp;
}