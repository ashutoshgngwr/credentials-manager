#ifndef DB_FUNCTIONS_H
#define DB_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "link_list.h"

FILE *db_open();
long db_is_empty(FILE*);
char *db_read_line(FILE*);
void db_add(char*, char*, char*, char*);
node *db_search(char*, char*);
void db_delete(char *url);
char *process_db_buffer(char*);

#endif