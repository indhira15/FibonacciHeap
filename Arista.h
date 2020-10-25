#ifndef ARISTA
#define ARISTA

#include "VectorCaracteristico.h"

template <typename A>
class Arista {
public:
     VectorCaracteristico<A>* nodo1;
     VectorCaracteristico<A>* nodo2;
     float weight;

     Arista(VectorCaracteristico<A>* &nodo11, VectorCaracteristico<A>* &nodo22, float weight): nodo1{nodo11}, nodo2{nodo22}, weight{weight} {
     }
};

#endif