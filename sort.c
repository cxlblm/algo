#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
冒泡排序
*/
void bubble(int* arr, size_t len)
{
	if (len <= 1) {
		return;
	}
	size_t compareNum = len - 1;
	for (size_t i = 0; i < compareNum; i++)
	{
		int flag = 0;		// 如果在某一次循环中被设置为1 说明没有交换值 就是有序的
		for (size_t j = 0; j < compareNum - i; j++)
		{
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = 1;
			}
		}
		if (!flag) {
			return;
		}
	}
}

/*
插入排序
*/
void insertion(int* arr, size_t len)
{
	if (len <= 1) {
		return;
	}
	for (size_t i = 1; i < len; i++)
	{
		// i控制遍历所有的无序元素
		int value = arr[i];		// 这里必须使用中间变量, 而不能使用索引
		int j = i - 1;		// 有序部分的最后一个元素
		for (; j >= 0; --j) {
			if (arr[j] > value) {
				arr[j + 1] = arr[j];	// 向后移动有序的元素
			} else {
				break;
			}
		}
		arr[j + 1] = value;
	}
}

/*
选择排序
*/
void select(int* arr, size_t len)
{
	if (len <= 1) {
		return;
	}
	size_t num = len - 1;
	for (size_t i = 0; i < num; i++)	// 需要比较多少次
	{
		size_t min = i, j = i + 1;
		for (; j < len; j++)
		{
			if (arr[j] < arr[min]) {	// 找到最小的元素
				min = j;
			}
		}
		if (i != min) {		// 将最小的元素与有序元素的最后一个交换位置
			int temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;
		}
	}
}

// 合并两个数组并把元素放回原始数组中
// 需要借助临时内存
void merge_array(int arr[], size_t start, size_t end)
{
	if (start > end) {
		return;
	}
	size_t middle = start + (end - start) / 2;
	size_t i = start, j = middle + 1, k = 0;
	int* temp = malloc(sizeof(int) * (end - start + 1));
	if (NULL == temp) {
		// 内存分配出错
		return;
	}
	while (i <= middle && j <= end) {
		if (arr[i] <= arr[j]) {
			temp[k] = arr[i];
			i++;
		} else {
			temp[k] = arr[j];
			j++;
		}
		k++;
	}

	size_t s = i, e = middle;
	// 如果第二个数组的元素都已经遍历完, j肯定要比元素的最大下标要大
	if (j <= end) {
		s = j;
		e = end;
	}

	while (s <= e) {
		temp[k] = arr[s];
		k++;
		s++;
	}

	for (size_t i = 0; i <=end - start; i++)
	{
		arr[start + i] = temp[i];
	}
	free(temp);
}

void merge_sort(int arr[], size_t start, size_t end)
{
	if (start >= end) {
		return;
	}
	size_t middle = start + (end - start) / 2;
	merge_sort(arr, start, middle);
	merge_sort(arr, middle + 1, end);
	merge_array(arr, start, end);
}

/*
归并排序
*/
void merge(int arr[], const size_t len)
{
	merge_sort(arr, 0, len - 1);
}

/**
 * 如果两个变量指向同一个地址, 说明是同一个变量, 就不需要交换
 * 对于使用加法, 异或的方式交换值, 会造成值变成零的情况
 *
 */
void swap(int* a, int* b)
{
	if (a == b) {
		return;
	}
	*a = *a + *b;
	*b = *a - *b;	// a + b - b
	*a = *a - *b;	// a + b - a 
	/*
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	*/
}

