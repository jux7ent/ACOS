#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <zconf.h>

#define CAPACITY_STRING_INCREASE 100

struct node {
    struct node *p_next;
    char *str;
};

void add_string_to_queue(char **string, struct node **left, struct node **right) {
    free((*left)->str);
    (*left)->str = *string;

    struct node *temp = (*left)->p_next;
    (*left)->p_next = NULL;
    (*right)->p_next = *left;
    *right = *left;
    *left = temp;
}

struct  node *counting_info(FILE *fp) {
    struct node *left_node, *right_node;
    left_node = right_node = (struct node *)malloc(sizeof(struct node *));
    size_t strings_count = 0;
    int ch;

    size_t capacity_string = CAPACITY_STRING_INCREASE;
    char *string = (char *)malloc(capacity_string);
    size_t index_str = 0;

    while ((ch = fgetc(fp)) != EOF) {
        string[index_str] = (char)ch;
        ++index_str;

        if (index_str * sizeof(char) > capacity_string) {
            capacity_string += CAPACITY_STRING_INCREASE;
            string = (char *)realloc(string, capacity_string);

            if (string == NULL) {
                perror("string is null");
            }
        }

        if (ch == '\n') { //add word
            if (strings_count < 10) {
                if (strings_count == 0) {
                    left_node->str = string;
                } else {
                    struct node *new_node = (struct node *)malloc(sizeof(struct node));
                    new_node->str = string;
                    new_node->p_next = NULL;
                    right_node->p_next = new_node;
                    right_node = new_node;
                }
                ++strings_count;
            } else {
                ++strings_count; //not necessary
                string[index_str] = '\0';
                add_string_to_queue(&string, &left_node, &right_node);
            }
            capacity_string = CAPACITY_STRING_INCREASE;
            index_str = 0;
            string = (char *)malloc(capacity_string);
        }
    }

    if (index_str) {
        string[index_str] = '\n';
        add_string_to_queue(&string, &left_node, &right_node);
    }

    return left_node;
}

void print_and_flush(struct node *left_node) {
    if (left_node == NULL) {
        perror("left_node is null");
        return;
    }

    do {
        printf("%s", left_node->str);
        free(left_node->str);
        left_node = left_node->p_next;
    } while (left_node != NULL);
}

int main(int argc, char **argv) {
    struct node *left_node;

	if (argc == 1) {
        left_node = counting_info(stdin);
        print_and_flush(left_node);
        return 0;
	}

	for (size_t i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");

        printf("==>%s<==\n", argv[i]);

        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        left_node = counting_info(fp);
        print_and_flush(left_node);

        fclose(fp);
    }

	return 0;
}
