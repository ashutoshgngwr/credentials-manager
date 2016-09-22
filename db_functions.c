#include "headers/db_functions.h"

FILE *db_open() {
	return fopen("cm.db", "a+");
}

long db_is_empty(FILE *db) {
	unsigned long c_pos = 0, end = 0;

	if(db == NULL)
		return 1;

	c_pos = ftell(db);

	fseek(db, 0, SEEK_END);
	end = ftell(db);

	fseek(db, c_pos, SEEK_SET);

	return !end;
}

void db_add(char *url, char *username, char *password, char *key) {
	char *en_user, *en_pass, *t_user, *t_pass;
	FILE *db = db_open();

	encrypt(t_user = str_copy(username), key);
	encrypt(t_pass = str_copy(password), key);

	en_user = base64_encode(t_user);
	en_pass = base64_encode(t_pass);

	fprintf(db, "%s,%s,%s\n", url, en_user, en_pass);

	dump(en_user, en_pass, t_user, t_pass);
	fclose(db);
}

char buf_url[1024], buf_user[1024], buf_pass[1024];

node *db_search(char *query, char *key) {
	node *results, *temp;
	char *url, *username, *password, *de_user, *de_pass;
	char end;
	FILE *db = db_open();

	if(db_is_empty(db))
		return NULL;

	results = list_create();

	rewind(db);

	while(fscanf(db, "%1023[^,],%1023[^,],%1023[^\n]%c", buf_url, buf_user, buf_pass, &end) != EOF) {
		url = process_db_buffer(buf_url);

		username = base64_decode(buf_user);
		password = base64_decode(buf_pass);

		if(strncmp(query, url, strlen(query))) {
			dump(url, username, password);
			continue;
		}

		decrypt(username, key);
		decrypt(password, key);

		temp = (node*) malloc(sizeof(node));
		temp->url = url;
		temp->username = username;
		temp->password = password;

		list_add(&results, temp);
	}

	fclose(db);

	return results;
}

void db_delete(char *url) {
	FILE *db, *temp;
	char end;

	db = db_open();
	temp = fopen("temp", "w");

	rewind(db);

	while(fscanf(db, "%1023[^,],%1023[^,],%1023[^\n]%c", buf_url, buf_user, buf_pass, &end) != EOF) {
		if(strcmp(url, buf_url))
			fprintf(temp, "%s,%s,%s\n", buf_url, buf_user, buf_pass);
	}

	fclose(temp);
	fclose(db);

	remove("cm.db");
	rename("temp", "cm.db");
}

char *process_db_buffer(char *buffer) {
	char *input = (char*) calloc(strlen(buffer) + 1, sizeof(char));
	strcpy(input, buffer);
	
	return input;
}
