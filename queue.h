#pragma once
#ifndef QUEUE_H
typedef struct _queue_node queue_node;
typedef struct _queue queue;

// 所有关于声明的东西都应该放到头文件中
struct _queue_node
{
	void* v;
	queue_node* prev;
	queue_node* next;
};

struct _queue
{
	struct _queue_node* head;
	struct _queue_node* last;
	int len;
	int (*push)(queue*, void *);
	void* (*pop)(queue*);
	int (*get_len)(queue*);
};

queue_node* init_queue_node(void* v);
queue* init_queue();
#endif // !QUEUE_H


