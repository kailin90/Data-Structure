//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa6
//-----------------------------------------------------------------------------
#include "Dictionary.h"

#define BLACK 0
#define RED 1

// Constructors-Destructors ---------------------------------------------------
typedef struct NodeObj{
    KEY_TYPE key;
    VAL_TYPE value;
    int color;
    struct NodeObj *left;
    struct NodeObj *right;
    struct NodeObj *parent;
} NodeObj;

typedef NodeObj *Node;

Node newNode(KEY_TYPE key, VAL_TYPE value){
    Node N = malloc(sizeof(NodeObj));
    N->key = key;
    N->value = value;
    N->parent = NULL;
    N->left = N->right = NULL;
    N->color = BLACK;
    return N;
}

void freeNode(Node* pN){
    if(pN!=NULL && *pN!=NULL){
      free(*pN);
      *pN = NULL;
    }
}

typedef struct DictionaryObj {
    int unique;
    int size;
    Node root;
    Node cursor;
    Node nil;
} DictionaryObj;

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique) {
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->size = 0;
    D->nil = newNode(KEY_UNDEF, VAL_UNDEF);
    D->unique = unique;
    D->cursor = NULL; 
    D->root = D->nil;
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD) {
    if( pD!=NULL && *pD!=NULL ){
        makeEmpty(*pD);
        free((*pD)->nil);
        free(*pD);
        *pD = NULL;
    }
}

// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D) {
    return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D) {
    return D->unique;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
    Node n = D->root;
    int compare =0;
    while(n != D->nil ){
        compare = KEY_CMP(k,n->key);
        if(compare ==0){
            return n->value;
        }
        if(compare >0){
            n = n->right;
        }else{
            n = n->left;
        }
    }
    return VAL_UNDEF;
}

Node TreeSearch(Dictionary D, Node R, char* k){
    if(R==D->nil || KEY_CMP(k, R->key) == 0){
        return R;
    }
    
    if(KEY_CMP(k, R->key) < 0){
        return TreeSearch(D, R->left, k);
    }else{
        return TreeSearch(D, R->right, k);
    }
}

Node TreeMinimum(Dictionary D, Node x) {
    while (x->left != D->nil) {
        x = x->left;
    }
    return x;
}

Node TreeMaximum(Dictionary D, Node x) {
    while (x->right != D->nil) {
        x = x->right;
    }
    return x;
}

void LeftRotate(Dictionary D, Node x) {
    Node y=x->right;
    x->right=y->left;
    if(y->left != D->nil){
        y->left->parent=x;
    }
    y->parent=x->parent;
    if(x->parent == D->nil){
        D->root=y;
    }else if (x==x->parent->left){
        x->parent->left=y;
    }else {
        x->parent->right=y;
    }
    y->left=x;
    x->parent=y;
}

void RightRotate(Dictionary D, Node x) {
    Node y=x->left;
    x->left=y->right;
    if(y->right != D->nil){
        y->right->parent=x;
    }
    y->parent = x->parent;
    if(x->parent == D->nil){
        D->root=y;
    }else if(x == x->parent->right){
        x->parent->right=y;
    }else{
        x->parent->left=y;
    }
    y->right=x;
    x->parent=y;
}


void RB_Transplant(Dictionary D, Node u, Node v) {
    if(u->parent == D->nil){
        D->root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RB_InsertFixUp(Dictionary D, Node z) {
    Node y;
    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->right){
                    z = z->parent;
                    LeftRotate(D, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(D, z->parent->parent);
            }
        }else{
            y = z->parent->parent->left;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    RightRotate(D, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(D, z->parent->parent);
            }
        }
    }
    D->root->color=BLACK;
}

