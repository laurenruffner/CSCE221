#include <iostream>
#include <limits>
#include <list>
#include <iterator>
#include <vector>
#include <ctime>
#include <math.h>

using namespace  std;

//SETTING MY LIMITS
int pos_inf = numeric_limits<int>::max();
int neg_inf = numeric_limits<int>::min();

//NODE STRUCT
struct Node{
  int val;
  int level;
  int searchcost;
  int insertcost;
  list <Node>::iterator down;
  Node() {
    val = NULL;
    level = NULL;
  }
  Node(int val, int level, list <Node>::iterator down) : val(val), level(level), down(down) {}
  Node(int val, int level, list <Node>::iterator down,int insertcost) : val(val), level(level), down(down), insertcost(insertcost) {}
};


//SKIPLIST CLASS
class SkipList
{
  private:
    vector<list<Node>> totalvec;
    const int max_height = 7;
    double totalnums = 0;
    int size = 0;
    double average_insertcost = 0;
    double average_deletecost = 0;
    
  public:
    //Default constructor
    SkipList(){
      srand(time(NULL));
      totalvec.push_back(list<Node> ());
      totalvec.at(0).push_back(Node(neg_inf, 0, totalvec[0].begin()));
      totalvec.at(0).push_back(Node(pos_inf, 0, totalvec[0].end()));
      for (int i = 1; i < max_height;  i++){
        totalvec.push_back(list<Node> ());
        totalvec.at(i).push_back(Node(neg_inf, i, totalvec[i-1].begin()));
        totalvec.at(i).push_back(Node(pos_inf, i,totalvec[i-1].end()));
      }
    }

    //Getters
    vector<list<Node>> get_vec(){
      return totalvec;
    }

    int get_totalnums(){
      return totalnums;
    }

    //Insert
    void insert(int value);

    //Delete
    void remove(int value);
    void removeall();

    //Search
    bool search(int value);

    list<Node>::iterator search1(int value);

    //Average Cost for Insertion
    double averageInsert();

    //Average Cost for Deletion
    double averageDelete();

    void print();
    

};

void SkipList::insert(int value){

  //CALCULATING NUM OF HEADS IN A ROW

  //cout << "pos " << pos_inf << endl;
  totalnums++;

  int total_heads = 0;
  for (int i = 0; i < max_height; i++){
    bool temp;
    if (rand()%2 == 1){
      total_heads++; //odd heads
    }
    else{      
      break; // even tails
    }
  }

  //DOESNT ALLOW IT OVER MAX HEIGHT 
  if (total_heads > 5){
    total_heads = 5;
  }

  cout << "Insert value " << value << " at level " << total_heads;

  int insert_comparisons_node = 0;
  int level = max_height-1;
  list<Node>::iterator iter8 = totalvec.at(level).begin();  
  list<Node>::iterator temp = iter8;

  while (level >= 0){
    while(1){
      iter8++;
      insert_comparisons_node++;
      average_insertcost++;


      if((iter8->val > value) && (level > total_heads)){
        temp = temp->down;
        iter8 = temp;
        break;
      }

      else if((iter8->val > value) && (level == total_heads) && (total_heads != 0)){
        totalvec.at(level).insert(iter8, Node(value,level,iter8,insert_comparisons_node));

        size++;
        iter8--;
        iter8->down = iter8;
        temp = iter8;
        iter8--;
        iter8 = iter8->down;
        break;
      }

      else if(((iter8->val > value) && (level == total_heads))){
        totalvec.at(level).insert(iter8, Node(value,level,iter8,insert_comparisons_node));
        size++;
        iter8--;
        iter8->down = iter8;
        temp->down = iter8;
        break;
      }

      else if((iter8->val > value) && (level < total_heads)){
        totalvec.at(level).insert(iter8, Node(value,level,iter8,insert_comparisons_node));
        size++;
        iter8--;
        temp-> down = iter8;
        temp = iter8;
        iter8--;
        iter8 = iter8->down;
        break;
      }
      else if((iter8->val == pos_inf) && (level == 0)){
        break;
      }

    }
    level--;
  }

  cout << " Number of Comparisons: " << insert_comparisons_node << endl;

  // BOTTOMS UP
  // do{
  //   iter8 = totalvec.at(level).begin();
  //   while(true){
  //     if (iter8->val > value){
  //       if (level == 0){
  //         totalvec.at(level).list::insert(iter8, Node(value,iter8));
  //         iter8--;
  //         iter8->down = iter8;
  //         previous = iter8;
  //         break;
  //       }
  //       else{
  //         totalvec.at(level).list::insert(iter8,Node(value,previous));
  //         iter8--;
  //         previous = iter8;
  //         break;
  //       }
  //     }
  //     iter8++;
  //   }
  //   level++;
  // }while(level <= total_heads);

}


