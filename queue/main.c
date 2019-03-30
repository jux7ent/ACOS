#include <stdlib.h>
#include <stdio.h>

struct QNode {
    char *key;
    struct QNode *next;
};

struct Queue {
    struct QNode *front, *rear;
};

struct QNode* newNode(char *k) {
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    temp->key = k;
    temp->next = NULL;
    return temp;
}

struct Queue *createQueue() {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}


void enQueue(struct Queue *q, char *k) {
    struct QNode *temp = newNode(k);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}


struct QNode *deQueue(struct Queue *q) {
    
    if (q->front == NULL)
        return NULL;

    
    struct QNode *temp = q->front;
    q->front = q->front->next;

    
    if (q->front == NULL) {
        q->rear = NULL;
    }

    return temp;
}

int main() {
    struct Queue *q = createQueue();
    enQueue(q, "Hello");
    enQueue(q, "world");
    deQueue(q);
    deQueue(q);
    enQueue(q, "ewqe");
    enQueue(q, "qweqwe");
    enQueue(q, "dasdas");

    struct QNode *n = deQueue(q);

    if (n != NULL)
        printf("Dequeued item is %s", n->key);

    return 0;
} 