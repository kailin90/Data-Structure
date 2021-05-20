//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa3
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printf("Print out Graph:\n");
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "Vertex:%d Discover:%2d Finish:%2d Parent:%2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printf("Print out List\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printf("Testing copyGraph(), this should be the same as graph printed out previsouly:\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printf("Testing transpose(), this should be the transpose of previsou graph:\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");
   printf("The correct output should be: 57621483\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);

   return(0);
}
