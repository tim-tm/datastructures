#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_SIZE 256
#define TABLE_SIZE 10
#define DELETED_NODE (Person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
    char name[MAX_NAME_SIZE];
    int age;
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
        if (hash_table[i] != NULL && hash_table[i] != DELETED_NODE) {
            printf("\t%s - %i\n", hash_table[i]->name, hash_table[i]->age);
        }
    }
}

bool insert_hash_table(Person* person) {
    if (person == NULL) return false;
    
    int index = hash(person->name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int curr = (i + index) % TABLE_SIZE;
        if (hash_table[curr] == NULL || hash_table[curr] == DELETED_NODE) {
            hash_table[curr] = person; 
            return true;   
        }
    }
    return false;
}

Person* find_hash_table(char* name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int curr = (i + index) % TABLE_SIZE;
        if (hash_table[curr] == NULL) return false;
        if (hash_table[curr] == DELETED_NODE) continue;

        if (!strncmp(hash_table[curr]->name, name, MAX_NAME_SIZE)) {
            return hash_table[curr];
        }
    }
    return NULL;
}

Person* delete_hash_table(char* name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int curr = (i + index) % TABLE_SIZE;
        if (hash_table[curr] == NULL) return NULL;
        if (hash_table[curr] == DELETED_NODE) continue;

        if (!strncmp(hash_table[curr]->name, name, MAX_NAME_SIZE)) {
            Person* ptr = hash_table[curr];
            hash_table[curr] = DELETED_NODE;
            return ptr;
        }
    }
    return NULL;
}