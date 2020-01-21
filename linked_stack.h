typedef struct _linked_stack linked_stack;
typedef struct _linked_stack_node linked_stack_node;

struct _linked_stack_node
{
	linked_stack_node* next;
	void* data;
};

struct _linked_stack
{
	linked_stack_node* head;
	int len;

	linked_stack_node* (*pop)(linked_stack*);
	int (*push)(linked_stack*, linked_stack_node*);
	int (*count)(linked_stack*);
};