//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa6
//-----------------------------------------------------------------------------

#include "Dictionary.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {
    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];

    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

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
    while (fgets(line, MAX_LEN, in) != NULL) {
        line_count++;
    }

    fseek(in, 0, SEEK_SET);
    char** strings = malloc(line_count*sizeof(char*));
    for (int i = 0; i < line_count; i++) {
        strings[i] = malloc(MAX_LEN*sizeof(char));
    }

    int i = 0;
    while (i < line_count) {
        fgets(strings[i], MAX_LEN, in);
        i++;
    }
    Dictionary D = newDictionary(0);
    for (i = 0; i < line_count; i++) {
        insert(D, strings[i], VAL_UNDEF);
    }
    printDictionary(out, D, "pre");
    fprintf(out, "\n");
    printDictionary(out, D, "in");
    fprintf(out, "\n");
    printDictionary(out, D, "post");


    /* close files */
    freeDictionary(&D);
    for (i = 0; i < line_count; i++) {
        free(strings[i]);
    }
    free(strings);
    fclose(in);
    fclose(out);
    return 0;
}