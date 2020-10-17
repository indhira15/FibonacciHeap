#ifndef NODOB_F
#define NODOB_F

#include <string>
#include <list>

#include "Arista.h"

#define NodoT NodoF<T> 

using namespace std;

enum Color{
	Blanco = 0,
	Negro = 1
};

template<class T>
class NodoF{
public:
	int rank;
	T key;
	Color estado;
	list<NodoT*> children;
	NodoT *padre;
	Arista<T>* arista;

	NodoF(T value){
		rank = 0;
		key = value;
	}

};

#endif // NODOF_H