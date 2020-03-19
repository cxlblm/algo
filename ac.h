#pragma once
#ifndef AC_H
#define AC_H

typedef struct _ac_trie_node ac_trie_node;
typedef struct _ac_trie ac_trie;

struct _ac_trie_node
{
	char c;
	ac_trie_node* children[26];		// 只有因为字母的情况
	int length;		// 当is_end_char的时候记录, 记录模式串的长度
	ac_trie_node* fail;	// 失败指针
	unsigned char is_end_char;
};

struct _ac_trie
{
	ac_trie_node* root;
};
#endif // AC_H

