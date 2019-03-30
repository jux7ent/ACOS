#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <zconf.h>

struct node {
    struct node *p_next;
    char ch;
};

typedef struct node node;

void print_and_flush(node *left_node, bool need_print);

int valid_symbol(int symbol) {
    if ((symbol < 32 && symbol != '\t') || symbol > 126) {
        return 0;
    } else {
        return symbol;
    }
}

void add_symbol(node **left, char ch) {
    printf("%c", (*left)->ch);
    (*left)->ch = ch;
    *left = (*left)->p_next;
}

node *init_nodes() { //allocate nodes
    node *node1 = (node *)malloc(sizeof(node));
    node *node2 = (node *)malloc(sizeof(node));
    node *node3 = (node *)malloc(sizeof(node));
    node *node4 = (node *)malloc(sizeof(node));

    node1->ch = '\0';
    node1->p_next = node2;

    node2->ch = '\0';
    node2->p_next = node3;

    node3->ch = '\0';
    node3->p_next = node4;

    node4->ch = '\0';
    node4->p_next = node1;

    return node1;
}

void m_free(node *left) {
    node *tmp;
    while (left) {
        tmp = left->p_next;
        free(left);
        left = tmp;
    }
}

void print_strings(FILE *fp) {
    node *left_node = init_nodes();
    size_t symbols_count = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch = valid_symbol(ch)) { //valid symbol
            ++symbols_count;
            bool queue_is_full = symbols_count > 4;

            if (queue_is_full) {
                add_symbol(&left_node, (char)ch);
            } else {
                node *tmp = left_node;
                while (tmp->ch) {
                    tmp = tmp->p_next;
                }
                tmp->ch = (char)ch;
            }
        } else {
            print_and_flush(left_node, symbols_count >= 4);
            symbols_count = 0;
        }
    }

    if (symbols_count) {
        print_and_flush(left_node, symbols_count >= 4);
    }

    m_free(left_node);
}

void print_and_flush(node *left_node, bool need_print) {
    if (left_node == NULL) {
        perror("left_node is null");
        return;
    }

    while (left_node->ch) {
        if (need_print) {
            printf("%c", left_node->ch);
        }
        left_node->ch = '\0';
        left_node = left_node->p_next;
    }

    if (need_print) {
        printf("\n");
    }
}

int main(int argc, char **argv) {
	if (argc == 1) {
        print_strings(stdin);
        return 0;
	}

	for (size_t i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        print_strings(fp);

        fclose(fp);
    }

	return 0;
}
