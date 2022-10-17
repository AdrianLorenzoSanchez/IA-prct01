#include "node.h"

Node::Node(unsigned id, float cost, Node* padre) {
  id_ = id;  
  cost_ = cost;
  padre_ = padre;
}

Node::Node() {
  id_ = 0;
  cost_ = 0;
  padre_ = NULL;
}
unsigned Node::get_id() const{
  return id_;
}

float Node::get_cost() const{
  return cost_;
}

Node* Node::get_padre() {
  return padre_;
}

void Node::set_cost(float cost) {
  cost_ = cost;
}



