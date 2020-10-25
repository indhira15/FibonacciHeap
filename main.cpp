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
	int numero_fotos_por_persona = 10;
	insertFemaleImages(userpath + "/faces94/female", numero_fotos_por_persona);
	insertMaleImages(userpath + "/faces94/male", numero_fotos_por_persona);
	insertMaleStaffImages(userpath + "/faces94/malestaff", numero_fotos_por_persona);
	
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
	int n_personas = number_of_nodos/numero_fotos_por_persona;
	for(int i=1; i<n_personas; ++i){
		grafo.pop_back();
	}

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
	// insertNImagesInDirectory(directory, "anonym2", n);
	// insertNImagesInDirectory(directory, "cwang", n);
	// insertNImagesInDirectory(directory, "doraj", n);
	// insertNImagesInDirectory(directory, "fordj", n);
	// insertNImagesInDirectory(directory, "hartb", n);
	// insertNImagesInDirectory(directory, "hensm", n);
	//insertNImagesInDirectory(directory, "ieorf", n);
	// insertNImagesInDirectory(directory, "lyond", n);
	//insertNImagesInDirectory(directory, "macci", n);
	// insertNImagesInDirectory(directory, "martin", n);
	// insertNImagesInDirectory(directory, "michael", n);
	// insertNImagesInDirectory(directory, "moors", n);
	// insertNImagesInDirectory(directory, "obeidn", n);
	// insertNImagesInDirectory(directory, "robin", n);
	// insertNImagesInDirectory(directory, "sandm", n);
	// insertNImagesInDirectory(directory, "spacl", n);
	// insertNImagesInDirectory(directory, "tony", n);
	// insertNImagesInDirectory(directory, "voudcx", n);
}

