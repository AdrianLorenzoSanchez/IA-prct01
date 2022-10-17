#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include "node.h"

#pragma once 

auto cmp = [](Node* left, Node* right) { return left->get_cost() > right->get_cost() ;};

class Graph {
 private:
  int nodos_;
  int aristas_;
  int generados_;
  int inspeccionados_;
  std::vector<std::vector<float>> costes_;
  std::string file_;
 public:
  Graph(std::string file);
  void algoritmo();
  Node* BFS(unsigned ini, unsigned final);
  void sucesores(Node* padre, std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)>& frontera);
  bool visitados(Node* nodo, int i);
  void print_result(Node* nodo, int origen);
};