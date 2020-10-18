#ifndef ARISTA
#define ARISTA

#include "VectorCaracteristico.h"

template <typename T>
class Arista {
public:
     VectorCaracteristico<T>* nodo1;
     VectorCaracteristico<T>* nodo2;
     float weight;

     Arista(VectorCaracteristico<T>* nodo1, VectorCaracteristico<T>* nodo2, float weight): nodo1{nodo1}, nodo2{nodo2}, weight{weight} {}
};

#endif