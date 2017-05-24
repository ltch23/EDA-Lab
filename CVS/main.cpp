#include <iostream>
#include "CGraph.h"
#include "CTraits.h"
#include <fstream>
#include <string>
#include "CFile.h"


using namespace std;
#define file foo

int main(){

	CGraph<Traits_1> cgraph;
    
    // if(cgraph.insert_node("1.txt"));
    // if(cgraph.insert_node("2.txt"));
    if(cgraph.insert());


    // if(cgraph.insert_edge("a","1.txt","2.txt"));
    
    cgraph.print();

    // cout<<"Buscando nodo 5"<<endl;
    // if(cgraph.foo("7.txt")) cout<<"existe\n";
    // else cout<<"no existe\n";
    
    return 0;
}

