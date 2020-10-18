#define cimg_use_jpeg 1
//#define cimg_use_png 1

#include <iostream>
#include <vector>
#include <array>
#include <set>

#include "Fibonacci_Heap.h"
#include "VectorCaracteristico.h"
#include "Arista.h"

using namespace std;

vector<VectorCaracteristico<float>*> vectoresCaracteristicos;

void insertNImagesInDirectory(string base, string directory, int nFiles) {
	for (int i = 1; i <= nFiles; ++i) {
		string path = base + "/" + directory + "/" + directory + "." + to_string(i) + ".jpg";
		// cout << path << "\n";
		VectorCaracteristico<float>* vc = new VectorCaracteristico<float>(path.c_str());
	 	vectoresCaracteristicos.push_back(vc);
	}
}

void insertFemaleImages(string directory) {
	insertNImagesInDirectory(directory, "9336923", 20);
	insertNImagesInDirectory(directory, "9338535", 20);
	insertNImagesInDirectory(directory, "anpage", 20);
	insertNImagesInDirectory(directory, "asamma", 20);
	insertNImagesInDirectory(directory, "asewil", 20);
	insertNImagesInDirectory(directory, "astefa", 20);
	insertNImagesInDirectory(directory, "drbost", 20);
	insertNImagesInDirectory(directory, "ekavaz", 20);
	insertNImagesInDirectory(directory, "elduns", 20);
	// gotone tiene cosas raras
	insertNImagesInDirectory(directory, "kaknig", 20);
	insertNImagesInDirectory(directory, "klclar", 20);
	insertNImagesInDirectory(directory, "ksunth", 20);
	insertNImagesInDirectory(directory, "lfso", 20);
	insertNImagesInDirectory(directory, "mbutle", 20);
	insertNImagesInDirectory(directory, "phughe", 20);
	insertNImagesInDirectory(directory, "sbains", 20);
	insertNImagesInDirectory(directory, "slbirc", 20);
	insertNImagesInDirectory(directory, "vstros", 20);
	insertNImagesInDirectory(directory, "yfhsie", 20);
}

