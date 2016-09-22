#ifndef INIT_CONFIG_H
#define INIT_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include "db_functions.h"
#include "link_list.h"

void init_config();
int init_done();
void ask_password();
void show_menu();
void add_entry();
void search_entry();
void show_results(node**);
void remove_entry(node**);
void edit_entry(node**);
void show_about();

#endif