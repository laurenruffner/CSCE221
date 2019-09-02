/*
 * Binary Tree - source file (functions implementation)
 */

#include "BTree.h"
#include <queue>
#include <math.h>


ostream& operator<<(ostream& out, BTree& tree)
{
  tree.print_level_by_level(out);
  return out;
}

ostream& operator<<(ostream& out, Node& node)
{
  out << "( "
      << node.value
      << ", "
      << node.search_cost
      << " )";
  return out;
}

istream& operator>>(istream& in, BTree& tree)
{
  int x;
  while (!in.eof()) {
    in >> x;
    tree.insert(x);
  }
  return in;
}

void BTree::copy(Node* node){
  if(node){
    insert(node->value);
    copy(node->left);
    copy(node->right);
  }
}

BTree::BTree(const BTree& other){
  root = NULL;
  copy(other.root);
  size = other.size;
}

BTree::BTree(BTree&& other)
{
  root = other.get_root();
  other.set_root(nullptr);
  size = other.size;
}

BTree& BTree::operator=(const BTree& other){
  root = NULL;
  copy(other.root);
  size = other.size;

  return *this;
}

BTree& BTree::operator=(BTree&& other)
{
  if (this != &other) {
    root = other.get_root();
    other.set_root(nullptr);
    size = other.size;
  }
  return *this;
}

float BTree::averageSearch(){

  return averageSearchCost/(float)size;
 
}

Node* BTree::insert(int obj){

  Node* temp = new Node(obj);
  Node* other = root;

  if (root == nullptr){
    root = temp;
    size++;
    return nullptr;
  }

  bool y = true;
  while (y){
    //GREATER
    if (obj > other->value){
      if(other->right== nullptr){
        other->right = temp;
        y = false;
        temp->search_cost++;
        size++;
      }
      else{
        other = other->right;
        temp->search_cost++;
      }
    }
    //LESS
    else if(obj < other->value){
      if(other->left == nullptr){
        other->left = temp;
        y = false;
        temp->search_cost++;
        size++;
      }
      else{
        other = other->left;
        temp->search_cost++;
      }
    }
  }
  return nullptr;
}
Node* search_helper(Node* newNode, int obj){
  if (obj == newNode -> value){
    return newNode;
  }
  else if (obj < newNode -> value){
    newNode = newNode -> left;
    return search_helper (newNode,obj);
  }
  else if (obj > newNode -> value){
    newNode = newNode -> right;
    return search_helper(newNode, obj);
  }
  
}
Node* BTree::search(int obj){
  if (root != NULL){
    return search_helper(get_root(), obj);
  }
  else{
      return nullptr;
  }
}

void BTree::update_search_cost()
{
  //MAKES THE SEARCH COST LINE BY LINE AND OUTPUTS ON A SINGULAR LINE
  
  int test = 0;
  Node* root = new Node;
  root = this-> get_root();
  int size = this-> size;
  int i = 0;
  int j = 0;
  int k =0;
  queue<Node*> queue;
  Node* nothing = nullptr;
  queue.push(root);
  while (!queue.empty()){
    Node* temp = queue.front();
    queue.pop();
    if (temp == nullptr){
      j++;
      queue.push(nothing);
      queue.push(nothing);
    }
    if(temp){
      i++;
      j++;
      
      temp->search_cost = test;
      cout << temp->value <<"[" << temp->search_cost << "] ";
      queue.push(temp->left);
      queue.push(temp->right);
    }
    if (i==size && j==pow(2,k)){
      cout << endl << endl;
      break;
    }
    if (j == (pow(2,k))){
      test++;
      k++;
      j = 0;
    }
  }
}

void BTree::inorder(ostream& out, const Node& tree)
{
  /*
    print your nodes in infix order
    if our tree looks like 
    4
    2 6
    1 3 5 7
    we should get
    1 2 3 4 5 6 7 
  */

 
  if (&tree == NULL){
    out << " ";
    return; 
  }
  else{
    Node* newN = get_root();
    
    inorder(out, *tree.left);
    out << tree.value << "[" << tree.search_cost << "]";
    averageSearchCost += (float) tree.search_cost;
    inorder(out, *tree.right);
  }
}

void BTree::print_level_by_level(ostream& out)
{
  /*
    print the tree using a BFS 

    output should look like this if we dont have a full tree

    4
    2 6
    1 X 5 7
    X X X X X X X 9

    it will be helpfull to do this part iterativly, 
    so do the BFS with the std stack data structure.

    it may also be helpfull to put the entire tree into a vector 
    (probably google this if you dont know how to do it)


  */
  

  Node* root = new Node;
  root = this-> get_root();
  int size = this-> size;
  //cout << "SIZE: " << this-> size << endl;
  int i = 0;
  int j = 0;
  int k =0;
  queue<Node*> queue;
  Node* nothing = nullptr;
  queue.push(root);
  while (!queue.empty()){
    Node* temp = queue.front();
    queue.pop();
    if (temp == nullptr){
      j++;
      out << " X ";
      queue.push(nothing);
      queue.push(nothing);
    }
    if(temp){
      i++;
      j++;
      out << temp->value <<"[" << temp->search_cost << "] ";
      queue.push(temp->left);
      queue.push(temp->right);
    }
    if (i==size && j==pow(2,k)){
      out << endl << endl;
      break;
    }
    if (j == (pow(2,k))){
      out << endl; 
      k++;
      j = 0;
    }
  }
}


