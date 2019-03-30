#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct wc_info {
    size_t strings_c;
    size_t words_c;
    size_t symbols_c;
};

void counting_info(bool from_file, FILE *fp, struct wc_info *info) {
    int ch;
    bool is_new_word = true;

    while ((ch = from_file ? fgetc(fp) : getchar()) != EOF) {
        switch (ch) {
            case '\n': {
                is_new_word = true;
                ++(info->strings_c);
            }
            default: {
                if (isspace(ch)) {
                    is_new_word = true;
                } else {
                    if (is_new_word) {
                        ++(info->words_c);
                    }
                    is_new_word = false;
                }
            }
        }
        ++(info->symbols_c);
    }
}

int main(int argc, char **argv) {

	int c;

	struct wc_info info;
	info.symbols_c = info.words_c = info.strings_c = 0;
	
	if (argc == 1) {
        counting_info(false, NULL, &info);
        printf("%lu %lu %lu\n", info.strings_c, info.words_c, info.symbols_c);
        return 0;
	}

	for (size_t i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        counting_info(true, fp, &info);
        printf("%lu %lu %lu %s\n", info.strings_c, info.words_c, info.symbols_c, argv[i]);
        info.symbols_c = info.words_c = info.strings_c = 0;

        fclose(fp);
    }

	return 0;
}
