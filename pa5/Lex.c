//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa5
//-----------------------------------------------------------------------------

#include "Dictionary.h"

#define MAX_LEN 300

int main(int argc, char *argv[]){
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

    fseek(in, 0, SEEK_SET);
    char** strings = malloc(line_count*sizeof(char*));
    for(int i = 0; i<line_count; i++){
        strings[i] = malloc(MAX_LEN*sizeof(char));
    }

    for(int i=0; fgets(line, MAX_LEN, in) != NULL; i++){
        strcpy(strings[i],line);
    }

    Dictionary D = newDictionary(0);
    for(int i=0; i<line_count;i++){
        insert(D,&strings[i][0],i);
    }

    for(beginForward(D); currentVal(D)!=VAL_UNDEF; next(D)){
        fprintf(out, "%s", currentKey(D));
    }

    /* close files */
    freeDictionary(&D);
    for(int i=0; i<line_count; i++){
        free(strings[i]);
    }
    free(strings);
    fclose(in);
    fclose(out);

    return 0;
}