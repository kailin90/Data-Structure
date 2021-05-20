//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa2
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]){

	int n, u, v;
	FILE *in, *out;
	char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

	fscanf(in, "%d", &n);
	Graph G = newGraph(n);

	while(fgets(line, MAX_LEN, in) != NULL)
	{
		fscanf(in, "%d %d", &u, &v);
		if (u == 0 && v == 0){
			break;
		}
		addEdge(G, u, v);
	}
	printGraph(out, G);

	int distance=getDist(G, v);
	List L = newList();
	while(fgets(line, MAX_LEN, in) != NULL){
		fscanf(in, "%d %d", &u, &v);
		if (u == 0 && v == 0){
			break;
		}
		fprintf(out, "\n");
		BFS(G, u);
		distance = getDist(G, v);
		if(distance != INF){
			getPath(L, G, v);
			fprintf(out, "The distance from %d to %d is %d\n", u, v, distance);
			fprintf(out, "A shortest %d-%d path is: ", u, v);
			printList(out, L);
			fprintf(out, "\n");
		}else if (distance == INF){
			fprintf(out, "The distance from %d to %d is infinity\n", u, v);
			fprintf(out, "No %d-%d path exists\n", u, v);
		}
		clear(L);
	}
	// close files
	fclose(in);
	fclose(out);
	freeList(&L);
	freeGraph(&G);
	
	return(0);
}