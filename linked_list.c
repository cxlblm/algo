#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"

linked_list_node* init_linked_list_node(int v)
{
	linked_list_node* n = malloc(sizeof(linked_list_node));
	if (!n)
	{
		return NULL;
	}
	n->value = v;
	n->next = NULL;
	n->pre = NULL;
	return n;
}

int linked_list_add(linked_list* l, int v)
{
	linked_list_node* n = init_linked_list_node(v);
	if (!n)
	{
		return 0;
	}
	l->latest->next = n;
	n->pre = l->latest;
	l->latest = n;
	++l->count;
	return 1;
}

int linked_list_delete(linked_list* l, int v)
{
	if (l->latest == l->head)
	{
		return 0;
	}
	linked_list_node* n = l->head->next;
	linked_list_node* next = NULL;
	int r = 0;
	while (n)
	{
		next = n->next;
		if (n->value == v)
		{
			n->pre->next = n->next;
			n->next ? n->next->pre = n->pre : NULL;
			free(n);
			++r;
			--l->count;
		}
		n = next;
	}
	return r;
}

void linked_list_each(linked_list* l, void fn(linked_list_node* node))
{
	if (!fn)
	{
		return;
	}

	linked_list_node* n = l->head->next;
	while (n)
	{
		fn(n);
		n = n->next;
	}
}

linked_list* init_linked_list()
{
	linked_list* l = malloc(sizeof(linked_list));
	if (!l)
	{
		return NULL;
	}
	linked_list_node* n = malloc(sizeof(linked_list_node));
	if (!n)
	{
		free(l);
		return NULL;
	}
	memset(n, 0, sizeof(linked_list_node));
	l->head = n;
	l->latest = n;
	l->add = linked_list_add;
	l->delete = linked_list_delete;
	l->each = linked_list_each;
	return l;
}

void test_linked_list_delete(void)
{
	linked_list* l = init_linked_list();
	int r;
	r = l->delete(l, 1);
	assert(r == 0);
	l->add(l, 1);
	l->add(l, 1);
	r = l->delete(l, 1);
	assert(r == 2);
}

void test_linked_list_add(void)
{
	linked_list* l = init_linked_list();
	int r;
	l->add(l, 1);
	assert(l->head->next->value == 1);
	l->add(l, 2);
	assert(l->head->next->next->value == 2);
}

void test_linked_list(void)
{
	test_linked_list_delete();
	test_linked_list_add();
}
