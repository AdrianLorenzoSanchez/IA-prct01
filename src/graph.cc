#include<stdlib.h>
#include<time.h>

#include "graph.h"
using namespace std;

Graph::Graph(std::string file) {

  aristas_ = 0;
  file_ = file;

  std::ifstream fin;
  file = "../ejemplos/"+file;
  fin.open(file);
  fin >> nodos_;  

  // Creamos la matriz de costes con tantas filas y columnas como el numero de nodos leído en el fichero
  costes_.resize(nodos_);
  for (int i = 0; i < costes_.size(); i++) 
    costes_[i].resize(nodos_);

  // Asignamos los costes de cada posible arista
  float coste;
  for (int i = 0; i < nodos_-1; i++) {
    for (int j = i+1; j < nodos_; j++) {
      fin >> coste;
      costes_[i][j] = coste; 
      costes_[j][i] = coste; 
      if (coste > 0) 
        aristas_++;
    }  
  }
  
}

void Graph::algoritmo() {
  
  int origen, destino;  // Identificador del nodo origen y destino
  bool salir = false; 

  // Mientras salir sea false se ejecutará el bucle 
  while (!salir) {
    cout << "Elija el nodo origen y destino [1-" << nodos_ << "] : "; cin >> origen >> destino;
    if ( origen <= 0 || origen > nodos_ || destino <= 0 || destino > nodos_ )
      cout << "Los nodos introducidos no son válidos." << endl;
    else {

      Node* nodo = costo_uniforme(origen-1, destino-1); // Se resta 1 ya que en c++ la primera posición de un vector es la 0.

      // Si el coste del nodo devuelto por el algoritmo es -1 no encontró solución
      if (nodo->get_cost() == -1) 
        cout << "No existe un camino." << endl;
      else 
        print_result(nodo, origen);
    }

    // Condicional para salir del bucle si se quire añadir un nuevo fichero de entrada
    char opcion;
    cout << "¿Nuevo fichero de entrada?(Y/N):"; cin >> opcion;
    if (opcion == 'Y')
      salir = true;
  }
}

Node* Graph::costo_uniforme(unsigned ini, unsigned final) {
  // Inicializamos el numero de nodos generados y inspeccionados a 0
  generados_ = 0;
  inspeccionados_ = 0;

  // Creamos una cola con prioridad para almacenar los nodos que están en la frontera ordenados por el menor coste de camino
  // Para compararlos entre sí utiliza la función cmp definifa en graph.h
  priority_queue<Node*, vector<Node*>, decltype(cmp)> frontera(cmp);

  // Creamos el nodo raíz del árbol, lo metemos en la cola e incrementamos el contador de generados
  Node* raiz = new Node(ini, 0, NULL);
  frontera.push(raiz);
  generados_++;
  
  Node* nodo = new Node();

  // Modificación
  vector<Node*> elegir;
  elegir.resize(2);
  int random;
  srand(time(NULL));

  while(!frontera.empty()) {
    if(frontera.size() == 1) {
    	nodo = frontera.top();
	    frontera.pop();
	    inspeccionados_++;
    }
    else {
	    elegir[0] = frontera.top(); frontera.pop();
	    elegir[1] = frontera.top(); frontera.pop();

	    random = rand()%2;
	    nodo = elegir[random];

	    if (random == 0)
	      frontera.push(elegir[1]);
	    else
	      frontera.push(elegir[0]);

	    inspeccionados_++;
    }		    
    
    if (nodo->get_id() == final) 
      return nodo;
      
    sucesores(nodo, frontera);
  }
  nodo->set_cost(-1);
  return nodo;
}


void Graph::sucesores(Node* padre, priority_queue<Node*, vector<Node*>, decltype(cmp)>& frontera) {

  // Recorre en la matriz de costes la fila del nodo padre
  // Si encuentra un sucesor comprueba que no se haya repetido en el camino que está explorando y lo mete en la cola
  for (int i = 0; i < costes_[padre->get_id()].size(); i++) {
      if (costes_[padre->get_id()][i] > 0 && !visitados(padre, i)) {
        Node* nodo = new Node(i, costes_[padre->get_id()][i]+padre->get_cost(), padre);
        frontera.push(nodo);
        generados_++; // Incrementamos el contador de nodos generados;
    }
  }

}

bool Graph::visitados(Node* nodo, int i) {

  // Si es el nodo raíz no se ha repetido en el camino
  if (nodo->get_padre() == NULL)
    return false;

  // Comprueba los demás nodos del camino
  while(nodo->get_padre() != NULL) {
    if(nodo->get_id() == i) 
      return true;
    nodo = nodo->get_padre();
  }
  // Comprueba el nodo raíz
  if (nodo->get_id() == i) 
    return true;

  return false;

}

void Graph::print_result(Node* nodo, int origen) {

  ofstream fout("../salida.csv", ios::app);
  float coste_camino = nodo->get_cost();
  fout << file_ << ";" << nodos_ << ";" << aristas_ << ";" << origen << ";" << nodo->get_id()+1 << ";";

  // Creo un vector para poder imprimir el camino de izquierda a derecha
  vector<Node*> imprimir;
  while (nodo->get_padre() != NULL) {
    imprimir.push_back(nodo);
    nodo = nodo->get_padre();
  }
  imprimir.push_back(nodo);

  // Imprimimos el vector empezando por el final para que salga en orden 
  for (int i = imprimir.size()-1; i > 0; i--)
    fout << imprimir[i]->get_id()+1 << "->";

  fout << imprimir[0]->get_id()+1 << ";" << coste_camino << ";" << generados_ << ";" << inspeccionados_ << endl;
}
