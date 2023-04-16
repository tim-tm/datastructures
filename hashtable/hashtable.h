#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint64_t hashfunc(const char*, size_t);
typedef void cleanfunc(void*);
typedef struct _hash_table hash_table;

hash_table* hash_table_create(uint32_t size, hashfunc* hashfunc, cleanfunc* cleanfunc);
void hash_table_clear(hash_table* table);
void hash_table_print(hash_table* table);
bool hash_table_insert(hash_table* table, const char* key, void* obj);
void* hash_table_find(hash_table* table, const char* key);
void* hash_table_delete(hash_table* table, const char* key);

uint64_t hash_table_collisions(hash_table* table);

#endif