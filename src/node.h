#include <iostream>

#pragma once 

class Node {
 private:
  unsigned id_;
  float cost_;
  Node* padre_;

 public: 
  Node(unsigned id, float cost, Node* padre); //Constructor parametrizado
  Node(); // Constructor por defecto
  unsigned get_id() const;
  float get_cost() const;
  Node* get_padre();
  void set_cost(float cost);
};