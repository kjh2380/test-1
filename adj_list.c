#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct LIST_Graph
{
	int vertex;
	struct LIST_Graph *link;
} LIST_Graph;

typedef struct LIST_GraphType {
	int n;	// ������ ����
	LIST_Graph *adj_list[MAX_VERTICES];
} LIST_GraphType;

typedef struct {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;
//
void error(char *message);
void Q_init(QueueType *q);// �ʱ�ȭ �Լ�
int is_empty(QueueType *q);// ���� ���� ���� �Լ�
int is_full(QueueType *q);// ��ȭ ���� ���� �Լ�
void enqueue(QueueType *q, element item);// ���� �Լ�
element dequeue(QueueType *q); // ���� �Լ�
element peek(QueueType *q); // ���� �Լ�

void LIST_graph_init(LIST_GraphType *g);// �׷��� �ʱ�ȭ 
void LIST_insert_vertex(LIST_GraphType *g, int v);// ���� ���� ����
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void LIST_insert_edge(LIST_GraphType *g, int u, int v);

void dfs_list(LIST_GraphType *g, int v);
void bfs_list(LIST_GraphType *g, int v);
void init_visited();

int visited[MAX_VERTICES];//���� �켱Ž�� �� �迭

int main()
{
	int sel = 0, i = 0;
	int input1, input2;
	LIST_GraphType LIST;
	LIST_graph_init(&LIST);
	init_visited();

	while (1)
	{
		printf("===���� ����Ʈ �׷���===\n");
		printf("1. ���� ����(0~)\n");
		printf("2. ���� ����\n");
		printf("3. ���� �켱 Ž��\n");
		printf("4. �ʺ� �켱 Ž��\n");
		printf("5. �ʱ�ȭ\n");
		printf("0. ����\n\t->");
		scanf("%d", &sel);
		if (!sel)break;
		switch (sel)
		{
		case 1:
		{
			printf("\t���� �Է� :");
			scanf("%d", &input1);
			LIST_insert_vertex(&LIST, input1);
			break; }
		case 2:
		{
			printf("\tstart :");
			scanf("%d", &input1);
			printf("\tend :");
			scanf("%d", &input2);
			LIST_insert_edge(&LIST, input1, input2);
			break; }
		case 3:
		{
			init_visited();
			printf("\t���� �Է� :");
			scanf("%d", &input1);
			printf("\t");
			dfs_list(&LIST, input1);
			printf("\n");
			break; }
		case 4:
		{
			init_visited();
			printf("\t���� �Է� :");
			scanf("%d", &input1);
			printf("\t");
			bfs_list(&LIST, input1);
			printf("\n");
			break; 
		}
		case 5:
		{
			LIST_graph_init(&LIST);
			break;
		}
		default:
		{
			printf("\t�߸� �Է��ϼ̽��ϴ�.\n");
			break; 
		}

		}
	}
	return 0;
}


void LIST_graph_init(LIST_GraphType *g)// �׷��� �ʱ�ȭ 
{
	int v;
	g->n = 0;
	for (v = 0; v<MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
void LIST_insert_vertex(LIST_GraphType *g, int v)// ���� ���� ����
{
	if (((g->n) + 1) > MAX_VERTICES){
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
void LIST_insert_edge(LIST_GraphType *g, int u, int v)
{// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
	// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
	LIST_Graph *node;
	if (u >= g->n || v >= g->n){
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (LIST_Graph *)malloc(sizeof(LIST_Graph));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}
void dfs_list(LIST_GraphType *g, int v)
{  // ���� ����Ʈ�� ǥ���� �׷����� ���� ���� �켱 Ž��
	LIST_Graph *w;
	visited[v] = TRUE;   		// ���� v�� �湮 ǥ�� 
	printf("%d ", v);   		// �湮�� ���� ��� 
	for (w = g->adj_list[v]; w; w = w->link)// ���� ���� Ž�� 
		if (!visited[w->vertex])
			dfs_list(g, w->vertex); //���� w���� DFS ���ν���
}
void bfs_list(LIST_GraphType *g, int v)
{
	LIST_Graph *w;
	QueueType q;
	Q_init(&q);    				// ť �ʱ� ȭ 
	visited[v] = TRUE;      // ���� v �湮 ǥ�� 
	printf("%d ", v);          // �湮�� ���� ��� 
	enqueue(&q, v);			// ���������� ť�� ���� 
	while (!is_empty(&q)){
		v = dequeue(&q);		// ť�� ����� ���� ���� 
		for (w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
			if (!visited[w->vertex]){	// �̹湮 ���� Ž�� 
				visited[w->vertex] = TRUE;   // �湮 ǥ��
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);	//������ ť�� ����
			}
	}
}

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void Q_init(QueueType *q)// �ʱ�ȭ �Լ�
{
	q->front = q->rear = 0;
}
int is_empty(QueueType *q)// ���� ���� ���� �Լ�
{
	return (q->front == q->rear);
}
int is_full(QueueType *q)// ��ȭ ���� ���� �Լ�
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType *q, element item)// ���� �Լ�
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
element dequeue(QueueType *q)// ���� �Լ�
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
element peek(QueueType *q) // ���� �Լ�
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

void init_visited()
{
	int i = 0;
	for (i = 0; i<MAX_VERTICES; i++)
		visited[i] = FALSE;
}