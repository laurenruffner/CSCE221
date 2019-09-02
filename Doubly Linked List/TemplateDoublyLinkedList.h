#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

//template <typename T>
template <typename T> class DoublyLinkedList; // class declaration




template <typename T> struct DListNode {
  T obj;
  DListNode<T> *prev, *next;
  DListNode(T e= T(), DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
};

template <typename T> class DoublyLinkedList {
private:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList(const DoublyLinkedList<T>& dll); // copy constructor
  DoublyLinkedList(DoublyLinkedList<T>&& dll); // move constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& dll); // move assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insertAfter(DListNode<T> &p, T newobj);
  void insertBefore(DListNode<T> &p, T newobj);
  T removeAfter(DListNode<T> &p);
  T removeBefore(DListNode<T> &p);
};

template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);

template <typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll);

struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list'
  //cout << "1" << endl;

  header.next = &trailer;
  trailer.prev = &header;
  
  //cout << "2" << endl;
  if (!dll.isEmpty()){
    DListNode<T>* node;
    node=dll.getFirst();
    while (node!=dll.getAfterLast()){
      insertLast(node->obj);
      node=node->next;
    }
  }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& dll)
{ 
  this->header.next = dll.header.next;
  this->trailer.prev = dll.trailer.prev;

  dll.header.next->prev = &this->header;
  dll.trailer.prev->next = &this->trailer;

  dll.header.next = &dll.trailer;
  dll.trailer.prev = &dll.header;

}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{

  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }

  header.next = &trailer;
  trailer.prev = &header;
  if (!dll.isEmpty()){
    node=dll.getFirst();
    while (node!=dll.getAfterLast()){
      insertLast(node->obj);
      node=node->next;
    }
  }
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& dll)
{ if (this != &dll){
    this-> ~DoublyLinkedList();

    this->header.next = dll.header.next;
    this->trailer.prev = dll.trailer.prev;

    dll.header.next->prev = &this->header;
    dll.trailer.prev->next = &this->trailer;

    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;

  }
  return *this;
}

template <typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

template <typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;

}

template <typename T>
T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}

template <typename T>
// remove the last object from the list
T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}

template <typename T>
// destructor
DoublyLinkedList<T>::~DoublyLinkedList()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
template <typename T>
// return the first object
T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
template <typename T>
// return the last object
T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
template <typename T>
// insert the new object after the node p
void DoublyLinkedList<T>::insertAfter(DListNode<T> &p, T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, &p, p.next);
  p.next->prev = newNode;
  p.next = newNode;

}
template <typename T>
// insert the new object before the node p
void DoublyLinkedList<T>::insertBefore(DListNode<T> &p, T newobj)
{
  DListNode<T>* newNode = new DListNode<T>(newobj, &p, p.next);
  p.prev->next = newNode;
  p.prev = newNode;
}
template <typename T>
// remove the node after the node p
T DoublyLinkedList<T>::removeAfter(DListNode<T> &p)
{
  DListNode<T> *test = &p;
  if (test->next == this->getAfterLast()){
    throw EmptyDLinkedListException("No Node After");
  }
  DListNode<T> *node = p.next;
  node->next->prev = &p;
  p.next = node-> next;
  T obj = node->obj;
  delete node;
  return obj;
}
template <typename T>
// remove the node before the node p
T DoublyLinkedList<T>::removeBefore(DListNode<T> &p)
{ DListNode<T> *test = &p;
  if(test->prev == this->getFirst()->prev){
    throw EmptyDLinkedListException("No Node Before");
  }

  DListNode<T> *node = p.prev;
  node->prev->next = &p;
  p.prev = node-> prev;
  T obj = node->obj;
  delete node;
  return obj;
}
template <typename T>
// return the list length
int DoublyLinkedListLength(DoublyLinkedList<T>& dll)
{
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->next; //iterate
  }
  return count;
}
template <typename T>
// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
  DListNode<T>* temp=dll.getFirst();
  while (temp!=dll.getAfterLast()){
      out<<temp->obj<<" ";
      temp=temp->next;
    }
  return out;
}