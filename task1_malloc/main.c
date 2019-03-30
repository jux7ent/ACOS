#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    false, true
} bool;

#define DEBUG false
#define WORDS_CAPACITY_INCREASE 1000
#define WORD_CAPACITY_INCREASE 100

void print_strings(char **words);

int cstring_cmp(const void *a, const void *b) {
    const char **ia = (const char **) a;
    const char **ib = (const char **) b;

    return strcmp(*ia, *ib);
}

int cmpfunc(const void *a, const void *b) {
    return cstring_cmp(a, b);
}

void not_null(void *pointer) {
    if (pointer == NULL) {
        perror(pointer);
    }
}

char *reading() {
    int c;

    size_t capacity_input = WORDS_CAPACITY_INCREASE;

    char *input_string = (char *) malloc(sizeof(char) * capacity_input);
    not_null(input_string);

    size_t i = 0;

    if (DEBUG) {
        while ((c = getchar()) != EOF && c != 'z') {
            input_string[i] = (char) c;
            ++i;

            if (i >= capacity_input - 1) {
                capacity_input += WORDS_CAPACITY_INCREASE;
                input_string = realloc(input_string, capacity_input);

                if (input_string == NULL) {
                    perror(input_string);
                }

            }
        }
    } else {
        while ((c = getchar()) != EOF) {
            input_string[i] = (char) c;

            ++i;
            if ((i + 1) * sizeof(char) >= capacity_input - 1) {
                capacity_input += WORDS_CAPACITY_INCREASE;
                input_string = realloc(input_string, sizeof(char) * capacity_input);

                if (input_string == NULL) {
                    exit(1);
                }
            }
        }
    }

    input_string[i] = 0;

    return input_string;
}

