#ifndef NODOB_F
#define NODOB_F

#include <string>
#include <list>

#include "Arista.h"

#define NodoT NodoF<T,D>

using namespace std;

enum Color{
	Blanco = 0,
	Negro = 1
};

template<class T, class D>
class NodoF{
public:
	int rank;
	T key;
	Color estado;
	list<NodoT*> children;
	NodoT *padre;
	//Arista<T>* arista;
	D *data;

	NodoF(T value){
		rank = 0;
		key = value;
	}

	NodoF(T value, D *dat){
		rank = 0;
		key = value;
		data = dat;
	}

	D* getData(){
		return data;
	}

};

#endif // NODOF_H