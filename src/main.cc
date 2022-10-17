#include <iostream>
#include "graph.h"

using namespace std;

int main() {
  
  bool salir = false;
  string file;
  
  while (!salir) {
    cout << "Especifica el fichero de entrada: "; cin >> file; 
    if (file == "0")
      salir = true;
    else {
       
      Graph grafo(file);
      grafo.algoritmo();

    }
  }
}