void insertMaleImages(string directory) {
	insertNImagesInDirectory(directory, "9326871", 20);
	insertNImagesInDirectory(directory, "9332898", 20);
	insertNImagesInDirectory(directory, "9338446", 20);
	insertNImagesInDirectory(directory, "9338454", 20);
	insertNImagesInDirectory(directory, "9338462", 20);
	insertNImagesInDirectory(directory, "9338489", 20);
	insertNImagesInDirectory(directory, "9338497", 20);
	insertNImagesInDirectory(directory, "9338519", 20);
	insertNImagesInDirectory(directory, "9338527", 20);
	insertNImagesInDirectory(directory, "9338543", 20);
	insertNImagesInDirectory(directory, "9414649", 20);
	insertNImagesInDirectory(directory, "9416994", 20);
	insertNImagesInDirectory(directory, "admars", 20);
	insertNImagesInDirectory(directory, "ahodki", 20);
	insertNImagesInDirectory(directory, "ajflem", 20);
	insertNImagesInDirectory(directory, "ajones", 20);
	insertNImagesInDirectory(directory, "ajsega", 20);
	insertNImagesInDirectory(directory, "akatsi", 20);
	insertNImagesInDirectory(directory, "ambarw", 20);
	insertNImagesInDirectory(directory, "asheal", 20);
	insertNImagesInDirectory(directory, "bplyce", 20);
	insertNImagesInDirectory(directory, "cchris", 20);
	insertNImagesInDirectory(directory, "ccjame", 20);
	insertNImagesInDirectory(directory, "cferdo", 20);
	insertNImagesInDirectory(directory, "cgboyc", 20);
	insertNImagesInDirectory(directory, "cjcarr", 20);
	insertNImagesInDirectory(directory, "cjdenn", 20);
	insertNImagesInDirectory(directory, "cjsake", 20);
	insertNImagesInDirectory(directory, "cmkirk", 20);
	insertNImagesInDirectory(directory, "csanch", 20);
	insertNImagesInDirectory(directory, "cshubb", 20);
	insertNImagesInDirectory(directory, "cwchoi", 20);
	insertNImagesInDirectory(directory, "dagran", 20);
	insertNImagesInDirectory(directory, "dakram", 20);
	insertNImagesInDirectory(directory, "dcbowe", 20);
	insertNImagesInDirectory(directory, "dioann", 20);
	insertNImagesInDirectory(directory, "djbirc", 20);
	insertNImagesInDirectory(directory, "djhugh", 20);
	insertNImagesInDirectory(directory, "djmart", 20);
	insertNImagesInDirectory(directory, "dmwest", 20);
	insertNImagesInDirectory(directory, "gdhatc", 20);
	insertNImagesInDirectory(directory, "ggeorg", 20);
	insertNImagesInDirectory(directory, "ggrego", 20);
	insertNImagesInDirectory(directory, "gjhero", 20);
	insertNImagesInDirectory(directory, "gjnorm", 20);
	insertNImagesInDirectory(directory, "gmwate", 20);
	insertNImagesInDirectory(directory, "gpapaz", 20);
	insertNImagesInDirectory(directory, "gpsmit", 20);
	insertNImagesInDirectory(directory, "gsreas", 20);
	insertNImagesInDirectory(directory, "irdrew", 20);
	insertNImagesInDirectory(directory, "jabins", 20);
	insertNImagesInDirectory(directory, "jagrif", 20);
	insertNImagesInDirectory(directory, "jcarte", 20);
	insertNImagesInDirectory(directory, "jdbenm", 20);
	insertNImagesInDirectory(directory, "jgloma", 20);
	insertNImagesInDirectory(directory, "jlemon", 20);
	insertNImagesInDirectory(directory, "jmedin", 20);
	insertNImagesInDirectory(directory, "jrtobi", 20);
	insertNImagesInDirectory(directory, "kaatki", 20);
	insertNImagesInDirectory(directory, "kdjone", 20);
	insertNImagesInDirectory(directory, "khchan", 20);
	insertNImagesInDirectory(directory, "khughe", 20);
	insertNImagesInDirectory(directory, "kjwith", 20);
	insertNImagesInDirectory(directory, "lejnno", 20);
	insertNImagesInDirectory(directory, "maasht", 20);
	insertNImagesInDirectory(directory, "mberdo", 20);
	insertNImagesInDirectory(directory, "mdpove", 20);
	insertNImagesInDirectory(directory, "mefait", 20);
	insertNImagesInDirectory(directory, "mhwill", 20);
	insertNImagesInDirectory(directory, "miaduc", 20);
	insertNImagesInDirectory(directory, "mjhans", 20);
	insertNImagesInDirectory(directory, "mpetti", 20);
	insertNImagesInDirectory(directory, "muthay", 20);
	insertNImagesInDirectory(directory, "nahaig", 20);
	insertNImagesInDirectory(directory, "namull", 20);
	insertNImagesInDirectory(directory, "ndbank", 20);
	insertNImagesInDirectory(directory, "ndhagu", 20);
	insertNImagesInDirectory(directory, "nhrams", 20);
	insertNImagesInDirectory(directory, "njmoor", 20);
	insertNImagesInDirectory(directory, "npbour", 20);
	insertNImagesInDirectory(directory, "npmitc", 20);
	insertNImagesInDirectory(directory, "nrclar", 20);
	insertNImagesInDirectory(directory, "nrrbar", 20);
	insertNImagesInDirectory(directory, "nwilli", 20);
	insertNImagesInDirectory(directory, "ohpark", 20);
	insertNImagesInDirectory(directory, "pacole", 20);
	insertNImagesInDirectory(directory, "pmives", 20);
	insertNImagesInDirectory(directory, "pshurr", 20);
	insertNImagesInDirectory(directory, "pspliu", 20);
	insertNImagesInDirectory(directory, "ptnich", 20);
	insertNImagesInDirectory(directory, "rarobi", 20);
	insertNImagesInDirectory(directory, "rgharr", 20);
	insertNImagesInDirectory(directory, "rgspru", 20);
	insertNImagesInDirectory(directory, "rjlabr", 20);
	insertNImagesInDirectory(directory, "rlocke", 20);
	insertNImagesInDirectory(directory, "rmcoll", 20);
	insertNImagesInDirectory(directory, "rmpugh", 20);
	insertNImagesInDirectory(directory, "rnpwil", 20);
	insertNImagesInDirectory(directory, "rrowle", 20);
	insertNImagesInDirectory(directory, "rsanti", 20);
	insertNImagesInDirectory(directory, "saduah", 20);
	insertNImagesInDirectory(directory, "saedwa", 20);
	insertNImagesInDirectory(directory, "sidick", 20);
	insertNImagesInDirectory(directory, "sjbeck", 20);
	insertNImagesInDirectory(directory, "skumar", 20);
	insertNImagesInDirectory(directory, "smrobb", 20);
	insertNImagesInDirectory(directory, "spletc", 20);
	insertNImagesInDirectory(directory, "svkriz", 20);
	insertNImagesInDirectory(directory, "swewin", 20);
	insertNImagesInDirectory(directory, "swsmit", 20);
	insertNImagesInDirectory(directory, "vpsavo", 20);
	insertNImagesInDirectory(directory, "whussa", 20);
	insertNImagesInDirectory(directory, "wjalbe", 20);
}

