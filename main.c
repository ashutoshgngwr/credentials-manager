#include <stdio.h>

#include "headers/output.h"
#include "headers/utils.h"

int main() {

	clear_screen();

	if(!init_done())
		init_config();
	else
		ask_password();

	show_menu();

	return 0;
}