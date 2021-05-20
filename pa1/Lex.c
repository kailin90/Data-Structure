//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa1
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

	int line_count;
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

	// read each line of input file, then count and print tokens
	line_count=0;
	while(fgets(line, MAX_LEN, in) != NULL){
		line_count++;
	}

	char words[line_count][MAX_LEN];
	rewind(in);
	int x=0;
	while(fgets(line, MAX_LEN, in) != NULL){
		strcpy(words[x],line);
		x++;
	}

	List l = newList();
	append(l,0);
	
	int i=1;
	while(i<line_count){
		moveFront(l);
		int j=i-1;
		while(index(l)!=j){
			moveNext(l);
		}

		while(j!=-1 && strcmp(words[i],words[get(l)])<0){
			movePrev(l);
			j--;
		}

		if(index(l)<=-1) {
			prepend(l,i);
		}else if(index(l)>-1){
			insertAfter(l,i);
		}
		i++;
	}

	moveFront(l);
	for(int m=0; m<line_count; m++){
		int n=get(l);
		fprintf(out,"%s\n", words[n]);
		moveNext(l);
	}

	// close files 
	fclose(in);
	fclose(out);
	freeList(&l);

	return(0);
}