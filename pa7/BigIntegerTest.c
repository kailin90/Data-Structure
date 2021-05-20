//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa7
//-----------------------------------------------------------------------------

#include"BigInteger.h"

int main(int argc, char* argv[]){
    char a[] = {"-111122223333"};
	char b[] = {"-111122223333"};
    char c[] = {"-222244446666"};

    BigInteger A = stringToBigInteger(a);
    BigInteger B = stringToBigInteger(b);
    BigInteger C = stringToBigInteger(c);

    BigInteger D = diff(A,B);
    printf("Testing diff(): ");
    if(sign(D) != 0){
        printf("failed\n");
    }else{
        printf("passed\n");
    }

    BigInteger E = sum(A,B);
    printf("Testing sum() on two equal numbers: ");
    if(!equals(C,E)){
        printf("failed\n");
    }else{
        printf("passed\n");
    }

    char f[] = {"222244446666"};   
    char g[] = {"111122223333"};
    BigInteger F = stringToBigInteger(f);
    BigInteger G = stringToBigInteger(g);

    printf("Testing sum() on two positive numbers: ");
    BigInteger temp1 = sum(F,G);
    BigInteger temp2 = sum(G,F);
    if(!equals(temp1,temp2)){
        printf("failed\n");
    }else{
        printf("passed\n");
    }

    printf("Testing sum() on one positive and one negative numbers: ");
    BigInteger temp3 = sum(F,A);
    BigInteger temp4 = sum(A,F);
    if(!equals(temp3,temp4)){
        printf("failed\n");
    }else{
        printf("passed\n");
    }

    printf("Testing sum() on two negative numbers: ");
    BigInteger temp5 = sum(A,C);
    BigInteger temp6 = sum(C,A);
    if(!equals(temp5,temp6)){
        printf("failed\n");
    }else{
        printf("passed\n");
    }    

    printf("Testing negate(): ");
    negate(A);
    if(sign(A)!=1){
        printf("failed\n");
    }else{
        printf("passed\n");
    }

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&temp1);
    freeBigInteger(&temp2);
    freeBigInteger(&temp3);
    freeBigInteger(&temp4);
    freeBigInteger(&temp5);
    freeBigInteger(&temp6);
    return 0;
}