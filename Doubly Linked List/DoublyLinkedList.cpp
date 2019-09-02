#include "DoublyLinkedList.h"
#include <stdexcept>

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  if (!dll.isEmpty()){
    DListNode* node;
    node=dll.getFirst();
    while (node!=dll.getAfterLast()){
      insertLast(node->obj);
      node=node->next;
    
  }
}

// move constructor
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& dll)
{ 
  this->header.next = dll.header.next;
  this->trailer.prev = dll.trailer.prev;

  dll.header.next->prev = &this->header;
  dll.trailer.prev->next = &this->trailer;

  dll.header.next = &dll.trailer;
  dll.trailer.prev = &dll.header;

}

// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
  DListNode *prev_node, *node = header.next;
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
// move assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& dll)
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

// insert the new object as the first one
void DoublyLinkedList::insertFirst(int newobj)
{ 
  DListNode *newNode = new DListNode(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
  DListNode *newNode = new DListNode(newobj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;

}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  int obj = node->obj;
  delete node;
  return obj;
}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  int obj = node->obj;
  delete node;
  return obj;
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
  DListNode *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// return the first object
int DoublyLinkedList::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}

// return the last object
int DoublyLinkedList::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj)
{
  DListNode *newNode = new DListNode(newobj, &p, p.next);
  p.next->prev = newNode;
  p.next = newNode;

}

// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode &p, int newobj)
{
  DListNode* newNode = new DListNode(newobj, &p, p.next);
  p.prev->next = newNode;
  p.prev = newNode;
}

// remove the node after the node p
int DoublyLinkedList::removeAfter(DListNode &p)
{
  DListNode *test = &p;
  if (test->next == this->getAfterLast()){
    throw EmptyDLinkedListException("No Node After");
  }
  DListNode *node = p.next;
  node->next->prev = &p;
  p.next = node-> next;
  int obj = node->obj;
  delete node;
  return obj;
}

// remove the node before the node p
int DoublyLinkedList::removeBefore(DListNode &p)
{ DListNode *test = &p;
  if(test->prev == this->getFirst()->prev){
    throw EmptyDLinkedListException("No Node Before");
  }

  DListNode *node = p.prev;
  node->prev->next = &p;
  p.prev = node-> prev;
  int obj = node->obj;
  delete node;
  return obj;
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
  DListNode *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->next; //iterate
  }
  return count;
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
  DListNode* temp=dll.getFirst();
  while (temp!=dll.getAfterLast()){
      out<<temp->obj<<" ";
      temp=temp->next;
    }
  return out;
}
