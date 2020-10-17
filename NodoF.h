#ifndef NODOB_F
#define NODOB_F

#include <string>
#include <list>

#define NodoT NodoF<T>

template<class T>
class NodoF{
public:
	int rank;
	T key;
	list<NodoT*> children;
	NodoT *padre;

	NodoF(T value){
		rank = 0;
		key = value;
	}

};

#endif // NODOF_H