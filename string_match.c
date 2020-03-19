#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

extern uint64_t time33(char* str, size_t len);

int bf(char* needle, size_t needle_len, char* str, size_t str_len)
{
	if (needle_len > str_len) {
		return -1;
	}

	for (size_t j = 0; j < str_len; j++)
	{
		// 如果剩余的字符串小于模式字符串, 就直接失败
		if (str_len - j < needle_len) {
			return -1;
		}
		for (size_t i = 0; i < needle_len; i++)
		{
			if (str[i + j] != needle[i]) {
				goto LOOP;
			}
		}
		return j;
	LOOP:;
	}
	return -1;
}

int rk(char* needle, size_t needle_len, char* str, size_t str_len)
{
	if (needle_len > str_len) {
		return -1;
	}
	uint64_t needle_33 = time33(needle, needle_len);

	for (size_t j = 0; j < str_len; j++)
	{
		if (str_len - j < needle_len) {
			return -1;
		}
		uint64_t str_33 = time33(str + j, needle_len);
		if (str_33 == needle_33) {
			for (size_t tmp = 0; tmp < needle_len; tmp++)
			{
				if (needle[tmp] != str[tmp + j]) {
					goto LOOP;
				}
			}
			return j;
		LOOP:;
		}
	}
	return -1;
}

// 模式字符串中所有的字符组成一个数组, 使用字符的ascii作为index, 字符在字符数组中最后出现的位置作为值
int init_bm_needle_arr(int* needle_arr, size_t len, char* needle, size_t needle_len)
{
	// 初始化不存在的值为-1, 如果不存在就需要多移动一位  x - (-1)
	for (size_t i = 0; i < 256; i++)
	{
		needle_arr[i] = -1;
	}
	// 把模式串的所有字符的最后一次出现的位置保存在数组中, 我们会从后往前定位模式字符串中的字符
	// 出现的越靠后需要向后滑动的位数越少
	for (size_t i = 0; i < needle_len; i++)
	{
		needle_arr[needle[i]] = i;
	}
	return 0;
}

// 定义可能出现的匹配后缀, 使用后缀字符的长度作为Key, 是否在之前出现的index位置作为value, 如果不存在是-1
// 可能匹配后缀的子串, 是否在匹配字符串开头出现
int init_bm_suffix_prefix(int* suffix, int* prefix, char* needle, size_t needle_len)
{
	for (size_t i = 0; i < needle_len; i++)
	{
		suffix[i] = -1;
		prefix[i] = 0;
	}
	for (size_t i = 0; i < needle_len - 1; i++)
	{
		int j = i;
		int k = 0;
		// 通过前缀字符串来查找后缀字符串
		while (j >= 0 && needle[j] == needle[needle_len - k - 1]) {
			++k;
			suffix[k] = j;
			--j;
		}
		if (j == -1) {
			prefix[k] = 1;
		}
	}
	return 0;
}

int bm_move(int* suffix, int* prefix, int bad_char, int needle_len)
{
	int k = needle_len - bad_char - 1;	// j是坏字符的位置, 所以需要再减去1, 那就是好字符串的起始位置
	if (suffix[k] != -1) {		// 如果不等于-1说明, 匹配字符串之前的字符串有完全匹配的子串
		return bad_char - suffix[k] + 1;
	}
	// r 是好后缀的后缀子串
	for (int r = bad_char + 2; r < needle_len; ++r) {
		if (prefix[needle_len - r] == 1) {
			return r;
		}
	}
	return needle_len;
}

int bm(char* needle, size_t needle_len, char* str, size_t str_len)
{
	if (needle_len > str_len) {
		return -1;
	}

	int needle_arr[256];
	init_bm_needle_arr(needle_arr, 256, needle, needle_len);

	// 构建一个模式串的子串数组, key是子串的长度, value是当前子串向前查询最后一个匹配的子串, 如果没有就是-1
	int* suffix = malloc(sizeof(int) * needle_len);
	int* prefix = malloc(sizeof(int) * needle_len);
	if (suffix == NULL || prefix == NULL) {
		free(suffix);
		free(prefix);
		return -1;
	}
	init_bm_suffix_prefix(suffix, prefix, needle, needle_len);

	int i = 0;
	while (i <= str_len - needle_len) {
		int j;
		// 需要找到坏字符串的位置, 如果所有字符串都相同那么就直接匹配到了
		for (j = needle_len - 1; j >= 0; j--) {
			if (str[i + j] != needle[j]) {
				break;
			}
		}
		if (j < 0) {
			return i;
		}
		// 通过坏字符算法所需要移动的位数
		int x = j - needle_arr[str[i + j]];

		int y = 0;
		if (j < needle_len - 1) {		// 说明有好后缀
			y = bm_move(suffix, prefix, j, needle_len);
		}
		// 在模式字符数组中查找坏字符是否存在以及存在的位置
		i = i + (x > y ? x : y);
	}
	return -1;
}


void kmp_next(int* next, char* b, int m)
{
	next[0] = -1;
	// 当前最长前缀的下标位置, -1代表不存在
	int k = -1;
	for (int i = 1; i < m; ++i) {
		// 如果k等于-1 说明就没有次长的前缀
		// k+1就是当前新增的字符, 如果和前一个匹配串的后一个字符相等说明是当前就是最长匹配串
		while (k != -1 && b[k + 1] != b[i])
		{
			k = next[k];
		}
		// 自增匹配到的前缀字符的结尾下标
		if (b[k + 1] == b[i]) {
			++k;
		}
		next[i] = k;
	}
}

int kmp(char* needle, int needle_len, char* str, int str_len)
{
	int* next = malloc(sizeof(int) * needle_len);
	if (next == NULL) {
		return -1;
	}
	kmp_next(next, needle, needle_len);
	int j = 0;
	for (int i = 0; i < str_len; ++i)
	{
		while (j > 0 && str[i] != needle[j]) {
			j = next[j - 1] + 1;
		}
		if (str[i] == needle[j]) {
			++j;
		}
		if (j == needle_len) {
			return i - needle_len + 1;
		}
	}
	return -1;
}

void test_bf(void)
{
	assert(bf("abc", 3, "ab", 2) == -1);
	assert(bf("ga", 2, "abcdegagde", 10) == 5);
	assert(bf("abc", 3, "abcfegshg", 9) == 0);
	assert(bf("kl", 2, "abcdefghijkl", 12) == 10);
}

void test_rk(void)
{
	assert(rk("abc", 3, "ab", 2) == -1);
	assert(rk("ga", 2, "abcdegagde", 10) == 5);
	assert(rk("a", 1, "ab", 2) == 0);
	assert(rk("klbd", 4, "abcdefghijklbdddd", 17) == 10);
}

void test_bm(void)
{
	assert(bm("abc", 3, "ab", 2) == -1);
	assert(bm("ga", 2, "abcdegagde", 10) == 5);
	assert(bm("a", 1, "ab", 2) == 0);
	assert(bm("klbd", 4, "abcdefghijklbdddd", 17) == 10);
	assert(bm("abc", 3, "abcfegshg", 9) == 0);
	assert(bm("klbd", 4, "abcdefghijklbdddd", 17) == 10);
}

void test_kmp(void)
{
	assert(kmp("abc", 3, "ab", 2) == -1);
	assert(kmp("ga", 2, "abcdegagde", 10) == 5);
	assert(kmp("a", 1, "ab", 2) == 0);
	assert(kmp("klbd", 4, "abcdefghijklbdddd", 17) == 10);
}

void test_string_match(void)
{

	// test_bf();
	// test_rk();
	// test_bm();
	test_kmp();
}