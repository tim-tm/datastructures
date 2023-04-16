#include "hashtable.h"
#include <stdio.h>
#include <string.h>

#define MAX_LINES 4096
#define FNV_PRIME 0x100000001b3
#define FNV_OFFSET 0xcbf29ce4235851UL

uint64_t test_hash_fnv0(const char* text, size_t length) {
    uint64_t hash = 0;
    for (int i = 0; i < length; ++i) {
        hash *= FNV_PRIME;
        hash ^= text[i];
    }
    return hash;
}

uint64_t test_hash_fnv1(const char* text, size_t length) {
    uint64_t hash = FNV_OFFSET;
    for (int i = 0; i < length; ++i) {
        hash *= FNV_PRIME;
        hash ^= text[i];
    }
    return hash;
}

uint64_t test_hash_fnv1a(const char* text, size_t length) {
    uint64_t hash = FNV_OFFSET;
    for (int i = 0; i < length; ++i) {
        hash ^= text[i];
        hash *= FNV_PRIME;
    }
    return hash;
}

void generate_random_word(char* buffer, size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        buffer[i] = 'a' + (rand() % 26);
    }
    buffer[len - 1] = 0;
}

void test_cleanup(void* addr) {
    free(addr);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: <worldlist filename> <num guesses>\n");
        return EXIT_FAILURE;
    }

    char* filename = argv[1];
    uint32_t num_guesses = atol(argv[2]);

    const int tableSize = (1<<20);
    hash_table* table = hash_table_create(tableSize, test_hash_fnv1a, test_cleanup);

    FILE* file = fopen(filename, "r");
    char buffer[MAX_LINES];
    uint32_t words = 0;
    while (!feof(file) && fgets(buffer, MAX_LINES, file) != NULL) {
        buffer[strcspn(buffer, "\n\r")] = 0;
        char* newEntry = malloc(strlen(buffer) + 1);
        strcpy(newEntry, buffer);

        hash_table_insert(table, newEntry, newEntry);
        words++;
    }
    fclose(file);
    printf("Loaded %d words into the table!\n", words);
    printf("\t... with %lu col.\n", hash_table_collisions(table));
    //hash_table_print(table);

    uint32_t guessesPassed = 0;
    const int minGuess = 2;
    const int maxGuess = 15;
    for (uint32_t i = 0; i < num_guesses; ++i) {
        generate_random_word(buffer, minGuess + (rand() % (maxGuess - minGuess)));
        if (hash_table_find(table, buffer)) {
            guessesPassed++;
        }
    }
    printf("%i of %i guessed passed!\n", guessesPassed, num_guesses);
    hash_table_clear(table);

    return 0;
}