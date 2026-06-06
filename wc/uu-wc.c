#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

#define MAX_ARGS 64
#define MAX_INPUT 1024


int main(int argc, char *argv[]) {

	char *filename = ""; 

	// flags to determine which one is in args
	int dash_l = 0;
	int dash_c = 0;
	int dash_w = 0;
	int dash_m = 0;
	int dash_default = 0;
	
	for (int i = 0; i < argc; i++) {
		// printf("argv[%d] = %s\n", i, argv[i]);

		if (strstr(argv[i], "txt") != NULL) {
			filename = argv[i];
		}

		if (strstr(argv[i], "-") != NULL) {
			if (strcmp(argv[i], "-c") == 0) {
				// printf("Dash C found!\n");
				dash_c = 1;
			}
			else if (strcmp(argv[i], "-l") == 0) {
				// printf("Dash L found!\n");
				dash_l = 1;
			}
			else if (strcmp(argv[i], "-w") == 0) {
				// printf("Dash W found!\n");
				dash_w = 1;
			}
			else if (strcmp(argv[i], "-m") == 0) {
				// printf("Dash M found!\n");
				dash_m = 1;
			}
		}
	}

	char ch;
	long lines = 0;
	long word_count = 0;
	int in_word = 0;
	FILE *fp = fopen(filename, "rb");

	if (fp == NULL) {
		fp = stdin;
	}	
	
	if (dash_l == 0 && dash_c == 0 && dash_w == 0 && dash_m == 0) {
		dash_default = 1;
		// get number of LINES and WORDS in the file
		while ((ch = fgetc(fp)) != EOF) {
			if (isspace(ch)) {
				if (ch == '\n') {
					lines++;
				}
				in_word = 0;
			}
			else {
				if(!in_word) {
					word_count++;
				}
				in_word = 1;
			}
		}

		// gets the number of BYTES in file
		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);

		printf("%ld	%ld	%ld	%s\n", lines, word_count, size, filename);
	}
	
	if (dash_l) {
		// gets number of LINES in the file
		while ((ch = fgetc(fp)) != EOF) {
			if (isspace(ch)) {
				if (ch == '\n') {
					lines++;
				}
				in_word = 0;
			}
			else {
				if(!in_word) {
					word_count++;
				}
				in_word = 1;
			}
		}
		printf("%ld	%s\n", lines, filename);
	}
	else if (dash_c) {
		// gets the number of BYTES in file
		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);

		printf("%ld	%s\n", size, filename);
	}
	else if (dash_w) {
		// get number of WORDS in the file
		long word_count = 0;
		int in_word = 0;
		while ((ch = fgetc(fp)) != EOF) {
			if (isspace(ch)) {
				in_word = 0;
			}
			else {
				if(!in_word) {
					word_count++;
				}
				in_word = 1;
			}
		}

		printf("%ld	%s\n", word_count, filename);
	}
	else if (dash_m) {
		// get number of CHARACTERS in the file
		wint_t wc;
		long char_count = 0;
		setlocale(LC_ALL, "");

 		while ((wc = fgetwc(fp)) != WEOF) {
			char_count++;
		}

		printf("%ld	%s\n", char_count, filename);
	}

	return 0;
}