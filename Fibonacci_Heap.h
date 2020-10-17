#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <string>
#include <vector>
#include <list>
#include <limits>
#include <fstream>
#include <cmath>

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
		fb_heap.push_front(n);
	}

	NodoT* GetNewMinNodo(){
		if(fb_heap.size()>0){
			auto aux = *fb_heap.begin();
			for(auto &a:fb_heap){
				if(a->key < aux->key){
					aux = a;
				}
			}
			return aux;
		}
		else
			return nullptr;
	}

	NodoT* GetMinNodo(){
		if(fh_size>0)
			return nodo_min;
		else
			return nullptr;
	}
	T GetMinNodoValue(){
		if(fh_size > 0)
			return nodo_min->key;
		else
			return -1;
	}
	NodoT* DeleteMin(){
		// retorna el min y lo borra
		if(fh_size > 0){
			NodoT* aux = GetMinNodo();
			auto itr_child = aux->children.begin();
			while(itr_child != aux->children.end()){
				// maybe volvelos los hijos blancos
				InsertNodo(*itr_child);
				++itr_child;
			}
			fb_heap.remove(aux);
			nodo_min = GetNewMinNodo();

			Compactar();
			return aux;
		}
		else
			return nullptr;
	}
	// siempre ponerlo en la posicion del primer nodo
	NodoT* Unir_dos_nodos(NodoT* &a, NodoT* &b){
		if(a->key < b->key){
	      a->rank = (max(a->rank, b->rank+1));
	      b->padre = a;
	      a->children.push_front(b);
	      fb_heap.remove(b);
	      return a;
	    }
	    else{
	      b->rank = (max(b->rank, a->rank+1));
	      a->padre = b;
	      b->children.push_front(a);
	      fb_heap.remove(b);
	      a = b;
	      return a;
	    }
	}

	void Compactar(){
		int tm = log2(fh_size) +1;
		vector<NodoT*> v(tm);
		fill(v.begin(), v.end(), nullptr);
		NodoT* nodo_aux;
		for(auto i=fb_heap.begin(); i!=fb_heap.end(); ++i){
			if(v[(*i)->rank] != nullptr){
				int aux2 = (*i)->rank;
				nodo_aux = Unir_dos_nodos((*i),v[(*i)->rank]);
				v[aux2] = nullptr;
				--i;
			}
			else{
				v[(*i)->rank] = (*i);
			}
		}


	}

	void print(){
		for(auto &a:fb_heap){
			cout << a->key << "\t";
		}
		cout << endl;
	}

	void PrintSubTree(NodoT* root) {
	    if (root) { 
	        for(auto it : root->children){
	            PrintSubTree(it);
	            cout << it->key << " ";
	        }
	    }
	}

	void PrintSubTreeSpecial(NodoT* root) {
	    if (root) { 
	        for(auto it : root->children){
	            cout << root->key << " -> ";
	            cout << it->key << ";\n";
	            cout << it->key << " -> ";
	            PrintSubTree(it);
	        }
	    }
	}

	void printSpecial() {

	  for(auto it = fb_heap.begin(); it != fb_heap.end(); it++){
	    cout << (*it)->key << ";\n";
	    // cout << "==Begin Printing sub tree==\n";
	    PrintSubTreeSpecial(*it);
	    // cout << "\n==End Printing sub tree==\n";
	}

	}
	void generatePDF() {
	  fstream file("FibonacciHeap.vz", fstream::out | fstream::trunc);

	  if (file.is_open()) {
	    file << "digraph G\n";
	    file << "{\n";

	    printSpecial(file);

	    file << "}\n";
	    file.close();
	    system("dot -Tpdf FibonacciHeap.vz -o FibonacciHeap.pdf");
	  }
	}

	void PrintSubTreeSpecial(fstream& file, NodoT* root) {
	    if (root) { 
	      file << "\"" << root <<"\" [\n";
	      file << "\tlabel = "<< root->key <<"\n]\n";
	        for(auto it : root->children){
	            if (it->key != root->key) {
	              file << "\"" << root <<"\" -> ";
	              file << "\"" << it << "\";\n";
	              /*
	              file << root->m_key << " -> ";
	              file << it->m_key << ";\n";*/
	              PrintSubTreeSpecial(file, it);
	            }
	        }
	    }
	}

	void printSpecial(fstream& file) {
	  for(auto it = fb_heap.begin(); it != fb_heap.end(); it++) {
	    file << "\"" << (*it) <<"\" [\n";
	    file << "\tlabel = "<< (*it)->key <<"\n]\n";
	    PrintSubTreeSpecial(file, *it);
	  }
	}

	int get_size() {
		return fh_size;
	}
};



#endif // FIBONACCI_HEAP_H