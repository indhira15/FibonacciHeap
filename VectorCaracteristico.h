#ifndef VECTORCARACTERISTICO
#define VECTORCARACTERISTICO

#define cimg_use_jpeg 1

#include "CImg.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cimg_library;

template <typename T>
class VectorCaracteristico {
     vector<T>* vc;
     const char* imgPath;

public:
     VectorCaracteristico(const char* imgPath): imgPath{imgPath} {
          CImg<T> A(imgPath);
          CImg<T> B = A.haar(false, 1);
          CImg<T> C = B.crop(0, 0, 89, 99);
          this->vc = vectorizar(C);
     }

     void printName() {
          cout << imgPath << "\n";
     }

     vector<T>* get() {
          return vc;
     }

private:
     vector<T>* vectorizar(CImg<T>& img) {
          vector<T>* r = new vector<T>();
          cimg_forXY (img, x, y) {
               r->push_back(		(
                                   img(x, y, 0) + 
                                   img(x, y, 1) + 
                                   img(x, y, 2) 
                                   )/3.0f
                              );
          }
          return r;
     }
};


#endif