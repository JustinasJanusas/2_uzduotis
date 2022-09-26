#include "linkedlist.h"

#define DELIMETER ","

void load_list(struct Person **list, FILE *file){
	char line[128];
	while (fgets(line, sizeof(line), file)) {
		struct Person *person = NULL;
		if(strcmp(line, "\n") == 0) {
		    continue;
		}
		person = create_address_node(line);
		if (person != NULL) {
		    add_to_list(list, person);
		}
	}
}

struct Person* create_address_node(char *address_line)
{
	struct Person *person = NULL;
	char *name;
	char *surname;
	char *number;
	char *email;
	name = strtok(address_line, DELIMETER);
	surname = strtok(NULL, DELIMETER);
	number = strtok(NULL, DELIMETER);
	email = strtok(NULL, DELIMETER);
	person = create_node(name, surname, number, email);
	return person;
}

struct Person* create_node(char *name, char *surname, char *number, char *email)
{
	struct Person *person = NULL;
	person = (struct Person*) malloc(sizeof(struct Person));
	if (person == NULL) {
		return NULL;
	}
	strcpy(person->name, name);
	strcpy(person->surname, surname);
	strcpy(person->number, number);
	strcpy(person->email, email);
	person->next = NULL;
	return person;
}


void add_to_list(struct Person **list, struct Person *person){
	struct Person* temp = *list;
	if (temp == NULL) {
		*list = person;
		return; 
	}

	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = person;
}


void add_to_list_by_index(struct Person **list, struct Person *person, int index){
	struct Person* temp = *list;
	int i = 0;
	if (temp == NULL) {
		if(index != i)
			free(person);
		*list = person;
		return; 
	}
	else if(index == i){
		person->next = *list;
		*list = person;
		return;
	}
	while (temp->next != NULL && index-1 > i) {
		temp = temp->next;
		i++;
	}
	if(i == index-1){
		person->next = temp->next;
		temp->next = person;	
		return;	
	}
	//gautas blogas indeksas
	free(person);
	
}
void remove_from_list(struct Person **list, int index){
	struct Person* temp = *list;
	int i = 0;
	if(temp == NULL)
		return;
	if(i == index){
		*list = temp->next;
		free(temp);
		return;
	}
	while (temp->next != NULL && index-1 > i) {
		temp = temp->next;
		i++;
	}
	if(i == index-1 && temp->next != NULL){
		struct Person *to_delete = temp->next;
		temp->next = to_delete->next;
		free(to_delete);		
	}
}
void delete_list(struct Person **list) 
{
	struct Person *to_delete = *list;
	while (*list != NULL) {
		*list = (*list)->next;
		free(to_delete);
		to_delete = *list;
	}
}
struct Person* get_node(struct Person *list, int index){
	int i = 0;
	struct Person *temp = list;
	while(temp != NULL){
		if(i == index)
			return temp;
		temp = temp->next;
		i++;
	}
	return NULL;
}
struct Person* find_node(struct Person *list, char line[], char type){
	struct Person *temp = list;
	while(temp != NULL){
		switch(type){
			case 'v':
				if (strstr(temp->name, line) != NULL)
					return temp;
				break;
			case 'p':
				if (strstr(temp->surname, line) != NULL)
					return temp;
				break;
			case 't':
				if (strstr(temp->number, line) != NULL)
					return temp;
				break;
			case 'e':
				if (strstr(temp->email, line) != NULL)
					return temp;
				break;
			default:
				return NULL;
		}
		temp = temp->next;
	}
	return NULL;
}