void insertMaleStaffImages(string directory) {
	insertNImagesInDirectory(directory, "anonym", 20);
	insertNImagesInDirectory(directory, "anonym1", 20);
	insertNImagesInDirectory(directory, "anonym2", 20);
	insertNImagesInDirectory(directory, "cwang", 20);
	insertNImagesInDirectory(directory, "doraj", 20);
	insertNImagesInDirectory(directory, "fordj", 20);
	insertNImagesInDirectory(directory, "hartb", 20);
	insertNImagesInDirectory(directory, "hensm", 20);
	insertNImagesInDirectory(directory, "ieorf", 20);
	insertNImagesInDirectory(directory, "lyond", 20);
	insertNImagesInDirectory(directory, "macci", 20);
	insertNImagesInDirectory(directory, "martin", 20);
	insertNImagesInDirectory(directory, "michael", 20);
	insertNImagesInDirectory(directory, "moors", 20);
	insertNImagesInDirectory(directory, "obeidn", 20);
	insertNImagesInDirectory(directory, "robin", 20);
	insertNImagesInDirectory(directory, "sandm", 20);
	insertNImagesInDirectory(directory, "spacl", 20);
	insertNImagesInDirectory(directory, "tony", 20);
	insertNImagesInDirectory(directory, "voudcx", 20);
}

int main() {

	system("clear");

	Fibonacci_heap<float>* fh = new Fibonacci_heap<float>();
	set<VectorCaracteristico<float>> visitados;

	// vector<NodoF<float>*> v;
	// for(int i=1000; i>0; --i){
	// 	fh->Insert(i);
	// }

	// for(int i=1000; i>0; --i){
	// 	cout << fh->DeleteMin()->key << endl;
	// }

	insertFemaleImages("/Users/gabrielspranger/Desktop/EDA/FibonacciHeap/faces94/female");
	insertMaleImages("/Users/gabrielspranger/Desktop/EDA/FibonacciHeap/faces94/male");
	insertMaleStaffImages("/Users/gabrielspranger/Desktop/EDA/FibonacciHeap/faces94/malestaff");
	
	// cada nodo es un vector caracteristico y el nombre de la imagen

	// hallar la distancia euclideana entre dos vectores caracteristicos
		// ver imagen del Notion

	cout << vectoresCaracteristicos.size() << endl;

	int n = 1;
	for (int i = 0; i < vectoresCaracteristicos.size(); ++i) {
		auto vc1 = *vectoresCaracteristicos[i]->get();
		for (int j = i+1; j < vectoresCaracteristicos.size(); ++j, ++n) {
			auto vc2 = *vectoresCaracteristicos[j]->get();
			cout << n << "\n";
			float acc = 0.0;
			for (int k = 0; k < vc1.size(); ++k) {
				acc += pow(float(vc1[k] - vc2[k]), 2);
			}
			// chequear si esta bien
			Arista<float>* arista = new Arista<float>(vectoresCaracteristicos[i], vectoresCaracteristicos[j], acc);
			fh->insertArista(arista);
		}
	}

	for (int i = 0; i < fh->get_size(); ++i) {
		auto minimo = fh->DeleteMin();
		auto encontrado1 = visitados.find(minimo->arista->nodo1);
		auto encontrado2 = visitados.find(minimo->arista->nodo2);
		// kruskall
		if (encontrado1 != visitados.end() || encontrado2 != visitados.end()) {
			visitados.insert(minimo->arista->nodo1);
			visitados.insert(minimo->arista->nodo2);
		}
	}

	return 0;
}
