#include <iostream>
using namespace std;

int main(){

    int s = 0;
    int i = 1;
    while (i > 0){
        s++;
        i/=2;
    }
    cout << s;
}