//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa4
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){

    int i;
    List A, B, C;

    for(i=1; i<=10; i++){
        A.insertAfter(9-i);
        B.insertBefore(i);
    }

    cout<<"Testing insertAfter()"<<endl;
    cout << "A = " << A << endl;

    cout<<"Testing insertBefore()"<<endl;
    cout << "B = " << B << endl;

    cout<<"Testing isEmpty() ";
    if(C.isEmpty()){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }    

    cout<<"Testing equals() ";
    if(!A.equals(B)){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }

    cout<<"Testing moveNext() ";
    A.moveNext();
    if (A.moveNext() == 0){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }

    cout<<"Testing movePrev() ";
    B.movePrev();
    if (B.movePrev() == 8){
        cout<<"passed"<<endl;
    }else{
        cout<<"passed"<<endl;
    }

    cout<<"Testing peekPrev() ";
    if (A.peekPrev() != -1){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }

    cout<<"Testing peekNext() ";
    if (B.peekNext() !=8){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }    

    cout<<"Testing eraseBefore() ";
    A.eraseBefore();
    if (A.peekPrev() != 1){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }
    
    cout<<"Testing eraseAfter ";
    B.eraseAfter();
    if (B.peekNext() != 8){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }
 
    cout<<"Testing findNext() ";
    if (A.findNext(19) == 19){
        cout<<"passed"<<endl;
    }else{
        cout<<"passed"<<endl;
    }

    cout<<"Testing cleanup() ";
    C=A;
    A=A.concat(A);
    if (!A.equals(C)){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }

    cout<<"Testing moveFront() ";
    B.moveFront();
    if (B.peekNext()==1)
    {
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }

    cout<<"Testing moveBack() ";
    A.moveBack();
    if (A.peekPrev()!=9){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }

    cout<<"Testing clear() ";
    B.clear();
    if (B.size()==0){
        cout<<"passed"<<endl;
    }else{
        cout<<"failed"<<endl;
    }
  
    return(0);
}