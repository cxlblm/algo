#include <stdio.h>

extern void testSingleLinked(void);
extern void test_linked_stack(void);
extern void test_array_stack(void);

int main(void)
{
	// testSingleLinked();
	// testStack();
	test_linked_stack();
	test_array_stack();
	// testSort();
	return 0;
}