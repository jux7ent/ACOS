#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_string(char *str, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		str[i] = 0;
	}
}

int main(int argc, char **argv) {
	
	char *pathname = argv[1];
	int c;
	
	if (argc == 1) {
		char *input_string;
		input_string = (char *)malloc(100);

		int c;
		size_t i = 0;

		while ((c = getchar()) != EOF) {

			if (c == '\n') {
				printf("%s \n", input_string);
				i = 0;
				clear_string(input_string, 100);
			} else {
				input_string[i] = (char) c;
				++i;
			}
		}

	} else {
		FILE *fp = fopen(pathname, "r");
	
		if (fp != NULL) {
			while (1) {
				c = fgetc(fp);
		
				if (feof(fp)) {
					break;
				}
		
				printf("%c", c);	
			}
			fclose(fp);
	 	} else {
			perror(pathname);
		}
	}

	return 0;
}
