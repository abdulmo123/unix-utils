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
			//printf("argv[%d] = %s\n", i, argv[i]);
			if (strstr(argv[i], ".txt") != NULL) {
				strcpy(files[f], argv[i]);
				//printf("files[%d] = %s\n", f, files[f]);
				f++;
			}
			if (strstr(argv[i], "-") != NULL) {
				strcpy(dash_arg, argv[i]);
				//printf("dash_arg = %s\n", dash_arg);
			}
		}
		execute_cat_cmd(f, files, dash_arg);
	}
}


void execute_cat_cmd(int f, char files[FILES][FILENAME_LENGTH], char dash_arg[10]) {
	FILE *fp = fopen(files[0], "rb");
	if (f == 0) {
		fp = stdin;
		char line[100];
		while (fgets(line, sizeof(line), fp)) {
			printf("%s", line);
		}
		fclose(fp);
		return;
	}

	for (int i = 0; i < f; i++) {
		fp = fopen(files[i], "r");
		char line[256];
		while (fgets(line, sizeof(line), fp)) {
			printf("%s", line);
		}
		fclose(fp);
	}
}
