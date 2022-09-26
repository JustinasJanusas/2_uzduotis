#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Person {
    char name[30];
    char surname[30];
    char number[15];
    char email[30];
    struct Person *next;
};


void load_list(struct Person **list, FILE *file);
void save_list(struct Person **list, FILE *file);
void add_to_list(struct Person **list, struct Person *person);
void add_to_list_by_index(struct Person **list, struct Person *person, int index);
void remove_from_list(struct Person **list, int index);
void delete_list(struct Person **list);
struct Person* get_node(struct Person *list, int index);
struct Person* find_node(struct Person *list, char line[], char type);
struct Person* create_address_node(char *address_line);
struct Person* create_node(char *name, char *surname, char *number, char *email);
