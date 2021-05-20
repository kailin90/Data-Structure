//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa2
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
    List *neighbor;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
}GraphObj;
typedef GraphObj *Graph;

// returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n){
    Graph graph = malloc(sizeof(GraphObj));
    graph->neighbor = malloc((n+1)*sizeof(List));
    graph->color = malloc((n+1)*sizeof(int));
    graph->parent = malloc((n+1)*sizeof(int));
    graph->distance = malloc((n+1)*sizeof(int));

    for (int i=1;i<n+1;i++){
        graph->neighbor[i]=newList();
        graph->color[i]=WHITE;
        graph->parent[i]=NIL;
        graph->distance[i]=INF;
    }

    graph->order=n;
    graph->size=0;
    graph->source=NIL;
    return graph;
}

// frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    if (pG!=NULL && *pG!=NULL){
        Graph graph=*pG;
        for (int i=1; i< graph->order+1; i++){
            freeList(&(graph->neighbor[i]));
        }
        free(graph->neighbor);
        free(graph->color);
        free(graph->parent);
        free(graph->distance);
        free(*pG);
        *pG=NULL;
    }else{
        printf("Error: cannot call freeGraph() on null graph");
        exit(EXIT_FAILURE);
    }
}

/*** Access functions ***/

// return order
int getOrder(Graph G){
    if (G==NULL){
        printf("Error: cannot call getOrder() on null graph");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// return size
int getSize(Graph G){
    if (G==NULL){
        printf("Error: cannot call getSize() on null graph");
        exit(EXIT_FAILURE);
    }
    return G->size;    
}

// returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G){
    if (G==NULL){
        printf("Error: cannot call getSource() on null graph");
        exit(EXIT_FAILURE);
    }
    return G->source;       
}

// will return the parent of vertex u in the Breadth-First tree created by BFS(), or NIL if BFS() has not yet been called.
// precondition 1 <= U <= getOrder(G)
int getParent(Graph G, int u){
    if (G==NULL){
        printf("Error: cannot call getParent() on null graph");
        exit(EXIT_FAILURE);
    }

    if (getOrder(G)>=u && u>=1){
        return G->parent[u];
    }else{
        return NIL;
    }
}

// returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
// precondition 1 <= U <= getOrder(G)
int getDist(Graph G, int u){
    if (G==NULL){
        printf("Error: cannot call getDist() on null graph");
        exit(EXIT_FAILURE);
    }

    if (getOrder(G)>=u && u>=1){
        return G->distance[u];
    }else{
        return INF;
    }
}

// appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
// getPath() has the precondition getSource(G)!=NIL, so BFS() must be called before getPath().
// precondition 1 <= U <= getOrder(G)
void getPath(List L, Graph G, int u){
    if (G==NULL){
        printf("Error: cannot call getPath() on null graph");
        exit(EXIT_FAILURE);
    }

    if (getOrder(G)<u || u<1){
        printf("Error: getPath() out of range");
        exit(EXIT_FAILURE);
    }
    
    if (u==getSource(G)){
        append(L,getSource(G));
    }else if(G->parent[u]!=NIL) {
	    getPath(L, G, G->parent[u]);
        append(L, u);
    }else{
        append(L,NIL);
    }
}

/*** Manipulation procedures ***/
// deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
    if (G==NULL){
        printf("Error: cannot call makeNull() on null graph");
        exit(EXIT_FAILURE);
    }

	for(int i = 1; i <= getOrder(G); i++){
		clear(G->neighbor[i]);
		G->distance[i] = INF;
		G->parent[i] = NIL;
		G->color[i] = WHITE;
	}
	G->source = NIL;
}


// inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u. 
// Your program is required to maintain these lists in sorted order by increasing labels.
// precondition that two int arguments must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v){
	if (G == NULL) {
		printf("Error: cannot call addEgde() on null graph object");
		exit(EXIT_FAILURE);
	}

	if (u < 1 || u > getOrder(G)) {
		printf("Error: 2nd argument is out of range");
        exit(EXIT_FAILURE);
	}

    if (v < 1 || v > getOrder(G)) {
		printf("Error: 3rd argument is out of range");
        exit(EXIT_FAILURE);
	}

	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
// precondition that two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v){
	if (G == NULL) {
		printf("Error: cannot call addArc() on null graph object");
		exit(EXIT_FAILURE);
	}

	if (u < 1 || u > getOrder(G)) {
		printf("Error: 2nd argument is out of range");
        exit(EXIT_FAILURE);
	}

    if (v < 1 || v > getOrder(G)) {
		printf("Error: 3rd argument is out of range");
        exit(EXIT_FAILURE);
	}

    if (length(G->neighbor[u]) == 0) {
        append(G->neighbor[u], v);
    }else{
        moveFront(G->neighbor[u]);
        while(index(G->neighbor[u]) >-1 && v>get(G->neighbor[u])) {
            moveNext(G->neighbor[u]);
        }
        if(index(G->neighbor[u]) == -1){
            append(G->neighbor[u], v);
        }else{
            insertBefore(G->neighbor[u], v);
        }
    }
    G->size++;
}

// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
/*
    BFS(G,s)
    for x in V(G)-{s}
            color[x] = white   
            d[x] = inf
            p[x] = nil 
    color[s] = gray       // discover the source s
    d[s] = 0
    p[s] = nil 
    Q = { }              // construct a new empty queue
    Enqueue(Q,s)
    while Q !=  { }
            x = Dequeue(Q) 
            for y in adj[x]
                if color[y] == white         // y is undiscovered
                    color[y] = gray         // discover y
                    d[y] = d[x]+1
                    p[y] = x
                    Enqueue(Q,y)
            color[x] = black                  // finish x
*/
void BFS(Graph G, int s){
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List Q = newList();
	append(Q,s);
	moveFront(Q);
	while(index(Q)!=-1){
		int x = get(Q);
		List temp = G->neighbor[x];
		moveFront(temp);
		for(moveFront(temp); index(temp)!=-1; moveNext(temp)){
			int y = get(temp);
			if(G->color[y] == WHITE){
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(Q,y);
			}
		}
		G->color[x] = BLACK;
		moveNext(Q);
	}
	freeList(&Q);
}

/*** Other operations ***/
// prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
	if (G == NULL) {
		printf("Error: cannot call printGraph() on null graph object");
		exit(EXIT_FAILURE);
	}
    
	for( int i = 1; i<=getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->neighbor[i]);
		fprintf(out, "\n");	
	}
}