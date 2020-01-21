#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_stack.h"

int linked_stack_push(linked_stack* s, linked_stack_node* n)
{
	linked_stack_node* o = s->head->next;
	n->next = o;
	s->head->next = n;
	++s->len;
	return s->len;
}

linked_stack_node* linked_stack_pop(linked_stack* s)
{
	if (s->len <= 0) {
		return NULL;
	}
	linked_stack_node* first = s->head->next;
	s->head->next = s->head->next == NULL ? NULL : s->head->next->next;
	--s->len;
	return first;
}

int linked_stack_count(linked_stack* s)
{
	return s->len;
};

linked_stack* create_linked_stack()
{
	linked_stack* s = malloc(sizeof(linked_stack));
	if (s == NULL) {
		return NULL;
	}
	linked_stack_node* head = malloc(sizeof(linked_stack_node));
	if (head == NULL) {
		return NULL;
	}
	head->data = NULL;
	head->next = NULL;
	s->head = head;
	return s;
}


linked_stack* test_create_linked_stack()
{
	linked_stack* s = create_linked_stack();
	assert(s != NULL);
	return s;
	
};

void test_linked_stack_push(void)
{
	int r = 0;
	linked_stack* s = test_create_linked_stack();
	linked_stack_node* n = malloc(sizeof(linked_stack_node));
	assert(n != NULL);
	r = s->push(s, n);
	assert(r == 1);
	linked_stack_node* n1 = malloc(sizeof(linked_stack_node));
	assert(n1 != NULL);
	r = s->push(s, n1);
	assert(r == 2);

}

void test_linked_stack(void)
{
	test_create_linked_stack();
}
