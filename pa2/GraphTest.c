//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa2
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, n=35;
   List  P = newList();
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   printf("Test getOrder(): %d\n", getOrder(G));
   printf("Test getSize(): %d\n", getSize(G));
   printf("Test getSource() without BFS(): %d\n", getSource(G));
   printf("Test getParent() without BFS(): %d\n", getParent(G, 33));
   printf("Test getDist() without BFS(): %d\n", getDist(G, 33));

   BFS(G,1);
   printf("Test getSource() with BFS(): %d\n", getSource(G));
   printf("Test getParent() with BFS(): %d\n", getParent(G, 33));
   printf("Test getDist() with BFS(): %d\n", getDist(G, 33));

   printf("Test getPatch():\n");
   getPath(P,G,33);
   moveFront(P);
   while (index(P)!=-1){
      printf("%d ", get(P));
      moveNext(P);
   }
   printf("\n");

   printf("Test makeNull():\n");
   makeNull(G);
   printf("Test getSource() with makeNull(): %d\n", getSource(G));
   printf("Test getParent() with makeNull(): %d\n", getParent(G, 33));
   printf("Test getDist() with makeNull(): %d\n", getDist(G, 33));

   // Free objects 
   freeList(&P);
   freeGraph(&G);

   return(0);
}