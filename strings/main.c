#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG false

typedef struct Node Node;
typedef struct Queue Queue;

struct Node {
    char symbol_;
    Node *next_;
};

struct Queue {
    Node *tail_;
    Node *head_;
    size_t size_;
    size_t max_size_;
};

Node *newNode(Node *next) {
    Node *new = (Node *)malloc(sizeof(Node));
    //new->symbol_ = '\0';
    new->next_ = next;

    return new;
}

Queue *newQueue(size_t max_size) {
    Queue *new = (Queue *)malloc(sizeof(Queue));
    new->tail_ = newNode(NULL);
    for (size_t i = 1; i < max_size; ++i) {
        new->tail_ = newNode(new->tail_);
    }
    new->head_ = new->tail_;
    new->size_ = 0;
    new->max_size_ = max_size;

    return new;
}

void clearAndPrintQueue(Queue *queue, bool print) {
    if (!print) {
        queue->size_ = 0;
        queue->head_ = queue->tail_;
    } else {
        Node *tail = queue->tail_;
        while (queue->size_) {
            printf("%c", queue->tail_->symbol_);
            Node *next = queue->tail_->next_;
            queue->tail_ = next;
            --queue->size_;
        }

        queue->head_ = queue->tail_ = tail;
        printf("%c", '\n');
    }
}

void addSymbol(Queue *queue, char ch) {
    /*if (!queue) {
        perror("queue is NULL");
        exit(1);
    }*/

    if (queue->size_) {
        if (queue->size_ < queue->max_size_) { //just to head
            queue->head_ = queue->head_->next_;
            ++queue->size_;
        } else {
            printf("%c", queue->tail_->symbol_);
            Node *next_tail = queue->tail_->next_;
            queue->tail_->next_ = NULL;
            queue->head_->next_ = queue->tail_;
            queue->head_ = queue->tail_;
            queue->tail_ = next_tail;
        }
    } else { //0 nodes
        ++queue->size_;
    }

    queue->head_->symbol_ = ch;
}

bool isValid(int symbol) {
    return !((symbol < 32 && symbol != '\t') || symbol > 126);
}

void print_words(FILE *fp, size_t min_size_word) {
    Queue *queue = newQueue(min_size_word);
    int ch;

    //int stop_symbol = DEBUG ? 'k' : EOF;

    while ((ch = fgetc(fp)) != EOF) {
        if (!((ch < 32 && ch != '\t') || ch > 126)) {
            if (queue->size_) {
                if (queue->size_ < queue->max_size_) { //just to head
                    queue->head_ = queue->head_->next_;
                    ++queue->size_;
                } else {
                    printf("%c", queue->tail_->symbol_);
                    Node *next_tail = queue->tail_->next_;
                    queue->tail_->next_ = NULL;
                    queue->head_->next_ = queue->tail_;
                    queue->head_ = queue->tail_;
                    queue->tail_ = next_tail;
                }
            } else { //0 nodes
                ++queue->size_;
            }

            queue->head_->symbol_ = ch;
        } else {
            //clearAndPrintQueue(queue, queue->size_ >= queue->max_size_);
            if ((queue->size_ < queue->max_size_)) {
                queue->size_ = 0;
                queue->head_ = queue->tail_;
            } else {
                Node *tail = queue->tail_;
                while (queue->size_) {
                    printf("%c", queue->tail_->symbol_);
                    Node *next = queue->tail_->next_;
                    queue->tail_ = next;
                    --queue->size_;
                }

                queue->head_ = queue->tail_ = tail;
                printf("%c", '\n');
            }
        }
    }
    if ((queue->size_ < queue->max_size_)) {
        queue->size_ = 0;
        queue->head_ = queue->tail_;
    } else {
        Node *tail = queue->tail_;
        while (queue->size_) {
            printf("%c", queue->tail_->symbol_);
            Node *next = queue->tail_->next_;
            queue->tail_ = next;
            --queue->size_;
        }

        queue->head_ = queue->tail_ = tail;
        printf("%c", '\n');
    }
}

int main(int argc, char **argv) {
    if (argc == 1) { //there isn't arguments
        print_words(stdin, 4);
        return 0;
    }

    for (size_t i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        print_words(fp, 4);

        fclose(fp);
    }

    return 0;
}