char **get_sorted_words(char *buffer) {
    char q = 0;
    size_t count_of_words = 0;
    size_t p = 0;
    bool space_seq = true;
    size_t capacity_words = WORDS_CAPACITY_INCREASE;
    int amp_count = 0;
    int stick_count = 0;

    char **result = (char **) malloc(sizeof(char **) * capacity_words);
    not_null(result);

    size_t word_index = 0;
    char *word = NULL;
    size_t capacity_word = 10;

    char ch;

    while (ch = buffer[p]) {
        if (q != 0) { //there is quote
            if (q == ch) { //end seq
                q = 0;
            } else {
                if (word == NULL) {
                    word_index = 0;
                    capacity_word = WORD_CAPACITY_INCREASE;
                    word = (char *)malloc(capacity_word * sizeof(char));
                }

                word[word_index] = ch;
                ++word_index;

                if ((word_index + 1) * sizeof(char) > capacity_word) {
                    capacity_word += WORD_CAPACITY_INCREASE;
                    word = realloc(word, capacity_word);
                    not_null(word);
                }
            }
            continue;
        } else if (isspace(ch)) { //space sequence
            space_seq = true;
            amp_count = stick_count = 0;

            if (word != NULL) {
                word[word_index] = '\0';
                result[count_of_words] = word;
                ++count_of_words;

                word = NULL;
                word_index = 0;
                capacity_word = WORD_CAPACITY_INCREASE;

                if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                    capacity_words += WORDS_CAPACITY_INCREASE;
                    result = realloc(result, capacity_words);
                    not_null(result);
                }
            }
        } else {
            switch (ch) {
                case '\'':
                    q = '\'';
                    break;
                case '\"':
                    q = '\"';
                    break;
                case ';': {
                    if (word != NULL) {
                        result[count_of_words] = word;
                        ++count_of_words;

                        if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                            capacity_words += WORDS_CAPACITY_INCREASE;
                            result = realloc(result, capacity_words);

                            not_null(result);
                        }
                    }
                    space_seq = true;

                    word = (char *)malloc(2 * sizeof(char));
                    word[0] = ';';
                    word[1] = 0;
                    amp_count = stick_count = 0;

                    //insert ;
                    result[count_of_words] = word;
                    ++count_of_words;

                    if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                        capacity_words += WORDS_CAPACITY_INCREASE;
                        result = realloc(result, capacity_words);

                        not_null(result);
                    }

                    word = NULL;
                    word_index = 0;
                    capacity_word = WORD_CAPACITY_INCREASE;

                    break;
                }
                case '&': {
                    if (amp_count == 0) {
                        ++amp_count;
                        stick_count = 0;

                        if (word != NULL) {
                            result[count_of_words] = word;
                            ++count_of_words;

                            if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                                capacity_words += WORDS_CAPACITY_INCREASE;
                                result = realloc(result, capacity_words);

                                not_null(result);
                            }
                        }

                        word = (char *) malloc(sizeof(char) * 3); // &&0
                        word[0] = '&';
                        word[1] = word[2] = 0;
                        word_index = 1; //!
                        space_seq = true;
                    } else if (amp_count == 1) {
                        word[1] = '&';
                        amp_count = stick_count = 0;

                        //insert &
                        result[count_of_words] = word;
                        ++count_of_words;

                        if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                            capacity_words += WORDS_CAPACITY_INCREASE;
                            result = realloc(result, capacity_words);

                            not_null(result);
                        }

                        word = NULL;
                        word_index = 0;
                        capacity_word = WORD_CAPACITY_INCREASE;
                        space_seq = true; //!

                    }
                    break;
                }
                case '|': {
                    if (stick_count == 0) {
                        ++stick_count;
                        amp_count = 0;

                        if (word != NULL) {
                            result[count_of_words] = word;
                            ++count_of_words;

                            if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                                capacity_words += WORDS_CAPACITY_INCREASE;
                                result = realloc(result, capacity_words);

                                not_null(result);
                            }
                        }

                        word = (char *) malloc(sizeof(char) * 3); // ||0
                        word[0] = '|';
                        word[1] = word[2] = 0;
                        space_seq = true;
                        word_index = 1;
                    } else if (stick_count == 1) {
                        amp_count = stick_count = 0;
                        word[1] = '|';

                        //insert word
                        result[count_of_words] = word;
                        ++count_of_words;

                        if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                            capacity_words += WORDS_CAPACITY_INCREASE;
                            result = realloc(result, capacity_words);

                            not_null(result);
                        }

                        word = NULL;
                        word_index = 0;
                        capacity_word = WORD_CAPACITY_INCREASE;
                        space_seq = true; //!
                    }
                    break;
                }
                default: {
                    if (space_seq) { //begining of the word
                        if (word != NULL) {
                            result[count_of_words] = word;
                            ++count_of_words;

                            if ((count_of_words + 1) * sizeof(char **) > capacity_words) {
                                capacity_words += WORDS_CAPACITY_INCREASE;
                                result = realloc(result, capacity_words);

                                not_null(result);
                            }
                        }
                        word_index = 0; //!
                        capacity_word = WORD_CAPACITY_INCREASE; //!
                        word = malloc(capacity_word);
                        space_seq = false;
                    }

                    word[word_index] = ch;
                    ++word_index;

                    if ((word_index + 1) * sizeof(char) > capacity_word) {
                        capacity_word += WORD_CAPACITY_INCREASE;
                        word = realloc(word, capacity_word);
                        not_null(word);
                    }
                }
            }
        }

        ++p;
    }

    if (q != 0) {
        perror("ERROR\n");
    }

    if (word != NULL) {
        result[count_of_words] = word;
        ++count_of_words;
    }

    result[count_of_words] = NULL;

    qsort(result, count_of_words, sizeof(char *), cmpfunc);

    return result;

}

void print_strings(char **words) {
    for (size_t i = 0; words[i] != NULL; ++i) {
        printf("\"%s\"\n", words[i]);
    }
}

void free_memory(char *input_string, char **words) {
    for (size_t i = 0; words[i] != NULL; ++i) {
        free(words[i]);
    }
    free(words);
    free(input_string);
}

int main() {

    char *input_string = reading();
    char **words = get_sorted_words(input_string);

    print_strings(words);

    free_memory(input_string, words);

    return 0;
}