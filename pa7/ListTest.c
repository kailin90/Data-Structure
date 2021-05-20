//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa7
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
    List A = newList();
    List B = newList();

    printf("Testing append() and prepend():\n");
    for(int i=1; i<=20; i++){
        append(A,i);
        prepend(B,i);
    }    

    printf("append list A():");
    printf("\n");
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%ld ", get(A));
    }
    printf("\n\n");

    printf("prepend list B():");
    printf("\n");
    for(moveBack(B); index(B)>=0; movePrev(B)){
        printf("%ld ", get(B));
    }
    printf("\n\n");

    printf("Testing moveFront():");
    moveFront(A);
    if(get(A)==front(A)){
        printf("passed\n\n");
    }else{
        printf("failed\n\n");
    }

    printf("Testing moveBack():");
    moveBack(B);
    if(get(B)==back(B)){
        printf("passed\n\n");
    }else{
        printf("failed\n\n");
    }

    printf("Testing insertBefore() on list A:\n");
    insertBefore(A,0);
    printList(stdout,A);
    printf("\n\n");

    printf("Testing insertAfter() on list B:\n");
    insertAfter(B,0);
    printList(stdout,B);
    printf("\n\n");

    printf("Testing deleteFront():\n");
    deleteFront(A);
    printList(stdout,A);
    printf("\n\n");

    printf("Testing deleteBack():\n");
    deleteFront(B);
    printList(stdout,B);
    printf("\n\n");

    printf("Testing delete() on A:\n"); 
    delete(A);
    printList(stdout,A);
    printf("\n\n");

    printf("Testing clear() on B:\n");
    clear(B);
    printList(stdout,B);
    printf("---------------------\n");
    printf("Nothing should be printed above");
    printf("\n\n");

    freeList(&A);
    freeList(&B);
    return 0;
}