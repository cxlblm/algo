typedef struct _array_stack array_stack;
typedef struct _array_stack_node linked_stack_node;

struct _array_stack {
	linked_stack_node** n;
	size_t len;
	size_t total;
	linked_stack_node* (*pop)(array_stack*);
	int (*push)(array_stack*, linked_stack_node*);
	int (*count)(array_stack*);
};

struct _array_stack_node {
	char* data;
};
