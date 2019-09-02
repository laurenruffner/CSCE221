#ifndef ADJMATRIX_H_
#define ADJMATRIX_H_

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <ostream>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

class AdjMatrix{
    private:
        int num_nodes;
        int num_edges;
    public:
        vector<vector<bool>> adjVec;

        AdjMatrix(int temp1,int temp2) {
            this->num_nodes = temp1;
            this->num_edges = temp2;
            adjVec = vector<vector<bool>>(num_nodes);
            for (int i = 0; i <  num_nodes; i++){
                adjVec[i] = vector<bool>(num_nodes);
                for (int j=0; j < num_nodes; j++){
                    adjVec[i][j] = 0;
                }
            }
        }

        void graph(ifstream &in);
        void add_edge(int first_v, int second_v);
        void print_graph(ofstream &out);
        void print_list(ofstream &out);

};

void AdjMatrix::add_edge(int first_v, int second_v){
    adjVec[first_v-1][second_v-1] = 1;
    adjVec[second_v-1][first_v-1] = 1;
}

void AdjMatrix:: print_graph(ofstream &out){
    cout << "   ";
    out << "   ";
    for (int k=0; k < adjVec.size(); k++){
        cout << k+1 << " ";
        out << k+1 << " ";
    }
    cout << endl << "-------------------" << endl;
    out << endl << "-------------------" << endl;

    int counter = 1;

    for (int i=0; i < adjVec.size(); i++){
        if (counter > 9){
            cout << counter << "|";
            out << counter << "|";
        }
        else {
            cout << counter << " |";
            out << counter << " |";
        }

        for (int j = 0; j<adjVec.size(); j++){
            cout << adjVec[i][j] << " ";
            out << adjVec[i][j] << " ";
        }
        cout << endl;
        out << endl;
        counter++;
    }
}

void AdjMatrix::  print_list(ofstream &out){
     int counter = 1;

    for (int i=0; i < adjVec.size(); i++){
        cout << counter;
        out << counter;
        for (int j = 0; j<adjVec.size(); j++){
            if (adjVec[i][j] == 1){
                cout << " -> " << j+1;
                out << " -> " << j+1;
            }
        }
        cout << endl;
        out << endl;
        counter++;
    }
    cout << endl;
    out << endl;
}

void AdjMatrix:: graph(ifstream &in){
    int node1, node2;
    while (in >> node1 >> node2){
        this->add_edge(node1, node2);
    }
}

//EULER MEHTOD

class Graph{ 
    int num_vertices;
    int num_edges = 0;
    vector<list<int>> adjList;
    vector<list<int>> adjCopy;
    vector<int> Stack;
public:
    Graph(int num_vertices, int num_edges) {
        this-> num_vertices = num_vertices;
        this-> num_edges = num_edges;
        for (int i = 0; i < num_vertices; i++){
            list<int> ll;
            adjList.push_back(ll);
        }
    } 

    void addEdge(int v, int w);
    string isEulerian(); 
    bool isConnected();
    void make(ifstream &in); 
    void print();
    void DFSUtil(int v, bool visited[]); 
  
  // Methods to print Eulerian tour 
   bool search(int u); 
   void eulerianPath();
   void print(vector<int> vec);

}; 
  
void Graph::addEdge(int v, int w){ 
    adjList[v-1].push_back(w);
    adjList[w-1].push_back(v);
} 

void Graph:: make(ifstream &in1){
    int node1,node2;
    while(in1 >> node1 >> node2){
        this->addEdge(node1,node2);
    }
    for (int i = 0; i < adjList.size(); i++){
        adjList[i].sort();
    }
};

void Graph:: print(){
    for (int i = 0; i < adjList.size(); i++){
        cout << i+1;
        auto j = adjList[i].begin();
        for (j; j != adjList[i].end(); j++){
            cout <<  " -> " << *j; 
        }
        cout << endl;
    }
}
  
void Graph::DFSUtil(int v, bool visited[]){
    visited[v] = true;
    
    for (int j =0; j < adjList.at(v).size(); j++){
        list<int>::iterator iter8 = adjList.at(v).begin();
        advance(iter8, j);
        int var = *iter8;
        if (!visited[var-1]){
            DFSUtil(var-1,visited);
        }            
    }
}

bool Graph::isConnected() { 
    bool visited[num_vertices]; 
    int i; 
    for (i = 0; i < num_vertices; i++){ 
        visited[i] = false; 
    }
    for (i = 0; i < num_vertices; i++){ 
        if (adjList.at(i).size() != 0){
            break;
        } 
    }
    if (i == num_vertices){ 
        return true; 
    }
    DFSUtil(i, visited);  
    for (i = 0; i < num_vertices; i++){ 
        if (visited[i] == false && adjList[i].size() > 0){ 
            return false; 
        }
    }
    return true; 
}

string Graph::isEulerian(){
    int odd = 0; 
    if (isConnected() == false){
        return "No";
    } 
    for (int i = 0; i < num_vertices; i++){
        if (adjList[i].size() & 1){
            odd++; 
        }
    }
    if (odd > 2){ 
        return "No"; 
    }
    return "Yes";
} 

void Graph::eulerianPath(){
    bool search_result;
    bool allcovered = true;
    for (int i=0; i < adjList.size(); i++){
        adjCopy = adjList;
        search_result = search(i+1);

        for (int i = 0; i < adjList.size(); i++){
            int j = 0;
            for(;j<Stack.size(); j++){
                if ((i+1) == Stack[j]){
                    break;
                }
            }
            if (j == Stack.size()){
                allcovered = false;
                break;
            }
        }

        if (search_result && allcovered && (Stack.size() -1 == num_edges)){
            print(Stack);
            return;
        }
        else{
            Stack.clear();
            allcovered = true;
        }
    }
}

bool Graph:: search(int u){
    Stack.push_back(u);
    if (adjCopy.at(u-1).empty()){
        return true;
    } 
    for (auto i = adjCopy.at(u-1).begin(); i != adjCopy.at(u-1).end(); ++i){
        int v = *i;
        adjCopy.at(u-1).remove(v);
        auto j = adjCopy.at(v-1).begin();
        while (*j != u && j != adjCopy.at(v-1).end()) j++;
        adjCopy.at(v-1).remove(u);
        if (search(v)){
            return true;
        }
        else{
            adjCopy.at(u-1).insert(i,v);
            adjCopy.at(v-1).insert(j,u);
        }

    }
    Stack.pop_back();
    return false;
}

void Graph::print(vector<int> vec){
    int i = 0;
    for (; i < vec.size() -2; i++){
        if(i == 0){
            cout << "Starting Vertex: " << vec.at(i) << endl;
        }
        
        cout << "(" << vec.at(i) << ", " << vec.at(i+1) << ") -> "; 
    }
    cout << "(" << vec.at(i) << ", " << vec.at(i+1) << ")" << endl;
}
#endif