void insertMaleImages(string directory, int n) {
	insertNImagesInDirectory(directory, "9326871", n);
	insertNImagesInDirectory(directory, "9332898", n);
	// insertNImagesInDirectory(directory, "9338446", n);
/*	insertNImagesInDirectory(directory, "9338454", n);
	insertNImagesInDirectory(directory, "9338462", n);
	insertNImagesInDirectory(directory, "9338489", n);
	insertNImagesInDirectory(directory, "9338497", n);
	insertNImagesInDirectory(directory, "9338519", n);
	insertNImagesInDirectory(directory, "9338527", n);
	insertNImagesInDirectory(directory, "9338543", n);
	insertNImagesInDirectory(directory, "9414649", n);
	insertNImagesInDirectory(directory, "9416994", n);
	insertNImagesInDirectory(directory, "admars", n);
	insertNImagesInDirectory(directory, "ahodki", n);
	insertNImagesInDirectory(directory, "ajflem", n);
	insertNImagesInDirectory(directory, "ajones", n);
	insertNImagesInDirectory(directory, "ajsega", n);
	insertNImagesInDirectory(directory, "akatsi", n);
	insertNImagesInDirectory(directory, "ambarw", n);
	insertNImagesInDirectory(directory, "asheal", n);
	insertNImagesInDirectory(directory, "bplyce", n);
	insertNImagesInDirectory(directory, "cchris", n);
	insertNImagesInDirectory(directory, "ccjame", n);
	insertNImagesInDirectory(directory, "cferdo", n);
	insertNImagesInDirectory(directory, "cgboyc", n);
	insertNImagesInDirectory(directory, "cjcarr", n);
	insertNImagesInDirectory(directory, "cjdenn", n);
	insertNImagesInDirectory(directory, "cjsake", n);
	insertNImagesInDirectory(directory, "cmkirk", n);
	insertNImagesInDirectory(directory, "csanch", n);
	insertNImagesInDirectory(directory, "cshubb", n);
	insertNImagesInDirectory(directory, "cwchoi", n);
	insertNImagesInDirectory(directory, "dagran", n);
	insertNImagesInDirectory(directory, "dakram", n);
	insertNImagesInDirectory(directory, "dcbowe", n);
	insertNImagesInDirectory(directory, "dioann", n);
	insertNImagesInDirectory(directory, "djbirc", n);
	insertNImagesInDirectory(directory, "djhugh", n);
	insertNImagesInDirectory(directory, "djmart", n);
	insertNImagesInDirectory(directory, "dmwest", n);
	insertNImagesInDirectory(directory, "gdhatc", n);
	insertNImagesInDirectory(directory, "ggeorg", n);
	insertNImagesInDirectory(directory, "ggrego", n);
	insertNImagesInDirectory(directory, "gjhero", n);
	insertNImagesInDirectory(directory, "gjnorm", n);
	insertNImagesInDirectory(directory, "gmwate", n);
	insertNImagesInDirectory(directory, "gpapaz", n);
	insertNImagesInDirectory(directory, "gpsmit", n);
	insertNImagesInDirectory(directory, "gsreas", n);
	insertNImagesInDirectory(directory, "irdrew", n);
	insertNImagesInDirectory(directory, "jabins", n);
	insertNImagesInDirectory(directory, "jagrif", n);
	insertNImagesInDirectory(directory, "jcarte", n);
	insertNImagesInDirectory(directory, "jdbenm", n);
	insertNImagesInDirectory(directory, "jgloma", n);
	insertNImagesInDirectory(directory, "jlemon", n);
	insertNImagesInDirectory(directory, "jmedin", n);
	insertNImagesInDirectory(directory, "jrtobi", n);
	insertNImagesInDirectory(directory, "kaatki", n);
	insertNImagesInDirectory(directory, "kdjone", n);
	insertNImagesInDirectory(directory, "khchan", n);
	insertNImagesInDirectory(directory, "khughe", n);
	insertNImagesInDirectory(directory, "kjwith", n);
	insertNImagesInDirectory(directory, "lejnno", n);
	insertNImagesInDirectory(directory, "maasht", n);
	insertNImagesInDirectory(directory, "mberdo", n);
	insertNImagesInDirectory(directory, "mdpove", n);
	insertNImagesInDirectory(directory, "mefait", n);
	insertNImagesInDirectory(directory, "mhwill", n);
	insertNImagesInDirectory(directory, "miaduc", n);
	insertNImagesInDirectory(directory, "mjhans", n);
	insertNImagesInDirectory(directory, "mpetti", n);
	insertNImagesInDirectory(directory, "muthay", n);
	insertNImagesInDirectory(directory, "nahaig", n);
	insertNImagesInDirectory(directory, "namull", n);
	insertNImagesInDirectory(directory, "ndbank", n);
	insertNImagesInDirectory(directory, "ndhagu", n);
	insertNImagesInDirectory(directory, "nhrams", n);
	insertNImagesInDirectory(directory, "njmoor", n);
	insertNImagesInDirectory(directory, "npbour", n);
	insertNImagesInDirectory(directory, "npmitc", n);
	insertNImagesInDirectory(directory, "nrclar", n);
	insertNImagesInDirectory(directory, "nrrbar", n);
	insertNImagesInDirectory(directory, "nwilli", n);
	insertNImagesInDirectory(directory, "ohpark", n);
	insertNImagesInDirectory(directory, "pacole", n);
	insertNImagesInDirectory(directory, "pmives", n);
	insertNImagesInDirectory(directory, "pshurr", n);
	insertNImagesInDirectory(directory, "pspliu", n);
	insertNImagesInDirectory(directory, "ptnich", n);
	insertNImagesInDirectory(directory, "rarobi", n);
	insertNImagesInDirectory(directory, "rgharr", n);
	insertNImagesInDirectory(directory, "rgspru", n);
	insertNImagesInDirectory(directory, "rjlabr", n);
	insertNImagesInDirectory(directory, "rlocke", n);
	insertNImagesInDirectory(directory, "rmcoll", n);
	insertNImagesInDirectory(directory, "rmpugh", n);
	insertNImagesInDirectory(directory, "rnpwil", n);
	insertNImagesInDirectory(directory, "rrowle", n);
	insertNImagesInDirectory(directory, "rsanti", n);
	insertNImagesInDirectory(directory, "saduah", n);
	insertNImagesInDirectory(directory, "saedwa", n);
	insertNImagesInDirectory(directory, "sidick", n);
	insertNImagesInDirectory(directory, "sjbeck", n);
	insertNImagesInDirectory(directory, "skumar", n);
	insertNImagesInDirectory(directory, "smrobb", n);
	insertNImagesInDirectory(directory, "spletc", n);
	insertNImagesInDirectory(directory, "svkriz", n);
	insertNImagesInDirectory(directory, "swewin", n);
	insertNImagesInDirectory(directory, "swsmit", n);
	insertNImagesInDirectory(directory, "vpsavo", n);
	insertNImagesInDirectory(directory, "whussa", n);
	insertNImagesInDirectory(directory, "wjalbe", n);
*/
}

void insertFemaleImages(string directory, int n){
	insertNImagesInDirectory(directory, "9336923", n);
	insertNImagesInDirectory(directory, "9338535", n);
	// insertNImagesInDirectory(directory, "anpage", n);
	// insertNImagesInDirectory(directory, "asamma", n);
	// insertNImagesInDirectory(directory, "asewil", n);
	//insertNImagesInDirectory(directory, "astefa", n);
	// insertNImagesInDirectory(directory, "drbost", n);
	// insertNImagesInDirectory(directory, "ekavaz", n);
	// insertNImagesInDirectory(directory, "elduns", n);
	// // gotone tiene cosas raras
	// insertNImagesInDirectory(directory, "kaknig", n);
	// insertNImagesInDirectory(directory, "klclar", n);
	// insertNImagesInDirectory(directory, "ksunth", n);
	// insertNImagesInDirectory(directory, "lfso", n);
	//insertNImagesInDirectory(directory, "mbutle", n);
	// insertNImagesInDirectory(directory, "phughe", n);
	// insertNImagesInDirectory(directory, "sbains", n);
	// insertNImagesInDirectory(directory, "slbirc", n);
	// insertNImagesInDirectory(directory, "vstros", n);
	// insertNImagesInDirectory(directory, "yfhsie", n);
}

void insertNImagesInDirectory(string base, string directory, int nFiles) {
	for (int i = 1; i <= nFiles; ++i) {
		string path = base + "/" + directory + "/" + directory + "." + to_string(i) + ".jpg";
		VectorCaracteristico<float>* vc = new VectorCaracteristico<float>(path.c_str());
	 	vectoresCaracteristicos.push_back(vc);
	}
}