#ifndef ARISTA
#define ARISTA

#include "VectorCaracteristico.h"

template <typename A>
class Arista {
public:
     VectorCaracteristico<A>* nodo1;
     VectorCaracteristico<A>* nodo2;
     float weight;

     Arista(VectorCaracteristico<A>* nodo1, VectorCaracteristico<A>* nodo2, float weight): nodo1{nodo1}, nodo2{nodo2}, weight{weight} {}
};

#endif