#include "SkipList.h"
#include <iostream>
#include <ostream>
#include <fstream>

using namespace std;

SkipList read_file(string file_name){
  SkipList skipl;
  ifstream data;
  data.open(file_name);
  data >> skipl;
  data.close();
  return skipl;
}

int main(){
    string file_name;
    cout << "Name of IN File?" <<  endl;
    cin >> file_name;

    SkipList list;

    ifstream data;
    data.open(file_name);
    data >> list;
    data.close();

    //list.print();
    cout << list;
    cout << "SEARCH 5: " << list.search(5) << "    SEARCH 88: " << list.search(88) << endl;

    list.removeall();
    //list.print();
    cout << list;
    cout << "average insert: " <<  list.averageInsert() << " average delete: " << list.averageDelete() << endl;
}