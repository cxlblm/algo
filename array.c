#include <stdio.h>

void deleteArray(int* arr, size_t index, size_t len)
{
	if (len <= index) {
		// 说明出错了
		printf("error");
		return;
	}
	--len;
	for (size_t i = index; i < len; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[len] = 0;
}

void each(int* arr, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}
}


int testArray(void)
{
	// 我们只能在定义数组的时候确定数组的长度(数组) 
	// 数组传到函数内部就变成了指针, 就不能再通过sizeof获取到数组的长度

	int arr[] = { 1, 2, 3, 4, 5, 6 };
	each(arr, 6);
	delete(arr, 1, 6);

	each(arr, 6);

	return 0;
}