void RB_DeleteFixUp(Dictionary D, Node x) {
    Node w = D->nil;
    while(x != D->root && x->color == BLACK) {
        if(x == x->parent->left) {
            w = x->parent->right;
            if(w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(D, x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }else{
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(D, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(D, x->parent);
                x = D->root;
            }
        }else{
            w = x->parent->left;
            if(w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(D, x->parent);
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(D, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(D, x->parent);
                x = D->root;
            }
        }
    }
    x->color = BLACK;
}
// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
    if (D->unique == 1 && lookup(D, k) != VAL_UNDEF) {
        printf("Error: calling insert() on duplicate key");
        exit(EXIT_FAILURE);
    }

    Node z = newNode(k, v);
    Node y = D->nil;
    Node x = D->root;
    while (x != D->nil) {
        y = x;
        if (KEY_CMP(z->key, x->key) < 0) {
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if (y == D->nil) {
        D->root = z;
    }else if(KEY_CMP(z->key, y->key) < 0) {
        y->left = z;
    }else{
        y->right = z;
    }
    z->left = D->nil;
    z->right = D->nil;
    z->color = RED;
    RB_InsertFixUp(D, z);
    D->size++;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k) {
    Node z = TreeSearch(D, D->root, k);
    if (D->cursor == z) {
        D->cursor = NULL;
    }

    Node y=z;
    Node x;
    int y_original_color = y->color;
    if (z->left == D->nil) {
        x = z->right;
        RB_Transplant(D, z, z->right);
    }else if(z->right == D->nil){
        x = z->left;
        RB_Transplant(D, z, z->left);
    }else{
        y = TreeMinimum(D, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }else{
            RB_Transplant(D, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(D, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(y_original_color == BLACK){
        RB_DeleteFixUp(D, x);
    }

    freeNode(&z);
    D->size--;
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D) {
    while(D->root != D->nil) {
        delete(D, D->root->key);
    }
    D->cursor = D->nil;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D) {
	D->cursor = D->root;
	if(D->size == 0){
	    return VAL_UNDEF;
	}
    D->cursor = TreeMinimum(D, D->cursor);
	return D->cursor->value;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D) {
	D->cursor = D->root;
	if(D->size == 0){
        return VAL_UNDEF;
    }
    D->cursor = TreeMaximum(D, D->cursor);
    return D->cursor->value;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D) {
    if (D->cursor == NULL) {
        return KEY_UNDEF;
    }
    return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D) {
    if(D->cursor == NULL){
        return VAL_UNDEF;
    }
    return D->cursor->value;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D) {
    Node n = D->cursor;
    if (D->cursor->right != D->nil) {
        D->cursor =  TreeMinimum(D, D->cursor->right);
        if (D->cursor == NULL) {
            D->cursor = D->nil;
        }
        return D->cursor->value;
    }

    Node y = n->parent;
    while (y != NULL && n == y->right) {
        n = y;
        y = y->parent;
    }

    D->cursor = y;
    if (D->cursor == NULL) {
        D->cursor = D->nil;
    }
    return D->cursor->value;
}

// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D) {
    Node n = D->cursor;
    if (D->cursor->left != D->nil) {
        D->cursor =  TreeMaximum(D, D->cursor->left);
        if (D->cursor == NULL) {
            D->cursor = D->nil;
        }
        return D->cursor->value;
    }

    Node y = n->parent;
    while (y != D->nil && n == y->left) {
        n = y;
        y = y->parent;
    }
    D->cursor = y;
    if (D->cursor == NULL) {
        D->cursor = D->nil;
    }
    return D->cursor->value;
}

// Other operations -----------------------------------------------------------

void pre(FILE *out, Node N){
    if (N->left != NULL && N->right != NULL){
        fprintf(out, "%s", N->key);
        pre(out, N->left);
        pre(out, N->right);
    }
}

void in(FILE *out, Node N){
    if (N->left != NULL && N->right != NULL){
        in(out, N->left);
        fprintf(out, "%s", N->key);
        in(out, N->right);
    }
}

void post(FILE *out, Node N){
    if (N->left != NULL && N->right != NULL){
        post(out, N->left);
        post(out, N->right);
        fprintf(out, "%s", N->key);
    }
}

// printDictionary()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printDictionary(FILE* out, Dictionary D, const char* ord){
    if(KEY_CMP(ord, "pre") == 0){
        fprintf(out, "******************************************************\n");
        fprintf(out, "PRE-ORDER:\n");
        fprintf(out, "******************************************************\n");
        pre(out, D->root);
    }else if(KEY_CMP(ord, "in") == 0){
        fprintf(out, "******************************************************\n");
        fprintf(out, "IN-ORDER:\n");
        fprintf(out, "******************************************************\n");
        in(out, D->root);
    }else if(KEY_CMP(ord, "post") == 0){
        fprintf(out, "******************************************************\n");
        fprintf(out, "POST-ORDER:\n");
        fprintf(out, "******************************************************\n");
        post(out, D->root);
    }
}