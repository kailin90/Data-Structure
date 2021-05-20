//-----------------------------------------------------------------------------
// Kailin Zhuo
// kzhuo
// pa4
//-----------------------------------------------------------------------------

#include "List.h"

using namespace std;

void shuffle(List &D);

int main(int argc, char *argv[]) {

  int num = 0;
  int count = 0;
  int n = stoi(argv[1]);

  List deck,shuffledDeck;
           
  cout << "deck size " << "\t" <<"shuffle count" << "\n";
  cout << "------------------------------" << "\n";

  for (int i = 0; i < n; i++) {
    num = 0;
    count = i+1;
    for (int j = 0; j < count; j++) {
      shuffledDeck.insertBefore(j);
      deck.insertBefore(j);
    }

    shuffle(shuffledDeck);
    num++;
    while (deck.equals(shuffledDeck) != true) {
      shuffle(shuffledDeck);
      num++;
    }
    
    cout << i+1 << " \t\t" << num << "\n";

    shuffledDeck.clear();
    deck.clear();
  }
  
  return 0;
}

void shuffle(List &D) {
   List A,B,C;
   int x = D.size() / 2;
   int y = D.size() - x;
   int size = D.size();
   D.moveFront();
   
   for (int i = 0; i < x; i++){
      A.insertBefore(D.peekNext());
      D.moveNext();
   }

   for (int i = 0; i < y; i++){
      B.insertBefore(D.peekNext());
      D.moveNext();
   }

  D.clear();
  A.moveFront();
  B.moveFront();

  while(C.size() != size){
    if (B.position() != B.size()){
      C.insertBefore(B.peekNext());   
      B.moveNext();
    }

    if (A.position() != A.size()){
      C.insertBefore(A.peekNext());
      A.moveNext();
    }
}

  D = C;
}