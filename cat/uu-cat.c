#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc > 1) {
		//for (int i = 0; i < argc; i++)  {
		//	printf("argv[%d] = %s\n", i, argv[i]);
		//}
		char *filename = argv[1];
		FILE *fp = fopen(filename, "r");
		if (fp == NULL) {
			fp = stdin;
		}
		//printf("I'm in there dawg!\n");
		char line[256];
		while (fgets(line, sizeof(line), fp)) {
			printf("%s", line);
		}
		fclose(fp);
	}
}
