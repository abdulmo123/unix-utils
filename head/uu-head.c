#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define FILES 256
#define FILENAME_LENGTH 32

void execute_head_cmd(int f, int len, char files[FILES][FILENAME_LENGTH], char dash_arg[4]);
bool startsWith(const char *str, const char *prefix);

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
	if (argc > 1) {
		int f = 0;
		char dash_arg[4];
        int len = 0;
		char files[FILES][FILENAME_LENGTH];
		for (int i = 1; i < argc; i++)  {
			char *str = argv[i];
			if (strstr(argv[i], ".txt") != NULL) {
				strcpy(files[f], argv[i]);
				f++;
			}
			if (startsWith(argv[i], "-")) {
				dash_arg[0] = argv[i][1];
				dash_arg[1] = '\0';

				
				if (strlen(argv[i]) > 2) {
					str = &argv[i][2];
					while ((*str >= '0') && (*str <= '9')) {
						len = (len * 10) + ((*str) - '0');
						str++;
					}	
				} 
			} 

			while ((*str >= '0') && (*str <= '9')) {
				len = (len * 10) + ((*str) - '0');
				str++;
			}
		}
		execute_head_cmd(f, len, files, dash_arg);
	} else {
        fp = stdin;
        char line[512];
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
        }
        fclose(fp);
    }
}

bool startsWith(const char *str, const char *prefix) {
	size_t prefix_len = strlen(prefix);

	if (strncmp(str, prefix, prefix_len) == 0) {
		return true;
	} else {
		return false;
	}
}

void execute_head_cmd(int f, int len, char files[FILES][FILENAME_LENGTH], char dash_arg[4]) {
	FILE *fp = NULL;
	for (int i = 0; i < f; i++) {
		int c = 0;
		int n = 0;
		if (f > 1) {
			printf("==> %s <==\n", files[i]);
		}
		fp = fopen(files[i], "r");
		if (strcmp(dash_arg, "n") == 0) {
			char line[1024];
			while (fgets(line, sizeof(line), fp) && n < len) {
				printf("%s", line);
				n++;
			}
		} else if (strcmp(dash_arg, "c") == 0) {
			int ch;
			while ((ch = fgetc(fp)) != EOF && c < len) {
				printf("%c", ch);
				c++;
			}
			printf("\n");
		}
		fclose(fp);
	}
}