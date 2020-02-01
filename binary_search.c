#include <stdio.h>
#include <assert.h>

// 有序输出中不存在重复的元素
int equal(int arr[], size_t len, int value)
{
	if (arr == NULL || len < 1) {
		return -1;
	}
	size_t low = 0;
	size_t high = len - 1;
	while (low <= high) {
		int middle = low + ((high - low) >> 1);
		if (arr[middle] == value) {
			return middle;
		} else if (arr[middle] < value) {

			low = middle + 1;
		} else {
			high = middle - 1;
		}
	}
	return -1;
}

int first_equal(int arr[], size_t len, int value)
{
	if (arr == NULL || len < 1) {
		return -1;
	}
	size_t low = 0;
	size_t high = len - 1;
	while (low <= high) {
		int middle = low + ((high - low) >> 1);
		if (arr[middle] >= value) {
			high = middle - 1;
		} else {
			low = middle + 1;
		}
	}
	if (low < len && arr[low] == value) {
		return low;
	}
	return -1;
}

int first_equal_easy(int arr[], size_t len, int value)
{
	if (arr == NULL || len < 1) {
		return -1;
	}
	size_t low = 0;
	size_t high = len - 1;
	while (low <= high) {
		int middle = low + ((high - low) >> 1);
		if (arr[middle] > value) {
			high = middle - 1;
		} else if (arr[middle] < value) {
			low = middle + 1;
		} else {
			if ((middle == 0) || (arr[middle - 1] != value)) {
				return middle;
			} else {
				high = middle - 1;
			}
		}
	}
	return -1;
}

int last_equal(int arr[], size_t len, int value)
{
	if (arr == NULL || len < 1) {
		return -1;
	}
	size_t low = 0;
	size_t high = len - 1;
	while (low <= high) {
		int middle = low + ((high - low) >> 1);
		if (arr[middle] > value) {
			high = middle - 1;
		} else {
			low = middle + 1;
		}
	}
	if (high < len && arr[high] == value) {
		return high;
	}
	return -1;
}

int last_equal_easy(int arr[], size_t len, int value)
{
	if (arr == NULL || len < 1) {
		return -1;
	}
	size_t low = 0;
	size_t high = len - 1;
	while (low <= high) {
		int middle = low + ((high - low) >> 1);
		if (arr[middle] > value) {
			high = middle - 1;
		} else if (arr[middle] < value) {
			low = middle + 1;
		} else {
			if ((middle == len - 1) || (arr[middle + 1] != value)) {
				return middle;
			} else {
				low = middle + 1;
			}
		}
	}
	return -1;
}

int first_gte(int arr[], size_t len, int value)
{
	if (arr == NULL || len < 1) {
		return -1;
	}
	size_t low = 0;
	size_t high = len - 1;
	while (low <= high) {
		int middle = low + ((high - low) >> 1);
		if (arr[middle] >= value) {
			if (middle == 0 || arr[middle - 1] < value) {
				return middle;
			} else {
				high = middle - 1;
			}
		} else {
			low = middle + 1;
		}
	}
	return -1;
}

int last_lte(int arr[], size_t len, int value)
{
	if (arr == NULL || len < 1) {
		return -1;
	}
	size_t low = 0;
	size_t high = len - 1;
	while (low <= high) {
		int middle = low + ((high - low) >> 1);
		if (arr[middle] > value) {
			high = middle - 1;
		} else {
			if (middle == len - 1 || arr[middle + 1] > value) {
				return middle;
			} else {
				low = middle = 1;
			}
		}
	}
	return -1;


}

void test_equal(void)
{
	size_t len;
	int r;
	int arr[] = { 11, 23, 34, 45, 46, 49, 50, 51, 52, 55 };
	len = sizeof(arr) / sizeof(int);
	r = equal(arr, len, 46);
	assert(r == 4);
	r = equal(arr, len, 48);
	assert(r == -1);
	int arr1[] = { 1 };
	len = sizeof(arr1) / sizeof(int);
	r = equal(arr1, len, 1);
	assert(r == 0);
}

void test_first_equal(void)
{
	int arr[] = { 11, 23, 34, 45, 46, 49, 49, 49, 50, 51, 52, 55};
	size_t len = sizeof(arr) / sizeof(int);
	int r = first_equal(arr, len, 49);
	assert(r == 5);
	r = first_equal(arr, len, 48);
	assert(r == -1);
}

void test_first_equal_easy(void)
{
	int arr[] = { 11, 23, 34, 45, 46, 49, 49, 49, 50, 51, 52, 55};
	size_t len = sizeof(arr) / sizeof(int);
	int r = first_equal_easy(arr, len, 49);
	assert(r == 5);
	r = first_equal_easy(arr, len, 48);
	assert(r == -1);
}

void test_last_equal(void)
{
	size_t len;
	int r;
	int arr[] = { 11, 23, 34, 45, 46, 49, 49, 49, 50, 51, 52, 55};
	len = sizeof(arr) / sizeof(int);
	r = last_equal(arr, len, 49);
	assert(r == 7);
	r = last_equal(arr, len, 48);
	assert(r == -1);

}

void test_last_equal_easy(void)
{
	size_t len;
	int r;
	int arr[] = { 11, 23, 34, 45, 46, 49, 49, 49, 50, 51, 52, 55};
	len = sizeof(arr) / sizeof(int);
	r = last_equal_easy(arr, len, 49);
	assert(r == 7);
	r = last_equal_easy(arr, len, 48);
	assert(r == -1);
}

void test_first_gte(void)
{
	size_t len;
	int r;
	int arr[] = { 11, 23, 34, 45, 46, 49, 49, 49, 50, 51, 52, 55};
	len = sizeof(arr) / sizeof(int);
	r = first_gte(arr, len, 49);
	assert(r == 8);
	r = first_gte(arr, len, 90);
	assert(r == -1);
}

void test_last_lte(void)
{
	size_t len;
	int r;
	int arr[] = { 11, 23, 34, 45, 46, 49, 49, 49, 50, 51, 52, 55};
	len = sizeof(arr) / sizeof(int);
	r = last_lte(arr, len, 49);
	assert(r == 7);
	r = last_lte(arr, len, 44);
	assert(r == 2);

}

void test_binary_search(void)
{
	test_equal();
	test_first_equal();
	test_first_equal_easy();
	test_last_equal();
	test_last_equal_easy();

}