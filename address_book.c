#include <stdio.h>
#include <liblinkedlist.h>
#include <string.h>

#define DELIMETER ','

void listen(struct Person **list);
void print_list(struct Person *list);
void print_person(struct Person *list);
void read_info(struct Person **list, int index);
void get_delete_info(struct Person **list);
void get_get_info(struct Person *list);
void get_find_info(struct Person *list);

int main(int argc, char *argv[]){
	char file_name[50];
	if(argc > 1)
		strncpy(file_name, argv[1], sizeof(file_name)); 
	else
		strcpy(file_name, "data.csv");
	struct Person *list = NULL;
	FILE *data_file = NULL;
	data_file = fopen(file_name, "r");
	if(!data_file){
		printf("Couldn't open open file: %s\nList is empty\n", file_name); 
		goto file_error;
	}
	load_list(&list, data_file);
	fclose(data_file);
file_error:
	listen(&list);
	delete_list(&list);
	return 0;
}

void listen(struct Person **list){
	int cont = 1;
	char string[50];
	while(cont){
		printf("user: ");
		fgets(string, 50, stdin);
		string[strlen(string)-1] = '\0';
		if(strcmp(string, "help") == 0){
			printf("komandos:\n\thelp\n\texit\n\tget\n\tfind"
				"\n\tdelete\n\tprint\n\tadd\n\taddn\n\tdelete\n\tdeleteall\n");
		}
		else if(strcmp(string, "exit") == 0)
			cont = 0;
		else if(strcmp(string, "print") == 0)
			print_list(*list);
		else if(strcmp(string, "add") == 0)
			read_info(list, -1);
		else if(strcmp(string, "addn") == 0)
			read_info(list, 0);
		else if(strcmp(string, "deleteall") == 0)
			delete_list(list);
		else if(strcmp(string, "delete") == 0){
			get_delete_info(list);
			fgets(string, 50, stdin);
		}
		else if(strcmp(string, "get") == 0){
			get_get_info(*list);
			fgets(string, 50, stdin);
		}
		else if(strcmp(string, "find") == 0)
			get_find_info(*list);
		else
			printf("type 'help' to see available commands\n");
	}
	
}

void print_list(struct Person *list){
	putchar('\n');
	struct Person *temp = list;
	while(temp != NULL){
		print_person(temp);
		temp = temp->next;
	}
	putchar('\n');
}

void print_person(struct Person *person){
	printf("%s %s %s %s", person->name, person->surname, person->number, person->email);
}

void read_info(struct Person **list, int index){
	char line[150]; 
	printf("Iveskite asmens informacija nurodytu formatu:\n"
		"vardas,pavarde,telNumeris,elPastas\n:");
	scanf("%s", line);
	strcat(line, "\n");
	struct Person *person = NULL;
	person = create_address_node(line);
	if(index<0){
		fgets(line, 150, stdin);
		add_to_list(list, person);
	}
	else{
		printf("Iveskite vieta sarase (numeruojama nuo 1): ");
		scanf("%d", &index);
		fgets(line, 150, stdin);
		add_to_list_by_index(list, person, index-1);
	}
}
void get_delete_info(struct Person **list){
	printf("Iveskite naikinamo elemento vieta sarase (skaiciuojama nuo 1): ");
	int index = -1;
	scanf("%d", &index);
	remove_from_list(list, index-1);
}
void get_get_info(struct Person *list){
	printf("Iveskite elemento pozicija sarase (numeruojama nuo 1): ");
	int index = -1;
	scanf("%d", &index);
	print_person(get_node(list, index-1));
}
void get_find_info(struct Person *list){
	char type[1];
	printf("Iveskite paieskos filtrus\nformatas:\n"
		"filtro tipai\n\tv - vardo\n\tp - pavardes\n\tt - telefono numerio\n\t"
		"e - el. pasto\nIveskite filtro tipa: ");
	char t[2];
	fgets(t, 2, stdin);
	
	char line[30];
	printf("Iveskite filtra: ");
	fgets(line, 30, stdin);
	fgets(line, 30, stdin);
	line[strlen(line)-1] = '\0';
	struct Person *temp = find_node(list, line, type[1]);
	if(temp != NULL)
		print_person(temp);
	else
		printf("Toks asmuo nerastas\n");
}
