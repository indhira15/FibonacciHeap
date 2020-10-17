#ifndef ARISTA
#define ARISTA

#include "VectorCaracteristico.h"

template <typename T>
struct Arista {
     VectorCaracteristico<T>* nodo1;
     VectorCaracteristico<T>* nodo2;
     float weight;

public:
     Arista(VectorCaracteristico<T>* nodo1, VectorCaracteristico<T>* nodo2, float weight): nodo1{nodo1}, nodo2{nodo2}, weight{weight} {}
};

#endif