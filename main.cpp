#include <iostream>
#include "Fibonacci_Heap.h"
using namespace std;

int main() {

    Fibonacci_heap<float>* fh = new Fibonacci_heap<float>();

    vector<NodoF<float>*> v;
    for(int i=1000; i>0; --i){
        fh->Insert(i);
    }

    for(int i=1000; i>0; --i){
        cout << fh->DeleteMin()->key << endl;
    }

  //  fh->generatePDF();
    return 0;
}