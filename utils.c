#include "headers/utils.h"

char s_buffer[1024];

void clear_screen() {
	system("clear");
	printf(WELCOME_MESSAGE);
}

void pause_process() {
	printf(CONTINUE_MESSAGE);
	getch();
}

char *process_buffer() {
	char *input = (char*) calloc(strlen(s_buffer) + 1, sizeof(char));
	strcpy(input, s_buffer);
	
	return input;
}

char *input_password() {
	char ch;
	int i = 0;
	while((ch = getch()) != '\n') {
		if(ch == '\b' && i) {
			i--;
			continue;
		}

		s_buffer[i++] = ch;

		putchar('*');
	}

	putchar('\n');

	s_buffer[i] = '\0';

	return process_buffer();
}

char *input_text() {
	char ch;
	int i = 0;

	while((ch = getchar()) != '\n')
		s_buffer[i++] = ch;

	s_buffer[i] = '\0';

	return process_buffer();
}

char getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

char *str_copy(char *src){
	char *res = (char *) calloc(strlen(src) + 1, sizeof(char));
	strcpy(res, src);
	return res;
}

char *base64_encode(unsigned char* str) {
	int len = 0;
	return base64(str, strlen(str), &len);
}

unsigned char *base64_decode(char *str) {
	int len = 0;
	return unbase64(str, strlen(str), &len);
}

size_t hash(const char* cp) {
	size_t hash = 5381;
	while (*cp)
		hash = 33 * hash ^ (unsigned char) *cp++;
	return hash;
}

void strrev(char *str) {
	char *p1, *p2;

	if (! str || ! *str)
		return;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
}

void encrypt(char *data, char *key) {
	int d_len, i;

	d_len = strlen(data);

	for(i = 0; i < d_len; i++)
		data[i] += 5;

	strrev(data);
}

void decrypt(char *data, char *key) {
	int d_len, i;

	d_len = strlen(data);

	strrev(data);

	for(i = 0; i < d_len; i++)
		data[i] -= 5;
}

void dump(char *first, ...) {
	va_list args;
	char *ch;

	va_start(args, first);

	free(first);

	while((ch = va_arg(args, char*)) != NULL);
		free(ch);

	va_end(args);
}