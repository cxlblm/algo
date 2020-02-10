#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _binary_tree_node binary_tree_node;

struct _binary_tree_node
{
	int data;
	binary_tree_node* left;
	binary_tree_node* right;

	/*
	int(*find)(binary_tree_node* tree, int value);
	int(*delete)(binary_tree_node* tree, int value);
	int(*insert)(binary_tree_node* tree, int value);
	*/
};

binary_tree_node* binary_tree_node_find(binary_tree_node* tree, int value)
{
	if (!tree)
	{
		return NULL;
	}
	while (tree)
	{
		if (tree->data == value)
		{
			return tree;
		}
		else if (tree->data > value)
		{
			tree = tree->left;
		}
		else
		{
			tree = tree->right;
		}
	}
	return NULL;
}

binary_tree_node* init_binary_tree_node(int value)
{
	binary_tree_node* node = malloc(sizeof(binary_tree_node));
	if (!node) {
		return NULL;
	}
	memset(node, 0, sizeof(binary_tree_node));
	node->data = value;
	return node;
}

// 需要在函数内部修改tree的值, 所以就需要二级指针
int binary_tree_node_insert(binary_tree_node** tree_pp, int value)
{
	if (!tree_pp)
	{
		return 0;
	}
	binary_tree_node* node = init_binary_tree_node(value);
	if (!node) {
		return 0;
	}
	if (!*tree_pp) {
		*tree_pp = node;
		return 1;
	}
	binary_tree_node* tree = *tree_pp;
	if (!tree)
	{
		return 0;
	}
	while (tree)
	{
		if (tree->data > value) {
			if (tree->left == NULL) {
				tree->left = node;
				return 1;
			}
			tree = tree->left;
		} else {
			if (tree->right == NULL) {
				tree->right = node;
				return 1;
			}
			tree = tree->right;
		}
	}
	return 0;
}


int binary_tree_node_delete(binary_tree_node** tree_pp, int value)
{
	if (!tree_pp || !*tree_pp)
	{
		return 0;
	}

	binary_tree_node* tree = *tree_pp;
	binary_tree_node* parent = NULL;
	while (tree && tree->data != value)
	{
		parent = tree;
		tree = tree->data > value ? tree->left : tree->right;
	}

	if (!tree)
	{
		return 0;
	}
	if (tree->left != NULL && tree->right != NULL)
	{
		binary_tree_node* right_tree_node = tree->right; // 右树中的最小的节点
		binary_tree_node* right_tree_node_parent = tree;	// 右树最小节点的父节点
		while (right_tree_node->left)
		{
			right_tree_node_parent = right_tree_node;
			right_tree_node = right_tree_node->left;
		}
		tree->data = right_tree_node->data;
		tree = right_tree_node;		// 需要本回收的内存
		parent = right_tree_node_parent;
	}

	// 如果删除的节点是叶子节点或者只有一个子节点
	binary_tree_node* child = tree->left;
	if (tree->right != NULL) {
		child = tree->right;
	}
	if (parent == NULL)	// 如果父节点为空, 说明要删除的是根节点
	{
		*tree_pp = NULL;
	}
	else if (parent->left == tree)
	{
		parent->left = child;
	}
	else
	{
		parent->right = child;
	}
	free(tree);
	return 1;
}

void pre_order(binary_tree_node* root)
{
	if (!root)
	{
		return;
	}
	printf("node: %d\n", root->data);
	pre_order(root->left);
	pre_order(root->right);
}

void in_order(binary_tree_node* root)
{
	if (!root)
	{
		return;
	}
	in_order(root->left);
	printf("node: %d\n", root->data);
	in_order(root->right);
}


void post_order(binary_tree_node* root)
{
	if (!root)
	{
		return;
	}
	// printf("node: %p, left: %p, right: %p\n", root, root->left, root->right);
	post_order(root->left);
	post_order(root->right);
	printf("node value: %d\n", root->data);
}

void test_binary_tree_insert(void)
{
	binary_tree_node* root = NULL;
	binary_tree_node_insert(&root, 30);
	binary_tree_node_insert(&root, 20);
	binary_tree_node_insert(&root, 20);
	binary_tree_node_insert(&root, 40);
	binary_tree_node_insert(&root, 10);
	pre_order(root);

	binary_tree_node* node;
	node = binary_tree_node_find(root, 10);
	assert(node != NULL);
	assert(node->data == 10);
	
	node = binary_tree_node_find(root, 30);
	assert(node != NULL);
	assert(node->data == 30);
}

void test_binary_tree_delete(void)
{
	binary_tree_node* root = NULL;
	binary_tree_node_insert(&root, 30);
	binary_tree_node_insert(&root, 20);
	binary_tree_node_insert(&root, 40);
	binary_tree_node_insert(&root, 45);
	binary_tree_node_insert(&root, 10);
	binary_tree_node_insert(&root, 15);

	int r;
	binary_tree_node* node;
	r = binary_tree_node_delete(&root, 20);
	assert(r == 1);
	node = binary_tree_node_find(root, 20);
	assert(node == NULL);
	node = binary_tree_node_find(root, 10);
	assert(node != NULL);
	assert(node->data == 10);

	node = binary_tree_node_find(root, 15);
	assert(node != NULL);
	assert(node->data == 15);


	node = binary_tree_node_find(root, 40);
	assert(node != NULL);
	assert(node->data == 40);

	r = binary_tree_node_delete(&root, 10);
	assert(r == 1);
	node = binary_tree_node_find(root, 10);
	assert(node == NULL);

	binary_tree_node_insert(&root, 10);

	r = binary_tree_node_delete(&root, 40);
	assert(r == 1);
	node = binary_tree_node_find(root, 40);
	assert(node == NULL);


	node = binary_tree_node_find(root, 30);
	assert(node != NULL);
	assert(node->data == 30);
}

void test_binary_tree(void)
{
	test_binary_tree_insert();
	// test_binary_tree_delete();
}

