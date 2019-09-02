// main.cpp
// Tests all functionality of the class My_matrix class.

#include <iostream>
#include <fstream>
#include "My_matrix.h"

int main(){
  
    
  try{

    //Test 1

    My_matrix m1(2,3);
    cout << m1;
    m1.fillmat();

    cout << "M1: \n";
    cout << m1;

    // Test 2
    
    string filename, out_name;
    My_matrix m2;
    cout << "File name: \n";
    cin >> filename;
    ifstream in; 
    in.open(filename);

    cout << "Output File Name: \n";
    cin >> out_name;
    ofstream save_out;
    save_out.open(out_name);
    in >> m2;
    cout << "M2: \n";
    cout << m2;
    save_out << m2;
    in.close();
    save_out.close();
    
    // Test 3

    My_matrix m3(m1);
    My_matrix m4;
    m4 = m1;
    cout << "M4: \n";
    cout << m4;
    cout << "M3: \n";
    cout << m3;
    
    // Test 4
   
    My_matrix m5(3,4);
    m5.fillmat();
    cout << m5;
    cout << "MULTIPLIED MATRIX: \n";
    cout << m1*m5;
    
    //FAILED ONE BECAUSE OF SIZE
    cout << m1*m2;

    // Test 5

    cout << "ADDED MATRIX: \n";
    cout << m1+m2;

    //FAILED ONE BECAUSE OF SIZE
    cout << m1+m5;

  } catch(exception &error){
    cerr << "Error: " << error.what() << endl;
  }
}
