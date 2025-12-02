#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node {
    int data;
    int status;
    struct node *next, *point;
} node;

typedef struct topsort {
    int n;
    struct topsort *next;
} topsort;

node *g = NULL;
topsort *tsort = NULL;
int time = 0;

void addvertex(int n) {
    node *t = (node*)malloc(sizeof(node));
    t->data = n;
    t->status = 0;
    t->point = NULL;
    t->next = g;
    g = t;
}

node* find(int n) {
    node *t = g;
    while (t && t->data != n)
        t = t->next;
    return t;
}

void addedge(int u, int v) {
    node *v1 = find(u);
    node *v2 = find(v);

    node *t = (node*)malloc(sizeof(node));
    t->next = v1->point;
    t->point = v2;
    v1->point = t;
}

void topsortpush(int n) {
    topsort *z = (topsort*)malloc(sizeof(topsort));
    z->n = n;
    z->next = tsort;
    tsort = z;
}

void topsortout() {
    while (tsort) {
        printf("%d ", tsort->n);
        tsort = tsort->next;
    }
}

void dfs_visit(node *u) {
    u->status = 1;
    printf("%d ", u->data);

    node *t = u->point;
    while (t) {
        node *v = t->point;
        if (v->status == 0)
            dfs_visit(v);
        t = t->next;
    }

    topsortpush(u->data);
}

void dfs(node *start) {
    node *t = g;
    while (t) {
        t->status = 0;
        t = t->next;
    }
    dfs_visit(start);
}

node *q[SIZE];
int front = 0, rear = 0;

int empty() { return front == rear; }

void enque(node *s) {
    int nr = (rear + 1) % SIZE;
    if (nr == front) {
        printf("Queue full\n");
        exit(1);
    }
    rear = nr;
    q[rear] = s;
}

node* deque() {
    if (empty()) {
        printf("Queue empty\n");
        exit(1);
    }
    front = (front + 1) % SIZE;
    return q[front];
}

void bfs(node *s) {
    node *t = g;
    while (t) {
        t->status = 0;
        t = t->next;
    }

    s->status = 1;
    printf("%d ", s->data);
    enque(s);

    while (!empty()) {
        node *u = deque();
        node *adj = u->point;
        while (adj) {
            node *v = adj->point;
            if (v->status == 0) {
                printf("%d ", v->data);
                v->status = 1;
                enque(v);
            }
            adj = adj->next;
        }
    }
}

int main() {
    addvertex(1);
    addvertex(2);
    addvertex(3);
    addvertex(4);
    addvertex(5);

    addedge(1,2);
    addedge(1,4);
    addedge(2,3);
    addedge(2,4);
    addedge(4,3);
    addedge(4,5);

    printf("\nBFS Traversal: ");
    bfs(find(1));

    printf("\nDFS Traversal + Topological Sort: ");
    dfs(find(1));

    printf("\nTopological Sort Order: ");
    topsortout();
}