int partition(int arr[], size_t start, size_t end)
{
	size_t len = end - start + 1;
	size_t middle = start + (end - start) / 2;
	if (len > 10) {
		if (arr[0] > arr[end]) {
			if (arr[middle] > arr[0]) {
				swap(&arr[0], &arr[end]);
			} else if (arr[middle] > arr[end]) {
				swap(&arr[middle], &arr[end]);
			}
		} else {	// arr[0] <= arr[end]
			if (arr[middle] < arr[0]) {
				swap(&arr[0], &arr[end]);
			} else if (arr[middle] < arr[end]) {
				swap(&arr[middle], &arr[end]);
			}
		}
	}
	int pivot = arr[end];
	size_t i = start;
	for (size_t j = start; j < end; j++)
	{
		if (arr[j] < pivot) {
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[end]);
	return i;
}

void quick_c(int arr[], size_t start, size_t end)
{
	if (start >= end) {
		return;
	}
	int pivot = partition(arr, start, end);
	quick_c(arr, start, pivot - 1);
	quick_c(arr, pivot + 1, end);
}

/*
快排
*/
void quick(int arr[], size_t len)
{
	quick_c(arr, 0, len - 1);
}

size_t a_partition(int arr[], size_t start, size_t end)
{
	int pivot = arr[end];
	size_t i = start;
	for (size_t j = start; j <= end; j++)
	{
		if (arr[j] > pivot) {
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[end]);
	return i;
}

int a_c(int arr[], size_t start, size_t end, size_t order)
{
	if (start >= end) {
		return -1;
	}
	size_t pivot = a_partition(arr, start, end);
	if (pivot + 1 == order) {
		return pivot;
	} else if (order > pivot + 1) {
		return a_c(arr, pivot + 1, end, order);
	} else {
		return a_c(arr, start, pivot - 1, order);
	}
}

int* find_special_value(int arr[], size_t len, size_t order)
{
	if (len < order) {
		return NULL;
	}
	int key = a_c(arr, 0, len - 1, order);
	if (key < 0) {
		return NULL;
	}
	return arr + key;
}

/**
 * 桶排序对数据本身的要求比较严格, 如果数据本身的范围比较小比如 年龄
 */
void bucket(int arr[], size_t len)
{
	//	
}

int* array_max(int arr[], size_t len)
{
	// 空数组怎么处理, 是否需要报错处理
	if (len <= 0 || arr == NULL) {
		return NULL;
	}
	int* max = &arr[0];
	for (size_t i = 1; i < len; i++)
	{
		if (arr[i] > *max) {
			max = &arr[i];
		}
	}
	return max;
}

/**
 * 计数排序(我们需要知道数据的取值范围)
 * 现在规定数据的取值范围必须在100以内
 */
void count_sort(int arr[], size_t len)
{
	int* max = array_max(arr, len);
	if (NULL == max) {
		// 说明是一个空数组
		return;
	}

	if (*max >= 1000) {
		fprintf(stderr, "该数组不适合计数排序");
		return;
	}
	int* bucket = malloc(sizeof(int) * (*max + 1));
	if (NULL == bucket) {
		fprintf(stderr, "内存分配失败");
		return;
	}
	for (int i = 0; i <= *max; i++)
	{
		bucket[i] = 0;
	}
	for (size_t i = 0; i < len; i++)
	{
		++bucket[arr[i]];
	}
	for (int i = 1; i <= *max; i++)
	{
		bucket[i] += bucket[i - 1];
	}
	int* r = malloc(sizeof(int) * len);
	if (NULL == r) {
		// 内存分配失败
		free(bucket);
		fprintf(stderr, "内存分配失败");
		return;
	}
	int index;
	for (size_t i = len; i-- > 0;)
	{
		index = bucket[arr[i]] - 1;
		r[index] = arr[i];
		--bucket[arr[i]];
	}
	for (size_t i = 0; i < len; i++)
	{
		arr[i] = r[i];
	}
	free(bucket);
	free(r);
}

int char_to_int_index(char c)
{
	return (c == 'x' || c == 'X') ? 10 : c - '0';
}

void bucket_init_zero(int* bucket, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		bucket[i] = 0;
	}
}

/*
 * 基数排序是不是针对数组类型的元素进行排序??
 */
void radix(char* arr[], size_t len, size_t max_len)
{
	int* bucket = malloc(sizeof(int) * 11);
	if (NULL == bucket) {
		// 内存分配失败
		fprintf(stderr, "内存分配失败");
		return;
	}
	bucket_init_zero(bucket, 11);
	char** temp = malloc(sizeof(char*) * len);
	if (NULL == temp) {
		free(bucket);
		// 内存分配失败
		fprintf(stderr, "内存分配失败");
		return;
	}
	int index;
	for (size_t byte = max_len; byte-- > 0;)
	{
		for (size_t j = 0; j < len; j++)
		{
			++bucket[char_to_int_index(arr[j][byte])];
		}
		for (size_t i = 1; i < 11; i++)
		{
			bucket[i] += bucket[i - 1];
		}
		for (size_t i = len; i-- > 0; )
		{
			int int_char = char_to_int_index(arr[i][byte]);
			index = bucket[int_char] - 1;
			temp[index] = arr[i];
			--bucket[int_char];
		}
		for (size_t i = 0; i < len; i++)
		{
			arr[i] = temp[i];
		}
		bucket_init_zero(bucket, 11);
		
	}
	free(temp);
	free(bucket);
}

void test_insertion(void)
{
	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	insertion(arr, 7);

	int arr1[] = { 2, 3, 5, 5, 6, 8, 11};
	for (size_t i = 0; i < 7; i++)
	{
		assert(arr1[i] == arr[i]);
	}
}

void test_bubble(void)
{
	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	bubble(arr, 7);

	int arr1[] = { 2, 3, 5, 5, 6, 8, 11};
	for (size_t i = 0; i < 7; i++)
	{
		assert(arr1[i] == arr[i]);
	}
}

void test_select(void)
{

	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	select(arr, 7);

	int arr1[] = { 2, 3, 5, 5, 6, 8, 11};
	for (size_t i = 0; i < 7; i++)
	{
		assert(arr1[i] == arr[i]);
	}
}

void test_merge_sort(void)
{
	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	merge(arr, 7);
	int arr1[] = { 2, 3, 5, 5, 6, 8, 11};
	for (size_t i = 0; i < 7; i++)
	{
		assert(arr1[i] == arr[i]);
	}

}

void test_quick_sort(void)
{
	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	quick(arr, 7);

	int arr1[] = { 2, 3, 5, 5, 6, 8, 11};
	for (size_t i = 0; i < 7; i++)
	{
		assert(arr1[i] == arr[i]);
	}
}

void test_find_special_value(void)
{
	int arr[] = { 11, 2, 8, 4, 23, 10 };
	int* r = find_special_value(arr, 6, 1);
	assert(*r == 23);

	r = find_special_value(arr, 6, 3);
	assert(*r == 10);

}

void test_count_sort(void)
{
	int arr[] = {11, 25, 2, 12, 34, 9, 9, 12, 9, 10, 33};
	count_sort(arr, 11);

	int r[] = {2, 9, 9, 9, 10, 11, 12,  12, 25, 33, 34};
	for (size_t i = 0; i < 11; i++)
	{
		assert(r[i] == arr[i]);
	}
}

void test_radix_sort(void)
{
	char* arr[] = {
		"220283199207278653",
		"140226198806257895",
		"420111198806247774",
		"350702199708039851",
		"140411197503175077",
		"321002197102154319",
		"420900196312102597",
		"65432619750317507X",
		"230503199911261712",
		"152526199207278752",
	};
	radix(arr, 10, 18);
	char* r[] = {
		"140226198806257895",
		"140411197503175077",
		"152526199207278752",
		"220283199207278653",
		"230503199911261712",
		"321002197102154319",
		"350702199708039851",
		"420111198806247774",
		"420900196312102597",
		"65432619750317507X",
	};
	for (size_t i = 0; i < 10; i++)
	{
		assert(r[i] == arr[i]);
	}
}


void test_sort(void)
{
	test_find_special_value();
	test_insertion();
	test_bubble();
	test_select();
	test_merge_sort();
	test_count_sort();
	test_radix_sort();
}

