#include <stdio.h>
#include "linked_list.h"

typedef linked_list_node graph_linked_node;
typedef linked_list graph_linked;
typedef struct _graph graph;

struct _graph_linked_node
{
	int value;
	graph_linked_node* next;
};

struct _graph_linked
{
	int num;
	graph_linked_node* head;
};

struct _graph
{
	size_t num;	// 顶点的个数
	graph_linked** adj;
};

int graph_add(graph* g, unsigned int s, unsigned int t)
{
	if (s >= g->num || t >= g->num)
	{
		return 0;
	}
	g->adj[s]->add(g->adj, t);
	g->adj[t]->add(g->adj, s);
}

graph* init_graph(size_t num)
{
	graph* g = malloc(sizeof(graph));
	if (!g)
	{
		return NULL;
	}
	graph_linked** adj = calloc(sizeof(graph_linked*), num);
	if (!adj)
	{
		free(g);
		return NULL;
	}
	g->adj = adj;
	g->num = num;
	return g;
}

void test_graph(void)
{

}
