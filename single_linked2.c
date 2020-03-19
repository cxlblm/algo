// 这个是一个带单链表

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "single_linked.h"

single_linked_list_node* init_node(int v)
{
	single_linked_list_node* node = malloc(sizeof(single_linked_list_node));
	if (node == NULL) {
		return NULL;
	}
	node->value = v;
	node->next = NULL;
	return node;
}

int single_linked_list_insert(single_linked_list* list, int value)
{
	if (list == NULL) {
		return 0;
	}
	single_linked_list_node* node = init_node(value);
	if (node == NULL) {
		return 0;
	}
	node->next = list->head->next;
	list->head->next = node;
	return 1;
}

// 从第一个之后的元素, 依次插入都当前链表中
void single_linked_list_reverse(single_linked_list* list)
{
	if (list == NULL || list->head == NULL || list->head->next == NULL || list->head->next->next == NULL) {
		return;
	}

	single_linked_list_node* head = list->head;
	single_linked_list_node* current = head->next->next;
	single_linked_list_node* next = NULL;
	head->next = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = head->next;
		head->next = current;
		current = next;
	}
}

int single_linked_free(single_linked_list** list_point)
{
	if (list_point == NULL || *list_point == NULL) {
		return 0;
	}
	single_linked_list *list = *list_point;

	single_linked_list_node *current = list->head;
	// 是否需要循环释放所有的内存, 可以在节点上添加一个free()方法
	if (current != NULL) {
		current = current->next;
		free(current);
	}
	free(list);
	*list_point = NULL;
	return 1;
}

void test_init_single_linked_list(void)
{
	single_linked_list *linked = init_single_linked_list();
	if (linked == NULL) {
		return;
	}
	assert(linked != NULL);
	assert(linked->head != NULL);
	assert(linked->head->value == 0);
}

single_linked_list* init_single_linked_list()
{
	single_linked_list* linked = malloc(sizeof(single_linked_list));
	if (linked == NULL) {
		return NULL;
	}
	single_linked_list_node* node = init_node(0);
	if (node == NULL) {
		free(linked);
		return NULL;
	}
	linked->add = single_linked_list_insert;
	linked->free = single_linked_free;
	linked->head = node;
	return linked;
}

void test_single_linked_list_insert(void)
{
	single_linked_list *linked = init_single_linked_list();
	linked->add(linked, 1);
	assert(linked->head->next->value == 1);
}

void test_single_linked_list_reverse()
{
	single_linked_list *linked = init_single_linked_list();
	linked->add(linked, 1);
	linked->add(linked, 2);
	linked->add(linked, 3);
	linked->add(linked, 4);

	single_linked_list_node *current = linked->head->next;
	assert(current->value == 4);

	current = current->next;
	assert(current->value == 3);

	current = current->next;
	assert(current->value == 2);

	current = current->next;
	assert(current->value == 1);
}

void test_single_linked2(void)
{
	test_init_single_linked_list();
	test_single_linked_list_insert();
	test_single_linked_list_reverse();
}