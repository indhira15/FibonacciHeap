#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <string>
#include <vector>
#include <list>
#include <limits>
#include <fstream>

using namespace std;

#include "NodoF.h"

template<class T>
class Fibonacci_heap{
private:
	int fh_size;
	list<NodoT*> fb_heap;
	NodoT * nodo_min;

public:
	Fibonacci_heap(): fh_size{0}{}

	NodoT* Insert(T key){
		NodoT *n = new NodoT(key);
		InsertNodo(n);
		if(nodo_min==nullptr || key < nodo_min->key){
			nodo_min = n;
		}
		++fh_size;
		return n;
	}
	void InsertNodo(NodoT *n){
		fb_heap.push_back(n);
	}
	NodoT* GetNewMinNodo(){

	}
	NodoT* GetMinNodo(){

	}
	NodoT* GetMinNodoValue(){

	}
	NodoT* DeleteMin(){
		// retorna el min y lo borra
	}
	void Compactar(){

	}

};



#endif // FIBONACCI_HEAP_H