#include <iostream>
#include "graph.h"

using namespace std;

int main() {

  string file;
  
  bool salir = false;
  while (!salir) {
    cout << "Especifica el fichero de entrada (0 salir): "; cin >> file; 
    if (file == "0")
      salir = true;
    else {
      Graph grafo(file);
      grafo.algoritmo();
    }
  }
}


