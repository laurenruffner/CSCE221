#include "BTree.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <math.h>

using namespace std;


BTree read_file(string file_name){
  BTree tree;
  ifstream data;
  data.open(file_name);
  data >> tree;
  data.close();
  return tree;
}

void output(BTree tree, string file_name){

  string file_name2;
  cout<< "Name of OUT File?" << endl;
  cin >> file_name2;
  ofstream myfile;
  myfile.open(file_name2, ios::app);
  
  //name of file
  myfile << file_name << endl;
  myfile << "INORDER: " << endl;
  tree.inorder(myfile, *tree.get_root());
  myfile << endl;
  cout << "SIZE: " << tree.get_size() << endl;
  cout << "AVERAGE SEARCH COST: " << tree.averageSearch() << endl;
  if (tree.get_size() <= (pow(2,4))){
    cout << "INORDER: " << endl;
    tree.inorder(cout, *tree.get_root());
    cout << endl;
    cout << "LINE-BY-LINE: " << endl;
    cout << tree;
    myfile << "LINE-BY-LINE: " << endl;
    myfile << tree;
    myfile << endl;
  }
}

int main(){
  int t = 1;
  while (t == 1){
    BTree tree1;
    string file_name;
    cout << "Name of IN File?" <<  endl;
    cin >> file_name;

    tree1 = read_file(file_name);
    output(tree1, file_name);

    int x;
    cout << "Do you want to test constructors and other functions (inorder will be outputted to screen for each)? 1 for yes, 0 for no." << endl;
    cin >> x;

    //PROVES CONSTRUCTORS AND OPERATORS WORK FOR ONLY THE FIRST ONE
    if (x == 1){

      BTree tree2(move (tree1));
      cout << "MOVE CONSTRUCTOR (INORDER): " << endl;
      tree2.inorder(cout, *tree2.get_root());
      cout << endl;

      BTree tree4;
      tree4 = move(tree2);
      cout << "MOVE OPERATOR (INORDER): " << endl;
      tree4.inorder(cout, *tree4.get_root());
      cout << endl;

      BTree tree3;
      tree3 = tree4;
      cout << "COPY OPERATOR (INORDER): " << endl;
      tree3.inorder(cout, *tree3.get_root());
      cout << endl;

      BTree tree5(tree4);
      cout << "COPY CONSTRUCTOR (INORDER): " << endl;
      tree5.inorder(cout, *tree5.get_root());
      cout << endl;

      cout << "UPDATE SEARCH COST: ";
      tree3.update_search_cost();

      cout << "SEARCH FOR 1: " << endl;
      cout << tree3.search(1)->value << endl;
    }
    else{
      cout << "SEARCH FOR 1: " << endl;
      cout << tree1.search(1)->value << endl;
    }

    cout << "Upload new file? 1 for yes 0 for no." << endl;
    cin >> t;
  } 
 return 0;
}