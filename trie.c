#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _trie_node trie_node;
typedef struct _trie trie;

struct _trie_node {
	char c;
	trie_node* children[26];		// 只有因为字母的情况
	unsigned char is_end_char;
};

struct _trie
{
	trie_node* root;
};

trie_node* init_trie_node(char c)
{
	trie_node *n = malloc(sizeof(trie_node));
	if (n == NULL) {
		return NULL;
	}
	memset(n, 0, sizeof(trie_node));
	n->c = c;
	return n;
}

trie* init_trie()
{
	trie *t = malloc(sizeof(trie));
	if (t == NULL) {
		return NULL;
	}
	trie_node* node = init_trie_node('/');
	if (node == NULL) {
		free(t);
		return NULL;
	}
	t->root = node;
	return t;
}

int trie_insert(trie* trie, char *str, size_t len)
{
	trie_node *p= trie->root;
	int r = 0;
	for (size_t i = 0; i < len; i++)
	{
		char index = str[i] - 'a';
		if ((p->children)[index] == NULL) {
			trie_node* node = init_trie_node(str[i]);
			if (node == NULL) {
				return -1;
			}
			(p->children)[index] = node;
		}
		p = (p->children)[index];
		++r;
	}
	p->is_end_char = 1;
	return r;
}

int trie_find(trie* t,  char* pattern, size_t len)
{
	trie_node* p = t->root;
	for (size_t i = 0; i < len; i++)
	{
		char index = pattern[i] - 'a';
		if ((p->children)[index] == NULL) {
			return 0;
		}
		p = (p->children)[index];
	}
	return p->is_end_char;	// 如果模式匹配结束, is_end_char是结束字符, 说明是完全匹配, 否则就只是前缀匹配到了
}

void test_trie_insert(void)
{
	trie *t = init_trie();
	if (t == NULL) {
		return;
	}
	assert(3 == trie_insert(t, "abc", 3));
}

void test_find(void)
{
	trie *t = init_trie();
	if (t == NULL) {
		return;
	}
	trie_insert(t, "abc", 3);
	trie_insert(t, "bcd", 3);
	assert(0 == trie_find(t, "bc", 2));
	assert(1 == trie_find(t, "abc", 2));
}

void test_trie(void)
{
	test_trie_insert();
}