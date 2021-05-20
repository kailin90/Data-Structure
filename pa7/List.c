//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa7
//-----------------------------------------------------------------------------
#include "List.h"
#include "BigInteger.h"
#define LIST_ELEMENT long

typedef struct NodeObj{
    int data;
    struct NodeObj *previous;
    struct NodeObj *next;
} NodeObj;

typedef NodeObj *Node;
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
}ListObj;

Node newNode(int x){
    Node node = malloc(sizeof(NodeObj));
    node->data=x;
    node->next=NULL;
    node->previous=NULL;
    return node;
}

void freeNode(Node* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
      free(*pQ);
      *pQ = NULL;
   }
}

// Creates and returns a new empty List.
List newList(void){
    List list;
    list=malloc(sizeof(ListObj));
    list->front=NULL;
    list->back=NULL;
    list->cursor=NULL;
    list->length=0;
    list->index=-1;
    return list;
} 
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL){
    if( pL!=NULL && *pL!=NULL){
        moveFront(*pL);
        while(length(*pL)>0){
            deleteBack(*pL);
        }
        free(*pL);
        *pL=NULL;
    }
}



// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L){
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if (L!=NULL){
        return L->index;
    }else{
        return -1;
    }
}

// Returns front element of L. Pre: length()>0
LIST_ELEMENT front(List L){
    if (length(L)>0){
        return L->front->data;
    }else{
        printf("Error: cannot front() empty or null list");
        exit(EXIT_FAILURE);
    }
}

// Returns back element of L. Pre: length()>0
LIST_ELEMENT back(List L){
    if (length(L)>0){
        return L->back->data;
    }else{
        printf("Error: cannot back() empty or null list");
        exit(EXIT_FAILURE);
    }    
}

