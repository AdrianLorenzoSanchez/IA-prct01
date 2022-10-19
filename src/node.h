#include <iostream>

#pragma once 

class Node {
 private:
  unsigned id_; // Identificador
  float cost_;  // Coste del camino haste el nodo
  Node* padre_; // Puntero al padre del nodo

 public: 
  Node(unsigned id, float cost, Node* padre); //Constructor parametrizado
  Node(); // Constructor por defecto
  unsigned get_id() const;
  float get_cost() const;
  Node* get_padre();
  void set_cost(float cost);

};
