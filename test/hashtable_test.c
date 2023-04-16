#include <stdio.h>
#include "../include/hashtable.c"

int main() {
    init_hash_table();

    Person tim = {"Tim", 16};
    insert_hash_table(&tim);

    Person tom = {"Tom", 16};
    insert_hash_table(&tom);
    print_hash_table();

    Person* test = find_hash_table("Tim");
    if (test != NULL) {
        printf("Found %s!\n", test->name);
    }
    delete_hash_table("Tim");
    print_hash_table();
    return 0;
}