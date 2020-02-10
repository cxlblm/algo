#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _heap heap;
extern void swap(int* a, int* b);

struct _heap
{
	int* arr;
	size_t num;	// 已经存储的元素个数
	int offset;
	size_t size;	// 元素的最大个数
};

int heap_scale(heap* h)
{
	if (h->num < h->size)
	{
		return 0;
	}
	int* p = realloc(h->arr, sizeof(int) * h->size * 2);
	if (!p) {
		// 分配内存失败
		return -1;
	}
	h->arr = p;
	return 1;
}

int heap_insert(heap* h, int value)
{
	int r = heap_scale(h);
	if (r == -1) {
		return 0;
	}
	h->arr[h->offset] = value;
	++h->offset;
	++h->num;

	// 堆化
	int i = h->num;
	while (i / 2 > 0 && h->arr[i] > h->arr[i / 2])
	{
		swap(&h->arr[i], &h->arr[i / 2]);
		i = i / 2;
	}
	return 1;
}

void heap_heapify(int* arr, size_t count, size_t start)
{
	while (1)
	{
		size_t max_pos = start;
		if (start * 2 <= count && arr[start] < arr[start*2])		// 查看左节点的值是否大于顶点的值
		{
			max_pos = start * 2;
		}
		if (start * 2 + 1 <= count && arr[max_pos] < arr[start * 2 + 1]) // 查看右节点的值是否大于新的最大值
		{
			max_pos = start * 2 + 1;
		}
		if (max_pos == start)
		{
			break;
		}
		swap(&arr[start], &arr[max_pos]);
		start = max_pos;
	}
}

int heap_remove_max(heap* h, int value)
{
	if (h->num <= 0) {
		return 0;
	}

	h->arr[1] = h->arr[h->offset];	// 堆顶的值交换到最后一个元素的值
	--h->offset;
	--h->num;
	// 重新堆化
	heap_heapify(h->arr, h->num, 1);
	return 1;
}

heap* init_heap(size_t size)
{
	heap* h = malloc(sizeof(heap));
	if (!h)
	{
		return NULL;
	}
	int* arr = calloc(sizeof(int), size);
	if (!arr)
	{
		free(h);
		return NULL;
	}
	h->arr = arr;
	h->num = 0;
	h->offset = 1;
	h->size = size;
	return h;
}

void build_heap(int* arr, size_t len)
{
	for (size_t i =  len / 2; i >= 1; --i)
	{
		heap_heapify(arr, len, i);
	}
}

// 堆排序和冒泡排序有点类似
// 每次都是找到最大或者最小的元素放到最后, 每次都是取到堆顶的元素, 然后再重新堆化
void heap_sort(int* arr, size_t len)
{
	build_heap(arr, len);
	size_t k = len;
	while (k > 1)
	{
		swap(&arr[1], &arr[k]);
		--k;
		heap_heapify(arr, k, 1);
	}
}

void test_heap_insert(void)
{
	heap* p = init_heap(8);
	int r;
	r = heap_insert(p, 8);
	assert(p->arr[1] == 8);
	heap_insert(p, 9);
	assert(p->arr[1] == 9);
}

void test_heap_remove_max(void)
{
	heap* p = init_heap(8);
	int r;

	r = heap_insert(p, 15);
	r = heap_insert(p, 20);
	r = heap_insert(p, 4);
	r = heap_insert(p, 8);
	r = heap_insert(p, 23);
	assert(p->arr[1] == 23);
}

void test_heap_sort(void)
{
	int arr[] = {0, 4, 13, 5, 2, 45, 23, 8, 10 };
	heap_sort(arr, (sizeof(arr) / sizeof(int)) - 1);

	int arr1[] = {0, 2, 4, 5, 8, 10, 13, 23, 45, };

	for (size_t i = 0; i < 9; i++)
	{
		assert(arr1[i] == arr[i]);
	}
}


void test_heap(void)
{
	test_heap_insert();
	test_heap_remove_max();
	test_heap_sort();
}
