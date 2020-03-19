#pragma once

#ifndef LIST_HEAD_H
#define LIST_HEAD_H

#define list_entry(ptr, type, member) \
	((type*)((char*)(ptr) - (char*)(&(((type *)0)->member)))

typedef struct _list_head list_head;

struct _list_head
{
	list_head* prev;
	list_head* next;
};

void _init(list_head* head);
void __append(list_head* head, list_head *node);
void _treaverse(list_head* head, void (*fn)(list_head* node));
#endif // LIST_HEAD_H

