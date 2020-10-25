#define cimg_use_jpeg 1

#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <map>

#include "Fibonacci_Heap.h"
#include "VectorCaracteristico.h"
#include "Arista.h"

using namespace std;

vector<VectorCaracteristico<float>*> vectoresCaracteristicos;

enum distanceMethod {
	EUCLIDEAN,
	MANHATTAN,
	CHEBYSHEV
};

void insertNImagesInDirectory(string base, string directory, int nFiles);
void insertFemaleImages(string directory, int n);
void insertMaleImages(string directory, int n);
void insertMaleStaffImages(string directory, int n);
void generatePDF(list<Arista<float>*>& grafo);
float getDistance(vector<float>& vc1, vector<float>& vc2, distanceMethod method);

int main() {
	Fibonacci_heap<float, Arista<float>> *fh = new Fibonacci_heap<float, Arista<float>>();
	set<VectorCaracteristico<float>*> visitados;

	char cwd[2048];
	getcwd(cwd, sizeof(cwd));
	string userpath = cwd;
	insertFemaleImages(userpath + "/faces94/female", 10);
	insertMaleImages(userpath + "/faces94/male", 10);
	insertMaleStaffImages(userpath + "/faces94/malestaff", 10);
	
	// cada nodo es un vector caracteristico que contiene el path
	// hallar la distancia euclideana entre dos vectores caracteristicos
	int number_of_nodos = vectoresCaracteristicos.size();
	map<VectorCaracteristico<float>*, VectorCaracteristico<float>*> m;


	cout << number_of_nodos<< endl;
	int n = 1;
	for (int i = 0; i < vectoresCaracteristicos.size(); ++i) {
		m[vectoresCaracteristicos[i]] = vectoresCaracteristicos[i];
		auto vc1 = *vectoresCaracteristicos[i]->get();
		for (int j = i+1; j < vectoresCaracteristicos.size(); ++j, ++n) {
			auto vc2 = *vectoresCaracteristicos[j]->get();
			//cout << n << "\n";
			float distance = getDistance(vc1, vc2, EUCLIDEAN); // EUCLIDEAN, MANHATTAN, CHEBYSHEV
			// chequear si esta bien
			Arista<float>* arista = new Arista<float>(vectoresCaracteristicos[i], vectoresCaracteristicos[j], distance);
			fh->Insert(arista->weight, arista);
		}
	}

	// kruscal
	list<Arista<float>*> grafo;
	int size_f = fh->get_size();
	cout << "size of fh: " << size_f << "\n";
	bool enc1, enc2;

	for (int i = 0; (i < size_f) & (grafo.size()<number_of_nodos-1); ++i) {
		auto minimo = fh->DeleteMin();
		auto arista = minimo->getData();
		if(m[arista->nodo1] != m[arista->nodo2]){
			grafo.push_back(arista);

			auto old = m[arista->nodo1];
			auto neww = m[arista->nodo2];
			for(auto &e: m){
				if(e.second == old){
					e.second = neww;
				}
			}
 		}
	}
	int n_personas = 6;
	for(int i=1; i<n_personas; ++i){
		grafo.pop_back();
	}

/*
	for (int i = 0; (i < size_f) & (grafo.size()<number_of_nodos-1); ++i) {
		auto minimo = fh->DeleteMin();
		auto encontrado1 = visitados.find(minimo->data->nodo1);
		auto encontrado2 = visitados.find(minimo->data->nodo2);
		enc1 = (encontrado1 == visitados.end());
		enc2 = (encontrado2 == visitados.end());
		if(enc1 & enc2){
			minimo->data->nodo2->padre = minimo->data->nodo1->padre; 
		}

		if( enc1 || enc2){ // si no esta enc1 o enc2
			if(!enc1){ // si esta enc1
				//minimo->data->nodo1->padre =  (minimo->data->nodo1->padre);
			}
			if(!enc2){ // si esta enc2
				minimo->data->nodo1->padre = (minimo->data->nodo2->padre);
				minimo->data->nodo2->padre = (minimo->data->nodo1->padre);
			}
			visitados.insert(minimo->data->nodo1);
			visitados.insert(minimo->data->nodo2);
			grafo.push_back(minimo->getData());

		}else{
			if(minimo->data->nodo1->padre != minimo->data->nodo2->padre){
				cout << "diferentes"<<endl;
				minimo->data->nodo2->padre = minimo->data->nodo1->padre;
				grafo.push_back(minimo->getData());
			}
		}
	}*/
	cout << "Aristas en el grafo: "<< grafo.size() << endl;
	generatePDF(grafo);
	return 0;
}

