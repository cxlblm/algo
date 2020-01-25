#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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
		int value = arr[i];		// 这里必须使用中间变量, 而不能使用索引
		int j = i;
		for (; j > 0; --j) {
			if (value < arr[j - 1]) {
				arr[j] = arr[j - 1];
			} else {
				break;
			}
		}
		arr[j] = value;
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
	for (size_t i = 0; i < num; i++)
	{
		size_t min = i, j = i + 1;
		for (; j < len; j++)
		{
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		if (i != min) {
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
	size_t middle = (start + end) / 2;
	size_t i = start, j = middle + 1, k = 0;
	int* temp = malloc(sizeof(int) * (end - start + 1));
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

	for (size_t i = 0; i <=end - start ; i++)
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
	size_t middle = (start + end) / 2;
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

int a_partition(int arr[], size_t start, size_t end)
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
	int pivot = a_partition(arr, start, end);
	if (pivot + 1 == order) {
		return pivot;
	} else if (order > pivot + 1) {
		return a_c(arr, pivot + 1, end, order);
	} else {
		return a_c(arr, start, pivot - 1, order);
	}
}

int a(int arr[], size_t len, size_t order)
{
	if (len < order) {
		return -1;
	}
	return a_c(arr, 0, len - 1, order);
}

int find_special_value(int arr[], size_t len, size_t order)
{
	int k = a(arr, len, order);
	if (k != -1) {
		return arr[k];
	}
	// error 怎么处理
	return ;
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

void test_merge_sort()
{
	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	merge(arr, 7);
	int arr1[] = { 2, 3, 5, 5, 6, 8, 11};
	for (size_t i = 0; i < 7; i++)
	{
		assert(arr1[i] == arr[i]);
	}

}

void test_quick_sort()
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
	int r = find_special_value(arr, 6, 1);
	assert(r == 23);

	r = find_special_value(arr, 6, 3);
	assert(r == 10);

}

void test_sort(void)
{
	test_find_special_value();
	test_insertion();
	test_bubble();
	test_select();
	test_merge_sort();
}

