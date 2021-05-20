//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa5
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// DictionaryClient.c
// Test client for Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
   
   Dictionary A = newDictionary(1);

   // add pairs to A --------------------------------------
   insert(A,"a",1);
   insert(A,"b",2);
   insert(A,"c",3);
   insert(A,"d",4);
   insert(A,"e",5);
   insert(A,"f",6);
   insert(A,"g",7);
   insert(A,"h",8);
   insert(A,"i",9);
   insert(A,"j",10);
   insert(A,"k",11);
   insert(A,"l",12);

   printf("Testing printDictionary(): \n");
   printDictionary(stdout,A);

   printf("Testing size(): ");
   int s = size(A);
   if (s!=12){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   printf("Testing getunique(): ");
   int unique = getUnique(A);
   if (unique!=1){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   printf("Testing lookup(): ");
   int look = lookup(A,"j");
   if (look!=10){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   printf("Testing delete(): ");
   delete(A,"a");
   look = lookup(A,"a");
   if (look!=VAL_UNDEF){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   printf("Testing makeEmpty(): \n");
   makeEmpty(A);
   printDictionary(stdout,A);
   printf("Nothing should be printed\n");
   printf("================\n");

   insert(A,"a",12);
   insert(A,"b",11);
   insert(A,"c",10);
   insert(A,"d",9);
   insert(A,"e",8);
   insert(A,"f",7);
   insert(A,"g",6);
   insert(A,"h",5);
   insert(A,"i",4);
   insert(A,"j",3);
   insert(A,"k",2);
   insert(A,"l",1);

   printf("Testing beginForward() and currentVal(): ");
   beginForward(A);
   int val = currentVal(A);
   if((strcmp (currentKey(A),"a") != 0) && val!=12){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   printf("Testing beginForward() and currentKey(): ");
   beginReverse(A);
   if(strcmp (currentKey(A),"l") != 0){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   printf("Testing prev(): ");
   prev(A);
   if(strcmp (currentKey(A),"k") != 0){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   printf("Testing next(): ");
   next(A);
   if(strcmp (currentKey(A),"l") != 0){
      printf("failed\n");
   }else{
      printf("passed\n");
   }

   // free heap memory ------------------------------------
   freeDictionary(&A);

   return(0);
}