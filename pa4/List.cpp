//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa4
//-----------------------------------------------------------------------------
#include"List.h"

using namespace std;

List::Node::Node(int x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Creates new List in the empty state.
List::List(){
    frontDummy =new Node(0);
    backDummy =new Node(0);
    frontDummy->next=backDummy;
    backDummy->prev=frontDummy;
    beforeCursor=frontDummy;
    afterCursor=backDummy;
    pos_cursor=0;
    num_elements=0;
}

// Copy constructor.
List::List(const List& L){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node *N = L.frontDummy->next;
    while (N != L.backDummy && N != nullptr) {
        this->insertBefore(N->data);
        N = N->next;
    }

    this->moveFront();
}


// Destructor
List::~List(){
    moveFront();
    while (!isEmpty() && num_elements > 0) {
        eraseAfter();
    }
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
    if (num_elements == 0){
        return true;
    }else{
        return false;
    }
}

// size()
// Returns the size of this List.
int List::size(){
    return num_elements;
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
    return pos_cursor;
}

// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor=frontDummy;
    afterCursor=frontDummy->next;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
    if (position() < size()) {
        return afterCursor->data;
    }else{
        cout << "position()>=size() in peekNext()";
        exit(EXIT_FAILURE);
    }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
    if (position() > 0) {
        return beforeCursor->data;
    }else{
        cout << "position()>0 in peekPrev()";
        exit(EXIT_FAILURE);        
    }
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<size() 
int List::moveNext(){
    if(position() >= size()){
        cout << "position() >= size() in moveNext()";
        exit(EXIT_FAILURE);
    }else{
        pos_cursor++;
        afterCursor = afterCursor->next;
        beforeCursor = beforeCursor->next;
        return beforeCursor->data;
    }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
int List::movePrev(){
    if(position() == 0){
        cout << "position() <= size() in movePrev()";
        exit(EXIT_FAILURE);
    }else{
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
        pos_cursor--;
        return afterCursor->data;
    }
}       

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x){
    Node* N = new Node(x);
    beforeCursor->next = N;
    N->prev = beforeCursor;
    N->next = afterCursor;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x){
    Node* node = new Node(x);
    node->prev= beforeCursor;
    node->next = afterCursor;
    beforeCursor->next = node;
    afterCursor->prev = node;
    beforeCursor=node;
    pos_cursor++;
    num_elements++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
    if (position() == size()){
        cout << "position() >= size() in eraseAfter()";
        exit(EXIT_FAILURE);  
    }else {
        Node *N = afterCursor;
        beforeCursor->next=afterCursor->next;
        afterCursor->next->prev = beforeCursor;
        afterCursor=afterCursor->next;
        num_elements--;
        delete N;
    }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if (pos_cursor == 0){
        cout << "position() <= size() in eraseBefore()";
        exit(EXIT_FAILURE);  
    }else {
        Node *N = beforeCursor;
        beforeCursor = beforeCursor->prev;
        afterCursor->prev = beforeCursor;
        beforeCursor->next = afterCursor;
        pos_cursor--;
        num_elements--;
        delete N;
    }
}

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so 
// eraseBefore() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1. 
int List::findNext(int x){
    while(pos_cursor != num_elements){
        if (afterCursor->data == x){
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so 
// eraseAfter() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position 0, and 
// returns -1. 
int List::findPrev(int x){
    while(position() != 0){
        if (beforeCursor->data == x){
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    return -1;       
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other 
// occurances. The cursor is not moved with respect to the retained 
// elements, i.e. it lies between the same two retained elements that it 
// did before cleanup() was called.
void List::cleanup(){
    Node *A, *B;
    A = frontDummy->next;

    while (A != backDummy) {
        int count = 0;
        B = A->next;
        while (B != backDummy) {
            if (A->data == B->data) {
                if (B == beforeCursor) {
                    B = B->next;
                    eraseBefore();
                } else if (B == afterCursor) {
                    B = B->next;
                    eraseAfter();
                } else {
                    B->next->prev = B->prev;
                    B->prev->next = B->next;
                    if (count < pos_cursor) {
                        pos_cursor--;
                    }
                    num_elements--;
                    B = B->next;
                }
            } else {
                count++;
                B = B->next;
            }
        }
        A = A->next;
    }
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while (num_elements > 0){
        eraseAfter();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
    List l = List();
    Node* N = frontDummy->next;
    while (N != backDummy){
        l.insertBefore(N->data);
        N = N->next;
    }

    N = L.frontDummy->next;
    while (N != L.backDummy){
        l.insertBefore(N->data);
        N = N->next;
    }
    return l;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
string List::to_string(){
    Node *N;
    string S = "(";
    N=frontDummy->next;
    while(N!=backDummy->prev){
        S += std::to_string(N->data) + ", ";
        N = N->next;
    }
    S += std::to_string(N->data);
    S += ")";
    return S;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;
    eq = (this->num_elements == R.num_elements);
    N = frontDummy;
    M = R.frontDummy;
    while (eq && N!=nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
ostream& operator<<( std::ostream& stream, List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if (this != &L){
        List temp = L;
        swap(frontDummy, temp.frontDummy);
        swap(backDummy, temp.backDummy);
        swap(num_elements, temp.num_elements);
    }
    return *this;
}