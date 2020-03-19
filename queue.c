#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

int queue_push(queue* queue, void *v)
{
    if (!queue) {
        return 0;
    }
    queue_node* node = init_queue_node(v);
    if (!node) {
        return 0;
    }
    queue->last->next = node;
    node->prev = queue->last;
    queue->last = node;
    ++queue->len;
    return queue->len;
};

void* queue_pop(queue* queue)
{
    if (!queue) {
        return NULL;
    }
    if (!queue->head) {
        return NULL;
    }
    queue_node* n = queue->head->next;
    if (!n) {
        return NULL;
    }
    queue->head->next = n->next;
    if (n->next) {
        n->next->prev = queue->head;
    }
    --queue->len;
    if (!n->next) {
        queue->last = queue->head;
    }
    return n->v;
};

int queue_get_len(queue* queue)
{
    return queue->len;
}

queue_node* init_queue_node(void *v)
{
    queue_node* n = malloc(sizeof(queue_node));
    if (!n) {
        return n;
    }
    n->v = v;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

queue* init_queue()
{
    queue* queue = malloc(sizeof(queue));
    if (!queue) {
        return NULL;
    }

    queue_node* n = init_queue_node(NULL);
    if (!n) {
        free(queue);
        return NULL;
    }
    queue->head = n;
    queue->last = queue->head;
    queue->len = 0;
    queue->push = queue_push;
    queue->pop = queue_pop;
    queue->get_len = queue_get_len;
    return queue;
}

void test_queue(void)
{
	queue *q = init_queue();
    q->push(q, NULL);
    assert(q->get_len(q) == 1);
    assert(q->pop(q) == NULL);
    int a = 0;
    q->push(q, &a);
    int b = 1;
    q->push(q, &b);
    int c = 1;
    q->push(q, &c);
    assert(q->get_len(q) == 3);
    assert(&a == q->pop(q));
    q->pop(q);
    assert(&c == q->pop(q));
    assert(q->head == q->last);
}
