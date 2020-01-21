#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "array_stack.h"
#define NUM 30

linked_stack_node* pop(array_stack* s)
{
	if (s->len <= 0) {
		return NULL;
	}
	--s->len;
	linked_stack_node *n = s->n[s->len];
	s->n[s->len] = NULL;
	return n;
};

int push(array_stack* s, linked_stack_node* n)
{
	s->n[s->len] = n;
	++s->len;
	return s->len;
};

int count(array_stack* s)
{
	return s->len;
};

array_stack* createStack(void)
{
	array_stack* s = malloc(sizeof(array_stack));
	if (NULL == s) {
		return NULL;
	}
	linked_stack_node** n = malloc(sizeof(linked_stack_node**) * NUM);
	if (NULL == n) {
		return NULL;
	}
	s->n = n;
	s->len = 0;
	s->total = NUM;
	s->pop = pop;
	s->push = push;
	s->count = count;
	return s;
}

void test_create(void)
{
	array_stack* s = createStack();
	assert(NULL != s);
}

void test_pop()
{
	array_stack* s = createStack();
	linked_stack_node* n = malloc(sizeof(linked_stack_node));
	int r = s->push(s, n);
	assert(r == 1);
	linked_stack_node* pushN = s->pop(s);
	assert(pushN == n);
}

void test_push()
{
	array_stack* s = createStack();
	linked_stack_node* n = malloc(sizeof(linked_stack_node));
	assert(n != NULL);
	n->data = "aaaaaaa";
	int r = s->push(s, n);
	assert(r == 1);

	linked_stack_node* n1 = malloc(sizeof(linked_stack_node));
	assert(n1 != NULL);
	n->data = "bbbbbb";
	r = s->push(s, n1);
	assert(r == 2);


	linked_stack_node* node = s->pop(s);
	assert(node == n1);
	node = s->pop(s);
	assert(node == n);

}

void test_array_stack()
{
	test_create();
	test_pop();
}