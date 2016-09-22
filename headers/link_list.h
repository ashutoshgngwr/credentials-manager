#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct node_ {
	char *url;
	char *username;
	char *password;

	struct node_* next;
} node;

node *list_create();
void list_add(node**, node*);
node *list_get_node(node*, int);
void list_delete_node(node**, int);
void list_dump(node**);
void list_dump_node(node*);

#endif