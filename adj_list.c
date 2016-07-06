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
	int n;	// 정점의 개수
	LIST_Graph *adj_list[MAX_VERTICES];
} LIST_GraphType;

typedef struct {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;
//
void error(char *message);
void Q_init(QueueType *q);// 초기화 함수
int is_empty(QueueType *q);// 공백 상태 검출 함수
int is_full(QueueType *q);// 포화 상태 검출 함수
void enqueue(QueueType *q, element item);// 삽입 함수
element dequeue(QueueType *q); // 삭제 함수
element peek(QueueType *q); // 삭제 함수

void LIST_graph_init(LIST_GraphType *g);// 그래프 초기화 
void LIST_insert_vertex(LIST_GraphType *g, int v);// 정점 삽입 연산
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void LIST_insert_edge(LIST_GraphType *g, int u, int v);

void dfs_list(LIST_GraphType *g, int v);
void bfs_list(LIST_GraphType *g, int v);
void init_visited();

int visited[MAX_VERTICES];//깊이 우선탐색 할 배열

int main()
{
	int sel = 0, i = 0;
	int input1, input2;
	LIST_GraphType LIST;
	LIST_graph_init(&LIST);
	init_visited();

	while (1)
	{
		printf("===인접 리스트 그래프===\n");
		printf("1. 정점 삽입(0~)\n");
		printf("2. 간선 삽입\n");
		printf("3. 깊이 우선 탐색\n");
		printf("4. 너비 우선 탐색\n");
		printf("5. 초기화\n");
		printf("0. 종료\n\t->");
		scanf("%d", &sel);
		if (!sel)break;
		switch (sel)
		{
		case 1:
		{
			printf("\t정점 입력 :");
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
			printf("\t정점 입력 :");
			scanf("%d", &input1);
			printf("\t");
			dfs_list(&LIST, input1);
			printf("\n");
			break; }
		case 4:
		{
			init_visited();
			printf("\t정점 입력 :");
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
			printf("\t잘못 입력하셨습니다.\n");
			break; 
		}

		}
	}
	return 0;
}


void LIST_graph_init(LIST_GraphType *g)// 그래프 초기화 
{
	int v;
	g->n = 0;
	for (v = 0; v<MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
void LIST_insert_vertex(LIST_GraphType *g, int v)// 정점 삽입 연산
{
	if (((g->n) + 1) > MAX_VERTICES){
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
void LIST_insert_edge(LIST_GraphType *g, int u, int v)
{// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
	// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
	LIST_Graph *node;
	if (u >= g->n || v >= g->n){
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (LIST_Graph *)malloc(sizeof(LIST_Graph));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}
void dfs_list(LIST_GraphType *g, int v)
{  // 인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
	LIST_Graph *w;
	visited[v] = TRUE;   		// 정점 v의 방문 표시 
	printf("%d ", v);   		// 방문한 정점 출력 
	for (w = g->adj_list[v]; w; w = w->link)// 인접 정점 탐색 
		if (!visited[w->vertex])
			dfs_list(g, w->vertex); //정점 w에서 DFS 새로시작
}
void bfs_list(LIST_GraphType *g, int v)
{
	LIST_Graph *w;
	QueueType q;
	Q_init(&q);    				// 큐 초기 화 
	visited[v] = TRUE;      // 정점 v 방문 표시 
	printf("%d ", v);          // 방문한 정점 출력 
	enqueue(&q, v);			// 시작정점을 큐에 저장 
	while (!is_empty(&q)){
		v = dequeue(&q);		// 큐에 저장된 정점 선택 
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]){	// 미방문 정점 탐색 
				visited[w->vertex] = TRUE;   // 방문 표시
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);	//정점을 큐에 삽입
			}
	}
}

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void Q_init(QueueType *q)// 초기화 함수
{
	q->front = q->rear = 0;
}
int is_empty(QueueType *q)// 공백 상태 검출 함수
{
	return (q->front == q->rear);
}
int is_full(QueueType *q)// 포화 상태 검출 함수
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType *q, element item)// 삽입 함수
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
element dequeue(QueueType *q)// 삭제 함수
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
element peek(QueueType *q) // 삭제 함수
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

void init_visited()
{
	int i = 0;
	for (i = 0; i<MAX_VERTICES; i++)
		visited[i] = FALSE;
}