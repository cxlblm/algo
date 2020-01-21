#include <stdio.h>
#include <assert.h>

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

void testInsertion(void)
{
	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	insertion(arr, 7);

	for (size_t i = 0; i < 7; i++)
	{
		printf("%d\n", arr[i]);
	}
}

void testBubble(void)
{
	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	bubble(arr, 7);

	for (size_t i = 0; i < 7; i++)
	{
		printf("%d\n", arr[i]);
	}
}

void testSelect(void)
{

	int arr[] = { 11, 2, 5, 8, 3, 5, 6 };
	select(arr, 7);

	int arr1[] = { 2, 3, 5, 5, 6, 8, 11};
	for (size_t i = 0; i < 7; i++)
	{
		assert(arr1[i] == arr[i]);
	}
}

void testSort(void)
{
	testInsertion();
	// testBubble();
	// testSelect();
}

