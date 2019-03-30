#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPACITY_STRING_INCREASE 200
#define \
    ADD_SYMBOL(node, symbol) \
    ({ \
        node->data_[node->index_] = symbol; \
        ++node->index_; \
    })
#define DEBUG false

typedef struct Node Node;
typedef struct Queue Queue;

struct Node {
    char *data_;
    Node *next_;
    size_t index_;
    size_t capacity_;
};

struct Queue {
    Node *tail_;
    Node *head_;
    size_t size_;
    size_t max_size_;
};

Node *newNode(Node *next) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->data_ = NULL;
    new->index_ = new->capacity_ = 0;
    new->next_ = next;

    return new;
}

Queue *newQueue(size_t max_size) {
    Queue *new = (Queue *)malloc(sizeof(Queue));
    new->head_ = new->tail_ = NULL;
    new->size_ = 0;
    new->max_size_ = max_size;

    return new;
}

void node_realloc_data(Node **node) {
    (*node)->capacity_ += CAPACITY_STRING_INCREASE;
    (*node)->data_ = (char *)realloc((*node)->data_, (*node)->capacity_);

    if (!(*node)->data_) {
        perror((*node)->data_);
        exit(1);
    }
}

Node *getNode(Queue *queue) {
    if (!queue) {
        perror("queue is NULL");
        exit(1);
    }

    if (queue->size_) {
        if (queue->size_ < queue->max_size_) { //just to head
            Node *new = newNode(NULL);
            queue->head_->next_ = new;
            queue->head_ = new;
            ++queue->size_;
        } else {
            Node *next_tail = queue->tail_->next_;
            queue->tail_->index_ = 0;
            queue->tail_->next_ = NULL;
            queue->head_->next_ = queue->tail_;
            queue->head_ = queue->tail_;
            queue->tail_ = next_tail;
        }
    } else { //0 nodes
        queue->head_ = queue->tail_ = newNode(NULL);
        ++queue->size_;
    }

    if (!queue->head_->data_) {
        node_realloc_data(&queue->head_);
    }


    return queue->head_;
}

Queue *get_last_strs(FILE *fp, size_t count_strs) {
    Queue *result = newQueue(count_strs);
    Node *curNode = NULL;
    int ch;

    int stop_symbol = DEBUG ? 'k' : EOF;

    while ((ch = fgetc(fp)) != stop_symbol) {
        if (!curNode) {
            curNode = getNode(result);
        }

        ADD_SYMBOL(curNode, ch);
        if (curNode->index_ >= curNode->capacity_) {
            node_realloc_data(&curNode);
        }

        if (ch == '\n') { //add string
            ADD_SYMBOL(curNode, '\0');
            curNode = NULL;
        }
    }

    if (curNode != NULL) {
        ADD_SYMBOL(curNode, '\0');
        curNode = NULL;
    }

    return result;
}

void print_strings(Queue *queue) {
    while (queue->tail_) {
        printf("%s", queue->tail_->data_);

        Node *next = queue->tail_->next_;
        free(queue->tail_->data_);
        free(queue->tail_);
        queue->tail_ = next;
    }
}

int main(int argc, char **argv) {
    Queue *queue = NULL;

    if (argc == 1) { //there is no arguments
         queue = get_last_strs(stdin, 10);
         print_strings(queue);
         free(queue);
         return 0;
    }

    for (size_t i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");

        printf("==>%s<==\n", argv[i]);

        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        queue = get_last_strs(fp, 10);
        print_strings(queue);
        free(queue);

        fclose(fp);
    }

    return 0;
}