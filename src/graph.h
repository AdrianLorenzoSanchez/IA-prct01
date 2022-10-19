#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include "node.h"

#pragma once 

// Comparador para ordenar los nodos dentro de la cola en función del coste
auto cmp = [](Node* left, Node* right) { return left->get_cost() > right->get_cost() ;}; 

class Graph {
 private:
  int nodos_;                               // Número de nodos
  int aristas_;                             // Número de aristas
  int generados_;                           // Número de nodos generados
  int inspeccionados_;                      // Número de nodos inspeccionados
  std::vector<std::vector<float>> costes_;  // Matriz que contiene los costes de cada nodo
  std::string file_;                        // Nombre del fichero de entrada
 public:
  Graph(std::string file);
  void algoritmo();
  Node* costo_uniforme(unsigned ini, unsigned final);
  void sucesores(Node* padre, std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)>& frontera);
  bool visitados(Node* nodo, int i);
  void print_result(Node* nodo, int origen); // Imprime en el fichero salida.csv la tabla con los resultados
};