//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa3
//-----------------------------------------------------------------------------

#ifndef Graph_H
#define Graph_H

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define NIL 0
#define INF -1
#define UNDEF -2

typedef struct GraphObj *Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
#endif