//SEARCH FOR VALUE IN ALL LISTS
bool SkipList:: search(int value){

  int level = totalvec.size()-1;
  list<Node>::iterator iter8;
  iter8 = totalvec.at(level).begin();
  while (level >= 0 ){
    while (true){
      //cout << "dick" << endl;

      if (iter8-> val == value){
        return true;
      }
      else if(iter8->val == pos_inf && level == 0){
        return false;
      }
      else if ((++iter8)->val > value){
        iter8--;
        iter8 = iter8->down;
        level--;
        break;
      }
      else if ((++iter8)-> val < value){
        iter8++; 
        break;
      }
      else{
        iter8--;
      }
    }
  }
  return false;
}


//MADE THIS SPECIFICALLY FOR REMOVE TAKES O(logn)
_List_iterator<Node> SkipList:: search1(int value){
  int search_cost = 0;
  list<Node> temp;
  temp.push_back(Node());
  list<Node>::iterator temp2; 
  int level = totalvec.size()-1;
  list<Node>::iterator iter8;
  iter8 = totalvec.at(level).begin();
  while (level >= 0 ){
    while (true){
      search_cost++;

      if (iter8-> val == value){
        iter8->searchcost = search_cost;
        return iter8;
      }

      else if(iter8->val == pos_inf && level == 0){
        return temp2;
      }

      else if ((++iter8)->val > value){
        iter8--;
        iter8 = iter8->down;
        level--;
        break;
      }

      else if ((++iter8)-> val < value){
        iter8++; 
        break;
      }

      else{
        iter8--;
      }
    }
  }
  return temp2;
}
          
          
//REMOVE SINGLE VALUE FROM LIST EVERYWHERE
void SkipList:: remove(int value){
  list<Node>::iterator iter8 = search1(value);
  int level = iter8->level;
  list<Node>::iterator temp = iter8->down;

  average_deletecost = average_deletecost + iter8->searchcost;
  cout << "Delete " << value << " from skip list, " << iter8->searchcost << " comparisons" << endl;

  while (level >= 0){
    totalvec.at(level).list::erase(iter8);
    if (level == 0){
      break;
    }
    iter8 = temp;
    temp = iter8->down;
    level--;
  }
}

void SkipList:: removeall(){
  
  while(true){
    list<Node>::iterator iter9 = totalvec.at(0).begin();
    if((++iter9)->val == pos_inf){
      break;
    }

    if(iter9->val == neg_inf){
      iter9++;
    }

    remove(iter9->val);
    iter9++;
    
  }
}

double SkipList:: averageInsert(){
  return (average_insertcost/totalnums);
}

double SkipList:: averageDelete(){
  return (average_deletecost/totalnums);
}


void SkipList:: print(){
  int level = totalvec.size()-1;
  list<Node>::iterator iter8;

  if (totalnums <= pow(2,4)){
    cout << "----------------------------" << endl;
    while (level >= 0 ){
    cout << "-oo ";
    iter8 = totalvec.at(level).begin();
    iter8++;
      while (iter8->val != pos_inf){
        cout << iter8->val << " ";
        iter8++;
      }
    cout << "+oo" << endl;
    level--;
    }
    cout << "----------------------------"<< endl;
  }
  else{
    cout << "Too Large of a Data File to print" << endl;
  }
}



//FOR SOME REASON THIS DOESN'T WORK ON PUTTY ---------- ---------------------
ostream& operator<<(ostream& out, SkipList& listt){
  int level = listt.get_vec().size()-1;
  list<Node>::iterator iter8;

  if (listt.get_totalnums() <= pow(2,4)){
    out << "----------------------------" << endl;
    while (level >= 0 ){
    out << "-oo ";
    iter8 = listt.get_vec().at(level).begin();
    iter8++;
      while (iter8->val != pos_inf){
        out << iter8->val << " ";
        iter8++;
      }
    out << "+oo" << endl;
    level--;
    }
    out << "----------------------------"<< endl;
  }
  else{
    out << "Too Large of a Data File to print" << endl;
  }
  return out;
}
//--------------------------------------------------------------------

istream& operator>>(istream& in, SkipList& skipl)
{
  int x;
  while (!in.eof()) {
    in >> x;
    skipl.insert(x);
  }
  return in;
}
