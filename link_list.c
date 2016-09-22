#include "headers/link_list.h"

node *list_create() {
	return NULL;
}

void list_add(node **base, node *to_add) {
	node *temp = *base;

	to_add->next = NULL;

	if(*base == NULL)
		*base = to_add;
	else {
		while(temp->next != NULL)
			temp = temp->next;

		temp->next = to_add;
	}
}

node *list_get_node(node *base, int loc) {
	int i;
	node *temp = base;

	if(loc < 1)
		return NULL;

	for(i = 0; i < loc - 1; i++) {
		temp = temp->next;

		if(temp == NULL)
			return NULL;
	}

	return temp;
}

void list_delete_node(node **base, int loc) {
	node *prev, *cur;
	int i;

	prev = cur = *base;

	if(loc < 1 || *base == NULL)
		return;
	else if(loc == 1) {
		*base = cur->next;
		list_dump_node(cur);
		return;
	}

	for(i = 2; i <= loc; i++) {
		prev = cur;
		cur = cur->next;

		if(cur == NULL)
			return;
	}

	prev->next = cur->next;

	list_dump_node(cur);
}

void list_dump(node **base) {
	node *temp = *base;

	if(*base == NULL)
		return;

	do {
		list_dump_node(temp);
	} while((temp = temp->next) != NULL);

	*base = NULL;
}

void list_dump_node(node *n) {
	dump(n->url, n->username, n->password);

	free(n);
}