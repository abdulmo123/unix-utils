#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILES 256
#define FILENAME_LENGTH 32

void execute_cat_cmd(int f, char files[FILES][FILENAME_LENGTH], char dash_arg[10]);

int main(int argc, char *argv[]) {
	if (argc > 1) {
		int f = 0;
		char dash_arg[10];
		char files[FILES][FILENAME_LENGTH];
		for (int i = 1; i < argc; i++)  {
			if (strstr(argv[i], ".txt") != NULL) {
				strcpy(files[f], argv[i]);
				f++;
			}
			if (strstr(argv[i], "-") != NULL) {
				strcpy(dash_arg, argv[i]);
			}
		}
		execute_cat_cmd(f, files, dash_arg);
	}
}


void execute_cat_cmd(int f, char files[FILES][FILENAME_LENGTH], char dash_arg[10]) {
	if (strcmp(dash_arg, "-n") == 0) {
		int idx = 0;
		FILE *fp = fopen(files[0], "rb");
		if (f == 0) {
			fp = stdin;
			char line[512];
			while (fgets(line, sizeof(line), fp)) {
				idx++;
				printf("%d %s", idx, line);
			}
			fclose(fp);
			return;
		}

		for (int i = 0; i < f; i++) {
			fp = fopen(files[i], "r");
			char line[512];
			while (fgets(line, sizeof(line), fp)) {
				idx++;
				printf("%d %s", idx, line);
			}
			fclose(fp);
		}
	} else if (strcmp(dash_arg, "-b") == 0) {
		int idx = 0;
		FILE *fp = fopen(files[0], "rb");
		if (f == 0) {
			fp = stdin;
			char line[512];
			while (fgets(line, sizeof(line), fp)) {
				if (line[0] != '\n' && line[0] != '\0') {
					idx++;
					printf("%d %s", idx, line);
				}
				else {
					printf("%s", line);
				}
			}
			fclose(fp);
			return;
		}

		for (int i = 0; i < f; i++) {
			fp = fopen(files[i], "r");
			char line[512];
			while (fgets(line, sizeof(line), fp)) {
				if (line[0] != '\n' && line[0] != '\0') {
					idx++;
					printf("%d %s", idx, line);
				}
				else {
					printf("%s", line);
				}
			}
			fclose(fp);
		}
	}
}
