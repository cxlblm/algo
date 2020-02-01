#include <stdio.h>

extern void testSingleLinked(void);
extern void test_linked_stack(void);
extern void test_array_stack(void);
extern void test_binary_search(void);

int main(void)
{
	// testSingleLinked();
	// testStack();
	// test_linked_stack();
	// test_array_stack();
	// test_sort();
	// test_binary_search();
	test_skip_list();
	return 0;
}