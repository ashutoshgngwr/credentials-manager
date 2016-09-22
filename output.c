#include "headers/output.h"

char* pass;

void init_config() {
	char *c_pass;
	FILE* f_config = fopen("cm.settings", "w");

	printf(ABOUT_SOFTWARE "\n" INIT_SOFT_MESSAGE);

	retry:
	
	printf(CREATE_PASSWORD_MESSAGE);
	pass = input_password();

	printf(CONFIRM_PASSWORD_MESSAGE);
	c_pass = input_password();

	if(strcmp(pass, c_pass)) {
		printf("\n" PASSWORD_MISMATCH_MESSAGE);
		dump(pass, c_pass);
		goto retry;
	}

	fprintf(f_config, "%lu", hash(pass));

	fclose(f_config);

	dump(c_pass);
}

int init_done() {
	FILE* f_config = fopen("cm.settings", "r");
	if(f_config == NULL)
		return 0;

	fseek(f_config, 0, SEEK_END);
	return ftell(f_config);
}

void ask_password() {
	size_t pass_hash;

	FILE* f_config = fopen("cm.settings", "r");
	fscanf(f_config, "%lu", &pass_hash);
	fclose(f_config);

	retry:

	printf("\n" ENTER_PASSWORD_MESSAGE);
	pass = input_password();

	if(hash(pass) != pass_hash) {
		printf("\n" INVALID_PASSWORD_MESSAGE);
		dump(pass);
		goto retry;
	}

}

void show_menu() {
	clear_screen();

	printf("\n" MENU_OPTIONS_MESSAGE);

	retry:

	switch(getch()) {
		case '1':
			add_entry();
			break;
		case '2':
			search_entry();
			break;
		case '3':
			show_about();
			break;
		case '4':
			dump(pass);
			system("clear");
			printf(GOODBYE_MESSAGE);
			break;
		default:
			goto retry;
	}
}

void add_entry() {
	char *url, *username, *password, choice;

	retry:

	clear_screen();

	printf("\n" ADD_ENTRY_MESSAGE "\n");

	retry_url:

	printf(ENTER_WEBSITE_MESSAGE);
	url = input_text();

	if(!strlen(url)) {
		printf(INVALID_INPUT "\n");
		dump(url);
		goto retry_url;
	}

	retry_user:

	printf(ENTER_USERNAME_MESSAGE, url);
	username = input_text();

	if(!strlen(username)) {
		printf(INVALID_INPUT "\n");
		dump(username);
		goto retry_user;
	}

	retry_pass:

	printf(ENTER_PASS_MESSAGE, url);
	password = input_text();

	if(!strlen(password)) {
		printf(INVALID_INPUT "\n");
		dump(password);
		goto retry_pass;
	}

	printf("\n" CONFIRM_ADD_ENTRY_MESSAGE, url, username, password);

	if(getch() == '\n') {
		db_add(url, username, password, pass);
		printf("\n" ENTRY_ADDED_MESSAGE);
	} else {
		dump(url, username, password);
		goto retry;
	}

	dump(url, username, password);

	pause_process();
	show_menu();
}

void search_entry() {
	char *query = NULL;
	node *results;

	retry0:

	clear_screen();

	printf("\n" SEARCH_ENTRY_MESSAGE "\n");

	retry1:

	if(query != NULL)
		dump(query);

	printf(WEBSITE_SEARCH_MESSAGE);
	query = input_text();

	if(!strlen(query)) {
		printf(INVALID_INPUT "\n");
		goto retry1;
	}

	results = db_search(query, pass);
	
	show_results(&results);

	if(results == NULL) {
		if(getch() == '\n') {
			goto retry0;
		}
	}

	dump(query);

	if(results != NULL)
		list_dump(&results);

	show_menu();
}

void show_results(node **results) {
	int i = 0;
	node *temp = *results;

	if(temp == NULL) {
		printf(NO_RESULTS_FOUND_MESSAGE);
		return;
	}

	printf("\n%3s %-30s %-30s %-30s\n", "SN.", "Website", "Username", "Password");

	do {
		printf("%-3d %-30s %-30s %-30s\n", ++i, temp->url, temp->username, temp->password);
		temp = temp->next;
	} while(temp != NULL);

	printf("\n" EDIT_REMOVE_ENTRY_MESSAGE);

	switch(tolower(getch())) {
		case 'e':
			edit_entry(results);
			break;
		case 'r':
			remove_entry(results);
			break;
	}
}

void remove_entry(node **results) {
	int loc = 0;
	node *temp;

	retry0:

	printf("\n" REMOVE_ENTRY_MESSAGE);
	scanf("%d", &loc);
	getch();

	if((temp = list_get_node(*results, loc)) == NULL) {
		printf(INVALID_INPUT);
		goto retry0;
	} else {
		printf("\n" REMOVE_ENTRY_CONFIRM_MESSAGE, temp->url);

		if(getch() != '\n')
			goto retry0;

		db_delete(temp->url);
		list_delete_node(results, loc);

		printf("\n" ENTRY_DELETED_SUCCESSFULLY);
		pause_process();
	}

	clear_screen();
	show_results(results);
}

void edit_entry(node **results) {
	int loc = 0;
	node *temp;
	char *url, *username, *password;

	retry0:

	printf("\n" EDIT_ENTRY_MESSAGE);
	scanf("%d", &loc);
	getch();

	if((temp = list_get_node(*results, loc)) == NULL) {
		printf(INVALID_INPUT);
		goto retry0;
	} else {
		printf("\n" EMPTY_UNCHANGED_MESSAGE);

		printf(ENTER_WEBSITE_MESSAGE);
		url = input_text();

		if(!strlen(url)) {
			dump(url);
			url = str_copy(temp->url);
		}

		printf(ENTER_USERNAME_MESSAGE, url);
		username = input_text();

		if(!strlen(username)) {
			dump(username);
			username = str_copy(temp->username);
		}
		
		printf(ENTER_PASS_MESSAGE, url);
		password = input_text();

		if(!strlen(password)) {
			dump(password);
			password = str_copy(temp->password);
		}

		printf("\n" ENTRY_EDIT_CONFIRM_MESSAGE, temp->url, temp->username, temp->password,
			url, username, password);

		if(getch() != '\n') {
			dump(url, username, password);
			goto retry0;
		}

		db_delete(temp->url);
		dump(temp->url, temp->username, temp->password);

		temp->url = url;
		temp->username = username;
		temp->password = password;

		db_add(url, username, password, pass);

		printf("\n" ENTRY_EDITED_SUCCESSFULLY);
		pause_process();

		clear_screen();
		show_results(results);
	}
}

void show_about() {
	clear_screen();
	printf("\n" ABOUT_SOFTWARE "\n");
	printf(ABOUT_AUTHOR "\n");
	pause_process();

	show_menu();
}