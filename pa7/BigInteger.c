//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa7
//-----------------------------------------------------------------------------
#include "BigInteger.h"
#include "List.h"

#define BASE 1000000000
#define POWER 9
#define LIST_ELEMENT long

typedef struct BigIntegerObj{
    List bigInteger;
    int sign;
}BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
    BigInteger bi = malloc(sizeof(BigIntegerObj));
    bi->bigInteger = newList();
    bi->sign = 0;
    return bi;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    if(pN!=NULL && *pN!=NULL){
        freeList(&((*pN)->bigInteger));
        free(*pN);
        *pN=NULL;
    }
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero 
// state.
int sign(BigInteger N){
    if(N->sign == 0){
        return 0;
    }else if(N->sign == -1){
        return -1;
    }else if(N->sign == 1){
        return 1;
    }
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
    if(sign(A) < sign(B)){
        return -1;
    }else if(sign(A) > sign(B)){
        return 1;
    }else if(sign(A) == sign(B)){
        if(sign(A) == 1){
            if(length(A->bigInteger) > length(B->bigInteger)){
                return 1;
            }else if(length(B->bigInteger) > length(A->bigInteger)){
                return -1;
            }else{
                moveFront(B->bigInteger);
                for(moveFront(A->bigInteger);index(A->bigInteger)!=-1;moveNext(A->bigInteger)){
                    if(get(A->bigInteger) > get(B->bigInteger)){
                        return 1;
                    }else if(get(A->bigInteger) < get(B->bigInteger)){
                        return -1;
                    }
                    moveNext(B->bigInteger);
                }
            }
        }else if(sign(A) == -1){
            if(length(B->bigInteger) > length(A->bigInteger)){
                return 1;
            }else if(length(A->bigInteger) > length(B->bigInteger)){
                return -1;
            }else{
                moveFront(B->bigInteger);
                for(moveFront(A->bigInteger);index(A->bigInteger)!=-1;moveNext(A->bigInteger)){
                    if(get(A->bigInteger) > get(B->bigInteger)){
                        return -1;
                    }else if (get(A->bigInteger) < get(B->bigInteger)){
                        return 1;
                    }
                    moveNext(B->bigInteger);
                }
            }
        }
        return 0;
    }
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
    if(compare(A,B)==0){
        return 1;
    }else{
        return 0;
    }
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
    N->sign=0;
    clear(N->bigInteger);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
    N->sign=N->sign*-1;
}

// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
    int length =strlen(s);
    int sign;
    BigInteger number = newBigInteger();
    List list = number->bigInteger;

    if(s[0] == '+'){
        number->sign= 1;
        sign=1;
    }else if (s[0] == '-'){
        number->sign = -1;
        sign=1;
    }else{
        number->sign =1;
        sign=0;
    }
    
    int i=0;
    LIST_ELEMENT sum=0;
    while(i<length-sign){
        for(int j=0;j<POWER;j++){
            if(i==length-sign){
                break;
            }else{
                LIST_ELEMENT output =1;
                while(j!=0){
                    output *=10;
                    j--;
                }
                sum = sum + (s[length-1-i]-'0')*output;
                i++;
            }
        }
        append(list,sum);
        sum=0;
    }
    
    return number;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
    BigInteger copy = newBigInteger();
    freeList(&(copy->bigInteger));
    copy->bigInteger = copyList(N->bigInteger);
    copy->sign = N->sign;
    return copy;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
    makeZero(S);
    if(sign(A) == 1 && sign(B) == -1){
        negate(B);
        subtract(S,A,B);
        negate(B);
        return;
    }

    if(sign(A) == -1 && sign(B) == 1){
        negate(A);
        subtract(S,B,A);
        negate(A);
        return;
    }

    List a = A->bigInteger;
    List b = B->bigInteger;
    List temp = S->bigInteger;

    long sum;
    moveBack(b);
    for(moveBack(a);index(a)!=-1 && index(b)!=-1;movePrev(a)){
        sum=get(a)+get(b);
        prepend(temp, sum);
        movePrev(b);        
    }

    moveFront(temp);
    if(get(temp) == 0){
        S->sign = 0;
    }else if(sign(A) == -1 && sign(B) == -1){
        S->sign = -1;
    }else{
        S->sign = 1;
    } 
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    BigInteger S = newBigInteger();
    add(S,A,B);
    return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
    makeZero(D);
    if(sign(A) == 1 && sign(B) == -1){
        negate(B);
        add(D,A,B);
        negate(B);
        return;
    }

    if(sign(A) == -1 && sign(B) == 1){
        negate(B);
        add(D,A,B);
        negate(B);
        return;
    }

    if(sign(A) == -1 && sign(B) == -1){
        negate(B);
        add(D,A,B);
        negate(B);
        return;
    }
        
    List a = A->bigInteger;
    List b = B->bigInteger;
    List temp = D->bigInteger;

    long sum;
    moveBack(b);
    for(moveBack(a);index(a)!=-1 && index(b)!=-1;movePrev(a)){
        sum=get(a) - get(b);
        prepend(temp, sum);		
        movePrev(b);
    }

    List list = D->bigInteger;
    moveFront(list);
    if(get(list)<0){
        for(moveFront(list);index(list)!=-1;moveNext(list)){
            set(list,-1*get(list));	
        }
    }
    D->sign = compare(A,B);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B
BigInteger diff(BigInteger A, BigInteger B){
    BigInteger D= newBigInteger();
    subtract(D,A,B);
    return D;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting 
// its current state:  P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
    makeZero(P);
    if(sign(A)*sign(B)==0){
        return;
    }
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
    BigInteger a = newBigInteger();
    return a;
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
    if (length(N->bigInteger) == 0 && N->sign == 0){
        fprintf(out, "0");
    }

    if (N->sign == -1) {
        fprintf(out, "-");
    }

    for(moveBack(N->bigInteger);index(N->bigInteger) >= 0;movePrev(N->bigInteger)){
        if (index(N->bigInteger) != length(N->bigInteger) - 1){
            fprintf(out, "%0*ld", POWER, get(N->bigInteger));           
        }else{
            fprintf(out, "%ld", get(N->bigInteger));
        }
    }
}