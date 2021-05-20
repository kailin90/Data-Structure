//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa5
//-----------------------------------------------------------------------------

#include "Dictionary.h"

typedef struct NodeObj{
    KEY_TYPE  key;
    VAL_TYPE value;
    struct NodeObj* left;
    struct NodeObj* right;
    struct NodeObj* parent;
} NodeObj;
typedef NodeObj *Node;

Node newNode(KEY_TYPE key, VAL_TYPE value) {
   Node N = malloc(sizeof(NodeObj));
   N->key = key;
   N->value = value;
   N->parent = NULL;
   N->left = N->right = NULL;
   return(N);
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
    }
}

typedef struct DictionaryObj {
    int size;
    int unique;;
    Node cursor;
    Node root;
} DictionaryObj;

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
    Dictionary D = (DictionaryObj*)malloc(sizeof(DictionaryObj));
    D->size = 0;
    D->unique = unique;
    D->cursor = NULL;
    D->root = NULL;
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
    if( pD!=NULL && *pD!=NULL ){
        makeEmpty(*pD);
        free(*pD);
        *pD = NULL;
   }
}

// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
    return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
    return D->unique;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    if( D==NULL ){
        printf("Error: calling lookup() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    Node temp = D->root;
    while(temp != NULL){
        int compare = KEY_CMP(k,temp->key);
        if(compare==0){
            return temp->value;
        }else if(compare >0){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    return VAL_UNDEF;   
}


// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 

/*
TreeInsert(T, z)
   y = NIL
   x = T.root
   while x != NIL
      y = x
      if z.key < x.key
         x = x.left
      else 
         x = x.right
   z.parent = y
   if y == NIL
      T.root = z    // tree T was empty
   else if z.key < y.key
      y.left = z
   else 
      y.right = z
*/

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    if (D==NULL){
        printf("Error: Calling insert() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    Node new = newNode(k,v);
    Node x = D->root;
    Node y=NULL;
    
    while(x!= NULL){
        y=x;
        if(KEY_CMP(k, x->key) < 0){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    if( y==NULL ){
        D->root = new;
    }else if(KEY_CMP(k, y->key) < 0){
        y->left = new;
    }else{
        y->right = new;
    }

    new->parent = y;
    D->size++;
}

/*
Transplant(T, u, v)
   if u.parent == NIL
      T.root = v
   else if u == u.parent.left
      u.parent.left = v
   else 
      u.parent.right = v
   if v != NIL
      v.parent = u.parent
*/
void transplant( Dictionary D, Node u, Node v){
    if( u->parent == NULL){
        D->root = v;
    }else if (u == (u->parent)->left){
        u->parent->left = v;
    }else{
        u->parent->right =v;
    }
    if(v!=NULL){
        v->parent = u->parent;
    }
}

/*
TreeMinimum(x) Pre: x != NIL
   while x.left != NIL
      x = x.left
   return x
*/

Node treeMinimum(Node x){
    while (x->left != NULL){
        x=x->left;
    }
    return x;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)

/*
Delete(T, z)
   if z.left == NIL               // case 1  or case 2.1 (right only)
      Transplant(T, z, z.right)
   else if z.right == NIL         // case 2.2 (left only)
      Transplant(T, z, z.left)
   else                           // case 3
      y = TreeMinimum(z.right)
      if y.parent != z
         Transplant(T, y, y.right)
         y.right = z.right
         y.right.parent = y
      Transplant(T, z, y)
      y.left = z.left
      y.left.parent = y
*/

void delete(Dictionary D, KEY_TYPE k){
    if (D==NULL){
        printf("Error: Calling delete() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    if(lookup(D,k)==VAL_UNDEF){
        printf("Error: D does not contain a pair whose key is k");
        exit(EXIT_FAILURE);
    }

    Node z = D->root;
    while(KEY_CMP(k,z->key) != 0){
        if(z==NULL){
            return;
        }else if(KEY_CMP(k,z->key) > 0){
            z = z->right;
        }else{
            z = z->left;
        }
    }

    if(D->cursor == z){
        D->cursor=NULL;
    }

    if( z->left == NULL){
        transplant(D, z, z->right);
    }else if(z->right == NULL){
        transplant(D,z,z->left);
    }else{
        Node y = treeMinimum(z->right);
        if(y->parent != z){
            transplant(D,y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        transplant(D,z,y);
        y->left=z->left;
        y->left->parent=y;
    }    

    D->size--;
    freeNode(&z);
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
    while(D->root != NULL) {
        delete(D, D->root->key);
    }
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D){
    if (D == NULL) {
        printf("Error: calling beginForward() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    if (size(D) > 0) {
        Node A = D->root;
        while (A->left != NULL) {
            A = A->left;
        }

        D->cursor = A;
        return A->value;
    }

    return VAL_UNDEF;   
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
    if (D == NULL) {
        printf("Error: Calling beginReverse() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    if (size(D) > 0) {
        Node n = D->root;
        while (n->right != NULL) {
            n = n->right;
        }
        D->cursor = n;
        return n->value;
    }

    return VAL_UNDEF;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
    if (D==NULL){
        printf("Error: Calling currentKey() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    if (D->cursor == NULL){
        return KEY_UNDEF;
    }else{
        return D->cursor->key;
    }    
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
    if (D==NULL){
        printf("Error: Calling currentVal() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    if (D->cursor == NULL){
        return VAL_UNDEF;
    }else{
        return D->cursor->value;
    }
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
    if (D == NULL) {
        printf("Error: calling next() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    if (D->cursor == NULL) {
        return VAL_UNDEF;
    }

    Node A = D->cursor;
    if (A->right != NULL) {
        Node current = A->right;
        while (current->left != NULL) {
            current = current->left;
        }
        D->cursor = current;
        return current->value;
    }

    Node temp = A->parent;
    while (temp != NULL && A == temp->right) {
        A = temp;
        temp = temp->parent;
    }

    if (temp == NULL) {
        D->cursor = NULL;
        return VAL_UNDEF;
    }

    D->cursor = temp;
    return temp->value;
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D){
    if (D == NULL) {
        printf("Error: calling next() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    if (D->cursor == NULL) {
        return VAL_UNDEF;
    }

    Node A = D->cursor;
    if (A->left != NULL) {
        Node current = A->left;
        while (current->right != NULL) {
            current = current->right;
        }
        D->cursor = current;
        return current->value;
    }

    Node temp = A->parent;
    while (temp != NULL && A == temp->left) {
        A = temp;
        temp = temp->parent;
    }

    if (temp == NULL) {
        D->cursor = temp;
        return VAL_UNDEF;
    }
    
    D->cursor = temp;
    return temp->value;
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
    if (D == NULL) {
        printf("Error: calling printDictionary() on null Dictionary reference");
        exit(EXIT_FAILURE);
    }

    beginForward(D);
    for (int i = 0; i < size(D); i++) {
        fprintf(out, "%s %d\n", currentKey(D), currentVal(D));
        next(D);
    }
}