#include <iostream>
#include <fstream>
#include "AdjMatrix.h"
using namespace std;

int main(int argc, char** argv){
    int nodes, edges;
    string name1,name2;
    cout << "Name of input file: " << endl;
    name1 = argv[1];
    cout << argv[1] << endl;

    ifstream in(argv[1]);
    cout << "Name of output file?" << endl;
    cin  >> name2;
    ofstream out(name2);
    in >> nodes >> edges;

    AdjMatrix matrix(nodes, edges);
    matrix.graph(in);
    matrix.print_graph(out);

    cout << endl;
    ifstream in1(name1);
    in1 >> nodes >> edges;
    Graph graph(nodes,edges);
    graph.make(in1);
    graph.print();
    cout << graph.isEulerian() << endl;
    graph.eulerianPath();

}