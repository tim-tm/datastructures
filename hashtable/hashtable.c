#include "hashtable.h"
#include <string.h>
#include <stdio.h>

typedef struct entry {
    char* key;
    void* object;
    struct entry* next;
} entry;

typedef struct _hash_table {
    uint32_t size;
    hashfunc* hash;
    cleanfunc* cleanfunc;
    entry** elements;
    uint64_t collisions;
} hash_table;

static size_t hash_table_index(hash_table* table, const char* key) {
    return (size_t) (table->hash(key, strlen(key)) % table->size);
}

hash_table* hash_table_create(uint32_t size, hashfunc* hashfunc, cleanfunc* cleanfunc) {
    hash_table* table = malloc(sizeof(*table));
    table->size = size;
    table->hash = hashfunc;
    table->collisions = 0;
    table->cleanfunc = cleanfunc ? cleanfunc : free; 
    
    // calloc zeros the mem
    table->elements = calloc(sizeof(entry*), table->size);
    return table;
}

void hash_table_clear(hash_table* table) {
    for (uint32_t i = 0; i < table->size; ++i) {
        while (table->elements[i]) {
            entry* tmp = table->elements[i];
            table->elements[i] = table->elements[i]->next;
            free(tmp->key);
            table->cleanfunc(tmp->object);
            free(tmp);
        }
    }
    free(table->elements);
    free(table);
}

void hash_table_print(hash_table* table) {
    printf("Start Table.\n");
    for (uint32_t i = 0; i < table->size; ++i) {
        if (table->elements[i] != NULL) {
            printf("\t%i - ", i);
            entry* tmp = table->elements[i];
            while (tmp != NULL) {
                printf("\"%s\" (%p) - ", tmp->key, tmp->object);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End Table.\n");
    
}

bool hash_table_insert(hash_table* table, const char* key, void* obj) {
    if (table == NULL || key == NULL || obj == NULL) return false;
    size_t index = hash_table_index(table, key);

    if (hash_table_find(table, key) != NULL) return false;

    entry* entry = malloc(sizeof(*entry));
    entry->object = obj;
    entry->key = strdup(key);

    if (table->elements[index]) {
        table->collisions++;
    }
    entry->next = table->elements[index];
    table->elements[index] = entry;
    return true;
}

void* hash_table_find(hash_table* table, const char* key) {
    if (table == NULL || key == NULL) return false;
    size_t index = hash_table_index(table, key);

    entry* tmp = table->elements[index];
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        tmp = tmp->next;
    }

    if (tmp == NULL) return NULL;
    return tmp->object;
}

void* hash_table_delete(hash_table* table, const char* key) {
    if (table == NULL || key == NULL) return false;
    size_t index = hash_table_index(table, key);

    entry* tmp = table->elements[index];
    entry* prev = NULL;
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) return NULL;
    if (prev == NULL) {
        // delete the lists head
        table->elements[index] = tmp->next;
    } else {
        // delete the lists middle
        prev->next = tmp->next;
    }

    void* result = tmp->object;
    free(tmp);
    return result;
}

uint64_t hash_table_collisions(hash_table* table) {
    return table->collisions;
}