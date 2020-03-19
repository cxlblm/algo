#include <stdio.h>

extern void testSingleLinked(void);
extern void test_linked_stack(void);
extern void test_array_stack(void);
extern void test_binary_search(void);
extern void test_hash(void);
extern void test_hash_map(void);
extern void test_binary_tree(void);
extern void test_heap(void);
extern void test_linked_list(void);
extern void test_single_linked2(void);
extern void test_string_match(void);
extern void test_trie(void);
extern void test_ac_trie(void);
extern void test_queue(void);

int main(void)
{
	// testSingleLinked();
	// testStack();
	// test_linked_stack();
	// test_array_stack();
	// test_sort();
	// test_binary_search();
	// test_skip_list();
	// test_hash();
	// test_binary_tree();
	// test_heap();
	// test_linked_list();
	// test_single_linked2();
	// test_string_match();
	// test_trie();
	test_ac_trie();
	// test_queue();
	return 0;
}