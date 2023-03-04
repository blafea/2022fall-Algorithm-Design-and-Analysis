#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Parent
{
    int idx;
    int weight;
    int cost;
};

struct AdjListNode
{
    int dest;
    int weight;
    int cost;
    struct AdjListNode *next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList *array;
};

struct AdjListNode *newAdjListNode(int dest, int weight, int cost)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->cost = cost;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, int weight, int cost)
{
    struct AdjListNode *newNode = newAdjListNode(dest, weight, cost);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight, cost);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

struct MinHeapNode
{
    int v;
    int key_l;
    int key_c;
};

struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode *newMinHeapNode(int v, int key_l, int key_c)
{
    struct MinHeapNode *minHeapNode = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key_l = key_l;
    minHeapNode->key_c = key_c;
    return minHeapNode;
}

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && (minHeap->array[left]->key_l < minHeap->array[smallest]->key_l || (minHeap->array[left]->key_l == minHeap->array[smallest]->key_l && minHeap->array[left]->key_c < minHeap->array[smallest]->key_c)))
        smallest = left;

    if (right < minHeap->size && (minHeap->array[right]->key_l < minHeap->array[smallest]->key_l || (minHeap->array[right]->key_l == minHeap->array[smallest]->key_l && minHeap->array[right]->key_c < minHeap->array[smallest]->key_c)))
        smallest = right;

    if (smallest != idx)
    {
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode *root = minHeap->array[0];

    struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(struct MinHeap *minHeap, int v, int key_l)
{
    int i = minHeap->pos[v];
    minHeap->array[i]->key_l = key_l;

    while ((i && minHeap->array[i]->key_l < minHeap->array[(i - 1) / 2]->key_l) || (i && minHeap->array[i]->key_l == minHeap->array[(i - 1) / 2]->key_l && minHeap->array[i]->key_c < minHeap->array[(i - 1) / 2]->key_c))
    {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

void find_cost(int dp[], long long int ans_cost[], struct Parent parent[], int now)
{
    if (parent[now].idx == 0)
    {
        dp[now] = parent[now].weight;
        ans_cost[now] = parent[now].cost;
        return;
    }
    else
        find_cost(dp, ans_cost, parent, parent[now].idx);

    if (parent[now].weight == dp[parent[now].idx])
    {
        dp[now] = dp[parent[now].idx];
        ans_cost[now] = ans_cost[parent[now].idx] + parent[now].cost;
    }
    else if (parent[now].weight > dp[parent[now].idx])
    {
        dp[now] = parent[now].weight;
        ans_cost[now] = parent[now].cost;
    }
    else
    {
        dp[now] = dp[parent[now].idx];
        ans_cost[now] = ans_cost[parent[now].idx];
    }
    return;
}

void PrimMST(struct Graph *graph)
{
    int V = graph->V;
    struct Parent *parent = (struct Parent *)malloc(V * sizeof(struct Parent));
    int *key_l = (int *)malloc(V * sizeof(int));
    int *key_c = (int *)malloc(V * sizeof(int));
    int *dp = (int *)malloc(V * sizeof(int));
    long long int *ans_cost = (long long int *)malloc(V * sizeof(long long int));

    struct MinHeap *minHeap = createMinHeap(V);

    for (int v = 1; v < V; ++v)
    {
        parent[v].idx = -1;
        parent[v].cost = 0;
        parent[v].weight = INT_MAX;
        key_l[v] = INT_MAX;
        key_c[v] = 0;
        minHeap->array[v] = newMinHeapNode(v, key_l[v], key_c[v]);
        minHeap->pos[v] = v;
    }

    key_l[0] = 0;
    key_c[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key_l[0], key_c[0]);
    minHeap->pos[0] = 0;

    minHeap->size = V;

    while (!isEmpty(minHeap))
    {
        struct MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        struct AdjListNode *pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;

            if (isInMinHeap(minHeap, v) && (pCrawl->weight < key_l[v]))
            {
                key_l[v] = pCrawl->weight;
                key_c[v] = pCrawl->cost;
                parent[v].idx = u;
                parent[v].cost = pCrawl->cost;
                parent[v].weight = pCrawl->weight;
                decreaseKey(minHeap, v, key_l[v]);
            }
            else if (isInMinHeap(minHeap, v) && pCrawl->weight == key_l[v] && pCrawl->cost < key_c[v])
            {
                key_c[v] = pCrawl->cost;
                parent[v].idx = u;
                parent[v].cost = pCrawl->cost;
                parent[v].weight = pCrawl->weight;
                decreaseKey(minHeap, v, key_l[v]);
            }

            pCrawl = pCrawl->next;
        }
    }
    long long int ans = 0;
    for (int i = 1; i < V; i++)
    {
        if (dp[i] == 0)
            find_cost(dp, ans_cost, parent, i);
        ans += ans_cost[i];
    }
    printf("%lld", ans);
}

int main()
{
    int n, m, u, v, l, c;
    scanf("%d %d", &n, &m);
    struct Graph *graph = createGraph(n);

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d %d", &u, &v, &l, &c);
        addEdge(graph, u, v, l, c);
    }

    PrimMST(graph);

    return 0;
}
