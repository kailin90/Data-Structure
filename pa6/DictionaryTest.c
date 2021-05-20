//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa6
//-----------------------------------------------------------------------------

#include"Dictionary.h"

int main(int argc, char* argv[]){
    Dictionary A = newDictionary(0);
    int* x;
    int* value = malloc(10*sizeof(int));
    char* key[] = { "a","b","c","d","e","f","g","h","i","j"};
    for (int i = 0; i < 10; i++){
        value[i] = i;
    } 

    printf("Testing printDictionary() and insert():\n");
    
    for(int i=0; i<10; i++){
        insert(A, key[i], &value[i]);
    }
    printDictionary(stdout, A, "in");
    printf("\n");
    printDictionary(stdout, A, "pre");
    printf("\n");
    printDictionary(stdout, A, "post");
    printf("\n\n");

    printf("Testing look up:\n");
    printf("look up 'a':%d\n", *lookup(A, "a"));
    printf("look up 'j':%d\n\n", *lookup(A, "j"));
    
    printf("Testing beginForward() and next():\n");
    x=beginForward(A);
    while(currentVal(A)!=VAL_UNDEF){
        printf("key: %s value: %d\n", currentKey(A), *x);
        x=next(A);
    }
    printf("\n");

    printf("Testing beginReverse() and prev():\n");
    x=beginReverse(A);
    while(currentVal(A)!=VAL_UNDEF){
        printf("key: %s value: %d\n", currentKey(A), *x);
        x=prev(A);
    }
    printf("\n");    

    printf("Testing makeEmpty():\n");
    makeEmpty(A);
    printf("Current size of A: %d\n", size(A));
    printDictionary(stdout, A, "in");
    printf("\n");
    printDictionary(stdout, A, "pre");
    printf("\n");
    printDictionary(stdout, A, "post");
    printf("\n");
    
    free(value);
    freeDictionary(&A);
    return(0);
}