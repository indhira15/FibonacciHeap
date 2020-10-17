#include <iostream>
#include "Fibonacci_Heap.h"
using namespace std;

int main() {

    Fibonacci_heap<float>* fh = new Fibonacci_heap<float>();

    vector<NodoF<float>*> v;
    for(int i=3; i<=10; ++i){
        v.push_back(fh->Insert(i));
    }
    v.push_back(fh->Insert(1));
    fh->print();
    fh->DeleteMin();
    fh->print();
    cout << fh->GetMinNodoValue() << endl;
    fh->generatePDF();
    return 0;
}