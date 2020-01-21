#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

typedef struct _single_linked single_linked;

struct _single_linked {
	single_linked *next;
	int data;
};

// 判断链表是否为空
int isEmpty(single_linked* linked)
{
	return NULL == linked;
}

single_linked * create_element(int value)
{
	single_linked* linked = malloc(sizeof(single_linked));
	if (NULL == linked) {
		return NULL;
	}
	linked->data = value;
	linked->next = NULL;
	return linked;
}

single_linked * create_single_linked(int value)
{
	return create_element(value);
}

single_linked* lastEle(single_linked* linked)
{
	if (NULL == linked) {
		return linked;
	}
	while (NULL != linked->next)
	{
		linked = linked->next;
	}
	return linked;
}

// 向链表中添加元素
int append(single_linked** linked_point, int value)
{
	single_linked* linked = *linked_point;
	single_linked* ele= create_element(value);
	if (NULL == linked) {
		*linked_point = ele;
		return 1;
	} 
	single_linked* last = lastEle(linked);
	last->next = ele;
	return 1;
}

int appendNode(single_linked** linked_point, single_linked *ele)
{
	single_linked* linked = *linked_point;
	if (NULL == linked) {
		*linked_point = ele;
		return 1;
	} 
	single_linked* last = lastEle(linked);
	last->next = ele;
	return 1;
}

// 如果是第一个元素被删除了, 那么整个链表就都需要被删除
int delete(single_linked** linked_point, int value)
{
	single_linked* linked = *linked_point;
	if (isEmpty(linked)) {
		return 0;
	}
	single_linked* pre = NULL;
	// single_linked* element = linked;
	while (NULL != linked) {
		if (value == linked->data) {
			// 需要删除元素
			if (NULL == pre) {	// 如果pre等于NULL说明需要删除的是第一个元素
				*linked_point = linked->next;
			} else {
				pre->next = linked->next;
			}
			free(linked);
			return 1;
		}
		pre = linked;
		linked = linked->next;
	}
	return 0;
}

void eachMap(single_linked* linked, void fn(single_linked *))
{
	while (NULL != linked) {
		fn(linked);
		linked = linked->next;
	}
}

void printEle(single_linked* linked)
{
	printf("address: %p, ", linked);
	printf("value: %c, ", linked->data);
	printf("next: %p\n", linked->next);
}

// a -> b -> c -> d
// a <- b <- c <- d
void reverse(single_linked** linkedPoint)
{
	single_linked* linked = *linkedPoint;
	if (NULL == linked || NULL == linked->next) {
		return;
	}
	
	single_linked* next = NULL;
	single_linked* pre = NULL;
	while (linked) {
		// 上一个元素
		pre = linked->next;
		linked->next = next;
		next = linked;
		linked = pre;
	}
	*linkedPoint = next;
}

single_linked* doublePointEach(single_linked **linkedPoint)
{
	single_linked* linked = *linkedPoint;
	if (NULL == linked || NULL == linked->next) {
		return linked;
	}
	
	single_linked *middle = linked, *two = linked, *next = NULL, *pre = NULL;

	while (NULL != two && NULL != two->next) {
		two = two->next->next;
		// 上一个元素
		pre = middle->next;
		middle->next = next;
		next = middle;
		middle = pre;

	}
	linked->next = pre;
	*linkedPoint = next;
	return middle;
}

int compare(single_linked* linked, single_linked* middle)
{
	while (NULL != middle) {
		if (linked->data != middle->data) {
			return 0;
		}
		middle = middle->next;
		linked = linked->next;
	}
	return 1;
}

int isPlalindrome(single_linked **linkedPoint)
{
	single_linked* linked = *linkedPoint;
	if (NULL == linked) {
		return 0;
	}
	if (NULL == linked->next) {
		return 1;
	}
	single_linked * middle = doublePointEach(linkedPoint);
	int r = compare(*linkedPoint, middle);
	doublePointEach(linkedPoint);
	return r;
}

int checkRing(single_linked* linked)
{
	single_linked* slow = linked, * fast = linked;
	while (1) {
		if (NULL == fast || NULL == fast->next) {
			return 0;
		}
		if (fast == slow) {
			return 1;
		}
		fast = fast->next->next;
		slow = slow->next;
	}
}

void test1(void)
{
	single_linked* linked = create_single_linked('a');
	append(&linked, 'b');
	append(&linked, 'b');
	append(&linked, 'a');
	append(&linked, 'e');
	int a = isPlalindrome(&linked);
	assert(a == 0);

}

void test2(void)
{
	single_linked* linked = create_single_linked('a');
	append(&linked, 'b');
	append(&linked, 'b');
	append(&linked, 'a');
	append(&linked, 'b');

	int a = isPlalindrome(&linked);
	assert(a == 1);
}

void test3(void)
{
	single_linked* linked = create_single_linked('a');
	int a = isPlalindrome(&linked);
	assert(a == 1);

}

void test4(void)
{
	single_linked* linked = NULL;
	int a = isPlalindrome(&linked);
	assert(a == 0);

}

void testDelete(void)
{
	single_linked* linked = NULL;
	int r = delete(&linked, 0);
	assert(r == 0);
}

void testDeleteOne(void)
{

	single_linked* linked = NULL;
	append(&linked, 'b');
	int r = delete(&linked, 'b');

	assert(linked == NULL);
	assert(r == 1);
}

void testDeleteTwo(void)
{
	single_linked* linked = NULL;
	append(&linked, 'b');
	append(&linked, 'a');
	int r = delete(&linked, 'a');

	assert(linked != NULL);
	assert(r == 1);
}

void testCheckRing(void)
{
	
	single_linked* linked = NULL;
	single_linked* a = create_element('b');
	single_linked* b = create_element('b');
	single_linked* c = create_element('b');
	single_linked* d = create_element('b');
	single_linked* e = create_element('b');
	appendNode(&linked, a);
	appendNode(&linked, b);
	appendNode(&linked, c);
	appendNode(&linked, d);
	appendNode(&linked, e);
	appendNode(&linked, c);

	int r = checkRing(linked);
	assert(r == 1);

}

void testSingleLinked(void)
{
	test1();
	test2();
	test3();
	test4();
	testDelete();
	testDeleteOne();
	testDeleteTwo();
	testCheckRing();
}
