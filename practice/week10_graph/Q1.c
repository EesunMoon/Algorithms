#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Graph {
	struct Vertex *vertex;
	struct Edge *edge;
}Graph;

typedef struct Node {
	int edge_index;
	struct Node *next;
}Node;

typedef struct Vertex {
	int id;
	struct Node *list;
}Vertex;

typedef struct Edge {
	int from, to;
	int weight;
}Edge;

Node *create_node(int id)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->edge_index = id;
	new_node->next = NULL;

	return new_node;
}

void init_vertex(Vertex *vertex, int id)
{
	vertex->list = create_node(-1);
	vertex->id = id;
}

void init_edge(Edge *edge, int n)
{
	int i, j, index = 0;
	for (i = 0; i<n; i++)
	{
		for (j = i; j<n; j++)
		{
			edge[index].from = i + 1;
			edge[index].to = j + 1;
			edge[index].weight = 0;
			index++;
		}
	}
}
void add_edge(Edge *edge, int index, int weight)
{
	edge[index].weight = weight;
}

void add_node(Vertex *vertex1, Vertex *vertex2, int edge_index)
{
	Node *new_node = create_node(edge_index);
	Node *tmp;

	tmp = vertex1->list;
	if (tmp == NULL) vertex1->list = new_node;
	else
	{
		while (tmp->next != NULL)
		{
			if (tmp->next != NULL && tmp->next->edge_index > edge_index) break;
			tmp = tmp->next;
		}
		new_node->next = tmp->next;
		tmp->next = new_node;
	}

	if (vertex1 == vertex2) return;

	new_node = create_node(edge_index);
	tmp = vertex2->list;
	if (tmp == NULL) vertex2->list = new_node;
	else
	{
		while (tmp->next != NULL)
		{
			if (tmp->next != NULL && tmp->next->edge_index > edge_index) break;
			tmp = tmp->next;
		}
		new_node->next = tmp->next;
		tmp->next = new_node;
	}
}

void search_vertex(Graph *graph, int vertex_index)
{
	Node *node = graph->vertex[vertex_index].list;
	Edge tmp;

	if (vertex_index < 0 || vertex_index > 5)
	{
		printf("-1\n");
		return;
	}
	while (node != NULL)
	{
		if (node->edge_index == -1)
		{
			node = node->next;
			continue;
		}
		tmp = graph->edge[node->edge_index];

		if (tmp.weight != 0)
		{
			if (tmp.from == vertex_index + 1) printf(" %d %d", tmp.to, tmp.weight);
			else printf(" %d %d", tmp.from, tmp.weight);
		}

		node = node->next;
	}
	printf("\n");
}
void modify_edge(Graph *graph, int vertex1_index, int vertex2_index, int weight)
{
	int i, tmp;
	if ((vertex1_index < 0 || vertex1_index > 5) || (vertex2_index < 0 || vertex2_index > 5))
	{
		printf("-1\n");
		return;
	}

	if (vertex1_index > vertex2_index)
	{
		tmp = vertex1_index;
		vertex1_index = vertex2_index;
		vertex2_index = tmp;
	}

	for (i = 0; i<21; i++)
	{
		if (graph->edge[i].from == vertex1_index + 1 && graph->edge[i].to == vertex2_index + 1)
		{
			if (graph->edge[i].weight == 0)
			{
				graph->edge[i].weight = weight;
				add_node(&(graph->vertex[vertex1_index]), &(graph->vertex[vertex2_index]), i);
			}
			else graph->edge[i].weight = weight;
			break;
		}
	}
}

int main()
{
	Graph *graph;
	int i, vertex_num, vertex1, vertex2, weight;
	char func;

	graph = (Graph *)malloc(sizeof(Graph));
	graph->vertex = (Vertex *)malloc(sizeof(Vertex) * 6);
	graph->edge = (Edge *)malloc(sizeof(Edge) * 21);

	for (i = 0; i<6; i++) init_vertex(&(graph->vertex[i]), i + 1);
	init_edge(graph->edge, 6);

	add_edge(graph->edge, 1, 1);
	add_edge(graph->edge, 2, 1);
	add_edge(graph->edge, 3, 1);
	add_edge(graph->edge, 5, 2);
	add_edge(graph->edge, 7, 1);
	add_edge(graph->edge, 13, 4);
	add_edge(graph->edge, 18, 4);
	add_edge(graph->edge, 19, 3);

	add_node(&(graph->vertex[1]), &(graph->vertex[2]), 7);
	add_node(&(graph->vertex[0]), &(graph->vertex[1]), 1);
	add_node(&(graph->vertex[0]), &(graph->vertex[2]), 2);
	add_node(&(graph->vertex[0]), &(graph->vertex[3]), 3);
	add_node(&(graph->vertex[0]), &(graph->vertex[5]), 5);
	add_node(&(graph->vertex[2]), &(graph->vertex[4]), 13);
	add_node(&(graph->vertex[4]), &(graph->vertex[4]), 18);
	add_node(&(graph->vertex[4]), &(graph->vertex[5]), 19);

	while (1)
	{
		scanf("%c", &func);

		if (func == 'a')
		{
			scanf("%d", &vertex_num);
			getchar();
			search_vertex(graph, vertex_num - 1);
		}
		else if (func == 'm')
		{
			scanf("%d %d %d", &vertex1, &vertex2, &weight);
			getchar();
			modify_edge(graph, vertex1 - 1, vertex2 - 1, weight);
		}
		else if (func == 'q')
		{
			break;
		}
		else break;
	}
	return 0;
}
