//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa2
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
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif