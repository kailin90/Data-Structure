//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa3
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {
	int n, u, v;
	FILE* in, * out;
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

	while (fgets(line, MAX_LEN, in) != NULL){
		fscanf(in, "%d %d", &u, &v);
		if (u == 0 && v == 0){
			break;
		}
		addArc(G, u, v);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out,"\n");

	List l = newList();
	for (int i = 1; i <=getOrder(G) ; i++){
		append(l, i);
	}
	DFS(G, l);
	Graph t = transpose(G);
	DFS(t, l);
	int strongly_connected_components = 0;
	moveFront(l);
	while (index(l) !=-1){
		if (getParent(t, get(l)) == NIL)
			strongly_connected_components++;
		moveNext(l);
	}
	fprintf(out, "G contains %d strongly connected components:", strongly_connected_components);
	fprintf(out,"\n");

	List new = newList();
	int num = 1;
	moveBack(l);
	while (index(l) >= 0){
		if(getParent(t, get(l)) != NIL){
			prepend(new, get(l));
			movePrev(l);
		}else if(getParent(t, get(l)) == NIL){
			prepend(new, get(l));
			fprintf(out, "Component %d:", num);
			printList(out, new);
			fprintf(out,"\n");
			num++;
			clear(new);
			movePrev(l);			
		}
	}

	// close files
	fclose(in);
	fclose(out);
	freeList(&l);
	freeList(&new);
	freeGraph(&G);
	freeGraph(&t);
	return(0);
}