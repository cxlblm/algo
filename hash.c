#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint64_t time33(char* str, size_t len)
{
	uint64_t hash = 5381;

	for (; len >= 8; len -= 8)
	{
		hash = ((hash << 5) + hash) + *str++;
		hash = ((hash << 5) + hash) + *str++;
		hash = ((hash << 5) + hash) + *str++;
		hash = ((hash << 5) + hash) + *str++;
		hash = ((hash << 5) + hash) + *str++;
		hash = ((hash << 5) + hash) + *str++;
		hash = ((hash << 5) + hash) + *str++;
		hash = ((hash << 5) + hash) + *str++;
	}
	switch (len)
	{
	case 7: hash = ((hash << 5) + hash) + *str++;
	case 6: hash = ((hash << 5) + hash) + *str++;
	case 5: hash = ((hash << 5) + hash) + *str++;
	case 4: hash = ((hash << 5) + hash) + *str++;
	case 3: hash = ((hash << 5) + hash) + *str++;
	case 2: hash = ((hash << 5) + hash) + *str++;
	case 1: hash = ((hash << 5) + hash) + *str++;
	}
	return hash;
}

void test_time33(void)
{
	char* str;
	str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcdefg";
	printf("%llu, size: %u\n", time33(str, strlen(str)), strlen(str));

	str = "aaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaabcdefg";
	printf("%llu, size: %ld\n", time33(str, strlen(str)), strlen(str));
}

void test_hash(void)
{
	test_time33();
}