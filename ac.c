#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ac.h"
#include "queue.h"

ac_trie_node* init_ac_trie_node(char c)
{
	ac_trie_node* n = malloc(sizeof(ac_trie_node));
	if (!n) {
		return NULL;
	}
	memset(n->children, 0, sizeof(ac_trie_node*) * 26);
	n->c = c;
	n->fail = NULL;
	n->is_end_char = 0;
	n->length = -1;
	return n;
}

ac_trie* init_ac_trie()
{
	ac_trie* trie = malloc(sizeof(ac_trie));
	if (!trie) {
		return NULL;
	}
	ac_trie_node* node = init_ac_trie_node('/');
	if (!node) {
		free(trie);
		return NULL;
	}
	trie->root = node;
	return trie;
}

void ac_trie_insert(ac_trie* trie, char* str)
{
	ac_trie_node* root = trie->root;
	size_t len = strlen(str);
	for (size_t i = 0; i < len; ++i)
	{
		int index = str[i] - 'a';
		ac_trie_node *node = (root->children)[index];
		if (!node) {
			ac_trie_node* new_node = init_ac_trie_node(str[i]);
			(root->children)[index] = new_node;
		}
		root = (root->children)[index];
	}
	root->is_end_char = 1;
	root->length = len;
}

void ac_trie_build_fail_pointer(ac_trie* trie)
{
	queue *q = init_queue();
	trie->root->fail = NULL;
	q->push(q, trie->root);
	while (q->get_len(q) > 0) {
		ac_trie_node* node = (ac_trie_node*)q->pop(q);
		for (size_t i = 0; i < 26; i++)
		{
			ac_trie_node* node_children = (node->children)[i];
			if (!node_children) {
				continue;
			}
			if (node == trie->root) {
				node_children->fail = trie->root;
			} else {
				ac_trie_node* fail = node->fail;
				while (fail) {
					ac_trie_node* fail_children = (fail->children)[node_children->c - 'a'];
					if (fail_children) {
						node_children->fail = fail_children;
						break;
					}
					fail = fail->fail;
				}
				if (!fail) {
					node_children->fail = trie->root;
				}
			}
			q->push(q, node_children);
		}
	}
}

void ac_trie_match(ac_trie* trie, char* str)
{
	ac_trie_node* p = trie->root;

	size_t len = strlen(str);
	for (size_t i = 0; i < len; ++i)
	{
		char index = str[i] - 'a';
		while (!p->children[index] && p != trie->root)
		{
			p = p->fail;
		}
		p = p->children[index];
		if (!p) {
			p = trie->root;
		}
		ac_trie_node* tmp = p;
		while (tmp != trie->root)
		{
			if (tmp->is_end_char) {
				int pos = i - tmp->length + 1;
				printf("起始位置: %d, 字符长度: %d", pos, tmp->length);
			}
			tmp = tmp->fail;
		}
	}
}

void test_ac_trie(void)
{
	ac_trie* trie = init_ac_trie();
	ac_trie_insert(trie, "abcd");
	ac_trie_insert(trie, "bcd");
	ac_trie_insert(trie, "c");
	ac_trie_insert(trie, "bc");
	ac_trie_build_fail_pointer(trie);
	ac_trie_match(trie, "bc");
}


