#include "MinQueue.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
    MinQueue<int> Que;

    Que.enqueue(5);
    Que.enqueue(8);
    cout << "ENQUEUE 5 & 8: ";
    cout << Que << "\n";
    cout << "SIZE: ";
    cout << Que.size() << endl;
    cout << "MIN OF LIST: ";
    cout << Que.min() << "\n";
    cout << "DEQUEUE: ";
    Que.dequeue();
    cout << Que << "\n";


    MinQueue<string> Str;
    Str.enqueue("hi");
    Str.enqueue("hello");
    Str.enqueue("wassup");
    cout << "ENQUEUE OF hi hello & wassup: " ;
    cout << Str << "\n";
    cout << "SIZE: ";
    cout << Str.size() << endl;
    cout << "MIN OF LIST: ";
    cout << Str.min() << "\n";
    Str.dequeue();
    cout << "DEQUEUE: ";
    cout << Str;



}