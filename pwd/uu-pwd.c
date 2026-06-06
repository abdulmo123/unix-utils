#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_LEN 1024

int main(int argc, char *argv[]) {

	char cwd[PATH_LEN];
	if (getcwd(cwd, sizeof(cwd))) {
		printf("%s\n", cwd);
	}
	return 0;

}
