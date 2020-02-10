typedef struct _linked_list linked_list;
typedef struct _linked_list_node linked_list_node;

//typedef int (*linked_list_add)(linked_list* l, int v);
//typedef int (*linked_list_delete)(linked_list* l, int v);
//typedef void (*linked_list_each)(linked_list* l, void(*fn)(linked_list_node* node));
linked_list* init_linked_list();

struct _linked_list_node
{
	int value;	// 如果想实现能存储多类型的值 是不是要使用 void* 或者 struct 包装呢
	linked_list_node* next;
	linked_list_node* pre;
};

struct _linked_list
{
	linked_list_node* head;
	linked_list_node* latest;
	int count;

	int (*add)(linked_list* l, int v);
	int (*delete)(linked_list* l, int v);
	void (*each)(linked_list* l, void(*fn)(linked_list_node* node));
};

