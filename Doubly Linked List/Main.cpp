#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;
int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DoublyLinkedList dll;
  cout << "list: " << dll << endl << endl;
  
  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertLast(i);
  }
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertFirst(i);
  }
  cout << "list: " << dll << endl << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl<< endl;


  //TESTING THE MOVE CONSTRUCTOR AND ASSIGNMENT

  DoublyLinkedList dll6;
  for (int i=10;i<=100;i+=10) {
    dll6.insertLast(i);
  }
  cout << "list dll6: " << dll6 << endl;


  //MOVE CONSTRUCTOR TESTED
  DoublyLinkedList dll7(move(dll6));
  cout << "move constructor list dll7: " << dll7 << endl;
  cout << "moved constructor list dll6: " << dll6 << endl;


  dll6 = move(dll7);
  cout << "move assignmnet list dll6: " << dll6 << endl;
  cout << "moved assignmnet list dll7: " << dll7 << endl << endl;


  //TESTING INSERTS
  dll6.insertBefore(*dll6.getFirst(), 5);
  cout << "insert before list dll6: " << dll6 << endl;
  dll6.insertAfter(*dll6.getFirst(), 55);
  cout << "insert after list dll6: " << dll6 << endl << endl;


  
  DoublyLinkedList dll8;
  for (int i=10;i<=100;i+=10) {
    dll8.insertLast(i);
  }
  cout << "list dll8: " << dll8 << endl;
  //TESTING REMOVES
  cout << dll6.removeBefore(*dll8.getFirst()->next) <<  endl;
  cout << "remove before list dll8: " << dll8 << endl;

  // << dll8.first() << endl;
  cout << dll6.removeAfter(*dll8.getFirst()) << endl;
  cout << "remove after list dll8: " << dll8 << endl << endl;

  //TESING LENGTH
  cout << "Length of dll8: " << DoublyLinkedListLength(dll8) << endl;
  
  return 0;
}
