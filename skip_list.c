#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define MAX_LEVEL 16

static double skip_list_p = 0.5;
typedef struct _skip_list skip_list;
typedef struct _skip_list_node skip_list_node;

static int debug = 1;

struct _skip_list_node
{
	int data;
	int max_level;
	skip_list_node* forwards[];	// 使用柔性数组减少内存的占用
};

struct _skip_list
{
	int max_level;
	int level_count;
	double skip_list_p;
	skip_list_node* head;	// 链表的头结点, 不存储真实的数据
};

/*
 * 随机数这玩意搞不太明白, 先这样吧
 */
double random_double()
{
	static int s = 0;
	if (!s)
	{
		srand((unsigned)time(NULL));
		s = 1;
	}
	return rand() / (double) RAND_MAX;
}

/*
 * 生成一个随机的层数
 */
int random_level()
{
	int level = 1;
	while (random_double() < skip_list_p && level < MAX_LEVEL)
	{
		++level;
	}
	return level;
}

skip_list_node* init_skip_list_node(int data, unsigned int level)
{
	skip_list_node* node = malloc(sizeof(skip_list_node) + sizeof(skip_list_node*) * level);
	if (!node) {
		return NULL;
	}
	node->data = data;
	node->max_level = level;
	// malloc 分配的内存不会被初始化, 我们需要手动设置为NULL
	memset(node->forwards, 0, sizeof(skip_list_node*) * level); // 初始化所有的数据为0
	return node;
}

skip_list* init_skip_list()
{
	skip_list* sl = malloc(sizeof(skip_list));
	if (!sl)
	{
		return sl;
	}
	sl->max_level = MAX_LEVEL;
	sl->level_count = 1;
	skip_list_node* node = init_skip_list_node(0, MAX_LEVEL);
	if (!node)
	{
		free(sl);
		sl = NULL;
		return sl;
	}
	node->max_level = 0;
	sl->head = node;
	return sl;
}

void skip_list_insert(skip_list* sl, int value)
{
	int level = random_level();
	skip_list_node* node = init_skip_list_node(value, level);
	skip_list_node** update = malloc(sizeof(skip_list_node*) * level);
	if (!update)
	{
		return;
	}
	for (int i = 0; i < level; i++)
	{
		update[i] = sl->head;
	}

	skip_list_node* p = sl->head;
	for (int i = level - 1; i >= 0; --i)
	{
		while (p->forwards[i] != NULL && p->forwards[i]->data < value)
		{
			p = p->forwards[i];
		}
		update[i] = p;
	}

	for (int i = 0; i < level; ++i)
	{
		node->forwards[i] = update[i]->forwards[i];
		update[i]->forwards[i] = node;
	}
	if (sl->level_count < level)
	{
		sl->level_count = level;
	}
}

skip_list_node* skip_list_find(skip_list* sl, int value)
{
	skip_list_node* p = sl->head;
	for (int i = sl->level_count - 1; i >= 0; --i)
	{
		while (p->forwards[i] != NULL && p->forwards[i]->data < value)
		{
			p = p->forwards[i];
		}
	}
	if (p->forwards[0] != NULL && p->forwards[0]->data == value)
	{
		return p->forwards[0];
	} else {
		return NULL;
	}
}

void skip_list_delete(skip_list* sl, int value)
{
	skip_list_node** update = malloc(sizeof(skip_list_node*) * sl->level_count);
	skip_list_node* p = sl->head;
	for (int i = sl->level_count - 1; i >= 0; --i)
	{
		while (p->forwards[i] != NULL && p->forwards[i]->data < value)
		{
			p = p->forwards[i];
		}
		update[i] = p;
	}
	if (p->forwards[0] != NULL && p->forwards[0]->data == value) {
		for (int i = sl->level_count - 1; i >= 0; --i)
		{
			if (update[i]->forwards[i] != NULL && update[i]->forwards[i]->data == value) {
				update[i]->forwards[i] = update[i]->forwards[i]->forwards[i];
			}
		}
	}
	while (sl->level_count > 1 && sl->head->forwards[sl->level_count] == NULL) {
		--sl->level_count;
	}
}

void test_skip_list_find(void)
{
	skip_list_node* r;
	skip_list* sl = init_skip_list();
	for (size_t i = 0; i < 1000; i++)
	{
		skip_list_insert(sl, i);
	}
	r = skip_list_find(sl, 501);
	assert(r->data == 501);

	for (size_t i = 2000; i < 5000; i++)
	{
		skip_list_insert(sl, i);
	}
	r = skip_list_find(sl, 3000);
	assert(r->data == 3000);
}

void test_skip_list_delete(void)
{
	skip_list_node* r;
	skip_list* sl = init_skip_list();
	for (size_t i = 0; i < 1000; i++)
	{
		skip_list_insert(sl, i);
	}
	skip_list_delete(sl, 501);
	r = skip_list_find(sl, 501);
	assert(r == NULL);

	for (size_t i = 2000; i < 5000; i++)
	{
		skip_list_insert(sl, i);
	}
	skip_list_delete(sl, 3000);
	r = skip_list_find(sl, 3000);
	assert(r == NULL);

}

void test_skip_list(void)
{
	test_skip_list_find();
	test_skip_list_delete();
}

