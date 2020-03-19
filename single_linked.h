typedef struct _single_linked_list single_linked_list;
typedef struct _single_linked_list_node single_linked_list_node;

//typedef int (*linked_list_add)(linked_list* l, int v);
//typedef int (*linked_list_delete)(linked_list* l, int v);
//typedef void (*linked_list_each)(linked_list* l, void(*fn)(linked_list_node* node));
single_linked_list* init_single_linked_list();

struct _single_linked_list_node
{
	int value;	// 如果想实现能存储多类型的值 是不是要使用 void* 或者 struct 包装呢
	single_linked_list_node* next;
};

struct _single_linked_list
{
	single_linked_list_node* head;
	single_linked_list_node* latest;
	int count;

	int (*add)(single_linked_list* l, int v);
	int (*delete)(single_linked_list* l, int v);
	void (*each)(single_linked_list* l, void(*fn)(single_linked_list_node* node));
	void (*free)(single_linked_list** l);
};