// Returns cursor element of L. Pre: length()>0, index()>=0
LIST_ELEMENT get(List L){
    if (length(L)<=0 || index(L)<0){
        printf("Error: cannot get() length or index error");
        exit(EXIT_FAILURE);
    }else{
        return L->cursor->data;
    }
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
/*
int equals(List A, List B){
   int eq = 0; 
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL )
   {
      printf("Stack Error: calling equals() on NULL Stack reference\n");
      exit(EXIT_FAILURE);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL)
   {
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}
*/

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L){
    if (L == NULL){
        printf("Error: cannot clear() empty list");
        exit(EXIT_FAILURE);        
    }

    while(length(L)>0){
        deleteFront(L);
    }
    L->front=NULL;
    L->back=NULL;
    L->cursor=NULL;
    L->length=0;
    L->index=-1;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x){
    if (length(L)<=0){
        printf("Error: cannot set() empty list");
        exit(EXIT_FAILURE);
    }

    if (index<0){
        printf("Error: inproper cursor in set()");
        exit(EXIT_FAILURE);
    }

    if (L==NULL){
        printf("Error: NULL list in set()");
        exit(EXIT_FAILURE);
    }
    L->cursor->data=x;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if (length(L)>0){
        L->cursor=L->front;
        L->index=0;
    }
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if (L->length>0){
        L->cursor=L->back;
        L->index=L->length-1;
    }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    if (L->cursor!=NULL && L->cursor!=L->front){
        L->cursor=L->cursor->previous;
        L->index--;
    }else if (L->cursor!=NULL && L->cursor==L->front){
        L->cursor=NULL;
        L->index=-1;
    }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    if (L->cursor!=NULL && L->cursor!=L->back){
        L->cursor=L->cursor->next;
        L->index++;
    }else if (L->cursor!=NULL && L->cursor==L->back){
        L->cursor=NULL;
        L->index=-1;
    }   
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x){
    if (L==NULL){
        printf("Error: cannot prepend() NULL list");
        exit(EXIT_FAILURE);
    }

    Node new=newNode(x);

    if (length(L)==0){
        L->front=L->back=new;      
    }else{
        new->next=L->front;
        L->front->previous=new;
        L->front=new;
    }
    L->length++;
    if (L->cursor!=NULL){
        L->index++;
    }
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x){
    if (L==NULL){
        printf("Error: cannot append() NULL list");
        exit(EXIT_FAILURE);
    }
    Node new=newNode(x);
    if (length(L)==0){
        L->front=L->back=new;      
    }else if(L->length==1){
        L->back=new;
        L->front->next=L->back;
        L->back->previous=L->front;
    }else{
        new->previous=L->back;
        L->back->next=new;
        L->back=new;
    }
    L->length++;    
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    if (L==NULL){
        printf("Error: cannot insertBefore() NULL list");
        exit(EXIT_FAILURE);
    }

    if (length(L)<=0){
        printf("Error: cannot insertBefore() empty list");
        exit(EXIT_FAILURE);        
    }

    if (index(L)<0){
        printf("Error: index error in insertBefore");
        exit(EXIT_FAILURE);         
    }

    if(L->index>=1){
        Node new = newNode(x);
        new->previous=L->cursor->previous;
        L->cursor->previous=new;
        new->previous->next=new;
        new->next=L->cursor;
        L->index++;
        L->length++;
    }else{
      prepend(L,x);
    }
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
    if (L==NULL){
        printf("Error: cannot insertAfter() NULL list");
        exit(EXIT_FAILURE);
    }

    if (length(L)<=0){
        printf("Error: cannot insertAfter() empty list");
        exit(EXIT_FAILURE);        
    }

    if (index(L)<0){
        printf("Error: index error in insertAfter()");
        exit(EXIT_FAILURE);         
    }

    if(L->index < L->length-1){
        Node new=newNode(x);
        new->next=L->cursor->next;
        new->previous=L->cursor;
        L->cursor->next->previous=new;
        L->cursor->next=new;
        L->length++;
    }else{
        append(L,x);
    }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if (L==NULL){
        printf("Error: cannot deleteFront() null list");
        exit(EXIT_FAILURE);
    }

    if (length(L)<=0){
        printf("Error: cannot deleteFront() empty list");
        exit(EXIT_FAILURE);        
    }

    Node toDelete=L->front;
    if (length(L)==1){
        L->front=L->back=NULL;
        freeNode(&toDelete);
    }else{
        L->front=toDelete->next;
        L->front->previous=NULL;
        L->index--;
        freeNode(&toDelete);
    }
    L->length--;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if (L==NULL){
        printf("Error: cannot deleteBack() null list");
        exit(EXIT_FAILURE);
    }

    if (length(L)<=0){
        printf("Error: cannot deleteBack() empty list");
        exit(EXIT_FAILURE);        
    }

  if(L!=NULL){
    Node temp = L->back;
    if(L->length>1){
      L->back=(L->back)->previous;
      L->back->next=NULL;
      if(L->index==L->length-1){
        L->index=-1;
      }
    }else{
      L->front = NULL;
      L->back= NULL;
      L->index=-1;
    }
    L->length=L->length-1;
    freeNode(&temp);
  }
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    if (L==NULL){
        printf("Error: cannot delete() from null list");
        exit(EXIT_FAILURE);
    }

    if (length(L)<=0){
        printf("Error: cannot delete() from empty list");
        exit(EXIT_FAILURE);        
    }

    if (index<0){
        printf("Error: index error in delete()");
        exit(EXIT_FAILURE);           
    }

    if (L->cursor==L->front){
        deleteFront(L);
    }else if (L->cursor==L->back){
        deleteBack(L);
    }else{
        Node toDelete=L->cursor;
        L->cursor->previous->next=toDelete->next;
        L->cursor->next->previous=toDelete->previous;
        freeNode(&toDelete);
        L->length--;
        L->cursor=NULL;
        L->index=-1;   
    }
}


// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    Node toPrint=L->front;
    while (toPrint!=NULL){
        fprintf(out, "%d", toPrint->data);
        toPrint=toPrint->next;
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    List copied = newList();
    Node toCopy = L->front;
    while (toCopy!=NULL){
        append(copied, toCopy->data);
        toCopy=toCopy->next;
    }
    return copied;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B){
    List toConcat = newList();
    Node toConcatA=A->front;
    Node toConcatB=B->front;
    while (toConcatA!=NULL){
        append(toConcat,toConcatA->data);
        toConcatA=toConcatA->next;
    }
    while (toConcatB!=NULL){
        append(toConcat,toConcatB->data);
        toConcatB=toConcatB->next;
    }
    return toConcat;
}