void generatePDF(list<Arista<float>*>& grafo) {
     ofstream graph("graph.vz", ios::out);
     bool fileWasOpened = false;

     if (graph.is_open()) {
          fileWasOpened = true;
          graph << "graph {\n";

		for (auto& arista : grafo) {
			//cout << arista->weight << "\n";
			graph << "\"" << arista->nodo1 << "\" [image=\"" << arista->nodo1->imgPath << "\" len=\"" << arista->weight << "\"];\n"; 
			graph << "\"" << arista->nodo2 << "\" [image=\"" << arista->nodo2->imgPath << "\" len=\"" << arista->weight << "\"];\n"; 
			graph << "\"" << arista->nodo1 << "\"" << " -- " << "\"" << arista->nodo2 << "\"" << ";\n";
		}
          graph << "}";
          graph.close();
     }
     if (fileWasOpened) {
          system("sfdp -Tpdf graph.vz -o chebyshev.pdf");
          system("open chebyshev.pdf");
     }
}

float getDistance(vector<float>& vc1, vector<float>& vc2, distanceMethod method) {
	switch (method) {
	case EUCLIDEAN: {
		float acc = 0.0;
		for (int k = 0; k < min(vc1.size(), vc2.size()); ++k) {
			acc += pow(float(vc1[k] - vc2[k]), 2);
		}
		return acc;
		break;
	}
	case MANHATTAN: {
		float acc = 0.0;
		for (int k = 0; k < min(vc1.size(), vc2.size()); ++k) {
			acc += abs(vc1[k] - vc2[k]);
		}
		return acc;
		break;
	}
	case CHEBYSHEV: {
		float acc = FLT_MIN;
		for (int k = 0; k < min(vc1.size(), vc2.size()); ++k) {
			acc = max(acc, vc1[k]-vc2[k]);
		}
		return acc;
		break;
	}
	default:
		break;
	}
}

void insertMaleStaffImages(string directory, int n) {
	insertNImagesInDirectory(directory, "anonym", n);
	insertNImagesInDirectory(directory, "anonym1", n);
	// insertNImagesInDirectory(directory, "anonym2", 20);
	// insertNImagesInDirectory(directory, "cwang", 20);
	// insertNImagesInDirectory(directory, "doraj", 20);
	// insertNImagesInDirectory(directory, "fordj", 20);
	// insertNImagesInDirectory(directory, "hartb", 20);
	// insertNImagesInDirectory(directory, "hensm", 20);
	//insertNImagesInDirectory(directory, "ieorf", n);
	// insertNImagesInDirectory(directory, "lyond", 20);
	//insertNImagesInDirectory(directory, "macci", n);
	// insertNImagesInDirectory(directory, "martin", 20);
	// insertNImagesInDirectory(directory, "michael", 20);
	// insertNImagesInDirectory(directory, "moors", 20);
	// insertNImagesInDirectory(directory, "obeidn", 20);
	// insertNImagesInDirectory(directory, "robin", 20);
	// insertNImagesInDirectory(directory, "sandm", 20);
	// insertNImagesInDirectory(directory, "spacl", 20);
	// insertNImagesInDirectory(directory, "tony", 20);
	// insertNImagesInDirectory(directory, "voudcx", 20);
}

void insertMaleImages(string directory, int n) {
	insertNImagesInDirectory(directory, "9326871", n);
	insertNImagesInDirectory(directory, "9332898", n);
	// insertNImagesInDirectory(directory, "9338446", 20);
/*	insertNImagesInDirectory(directory, "9338454", 20);
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
*/
}

void insertFemaleImages(string directory, int n){
	insertNImagesInDirectory(directory, "9336923", n);
	insertNImagesInDirectory(directory, "9338535", n);
	// insertNImagesInDirectory(directory, "anpage", 20);
	// insertNImagesInDirectory(directory, "asamma", 20);
	// insertNImagesInDirectory(directory, "asewil", 20);
	//insertNImagesInDirectory(directory, "astefa", n);
	// insertNImagesInDirectory(directory, "drbost", 20);
	// insertNImagesInDirectory(directory, "ekavaz", 20);
	// insertNImagesInDirectory(directory, "elduns", 20);
	// // gotone tiene cosas raras
	// insertNImagesInDirectory(directory, "kaknig", 20);
	// insertNImagesInDirectory(directory, "klclar", 20);
	// insertNImagesInDirectory(directory, "ksunth", 20);
	// insertNImagesInDirectory(directory, "lfso", 20);
	//insertNImagesInDirectory(directory, "mbutle", n);
	// insertNImagesInDirectory(directory, "phughe", 20);
	// insertNImagesInDirectory(directory, "sbains", 20);
	// insertNImagesInDirectory(directory, "slbirc", 20);
	// insertNImagesInDirectory(directory, "vstros", 20);
	// insertNImagesInDirectory(directory, "yfhsie", 20);
}

void insertNImagesInDirectory(string base, string directory, int nFiles) {
	for (int i = 1; i <= nFiles; ++i) {
		string path = base + "/" + directory + "/" + directory + "." + to_string(i) + ".jpg";
		VectorCaracteristico<float>* vc = new VectorCaracteristico<float>(path.c_str());
	 	vectoresCaracteristicos.push_back(vc);
	}
}