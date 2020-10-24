#ifndef NODOB_F
#define NODOB_F

#include <string>
#include <list>

#include "Arista.h"

#define NodoT NodoF<T,D>

using namespace std;

template<class T, class D>
class NodoF{
public:
	int rank;
	T key;
	list<NodoT*> children;
	NodoT *padre;
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