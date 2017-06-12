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
    char op;
    string tim;
    // if(cgraph.insert_node("1.txt"));
    // if(cgraph.insert_node("2.txt"));
    
    cout<<"op: ";cin>>op;
    while(op=='i' or op=='d' or op=='r'){
    if(op=='i')
        if(cgraph.insert());
    if(op=='d'){
        if(cgraph.remove());
    }
    if(op=='r'){
        cout<<"time: ";cin>>tim;
        if(cgraph.restore(tim));
    }
    cgraph.print();
    cout<<"op: ";cin>>op;
    }

    // if(cgraph.insert_edge("a","1.txt","2.txt"));
    

    // cout<<"Buscando nodo 5"<<endl;
    // if(cgraph.foo("7.txt")) cout<<"existe\n";
    // else cout<<"no existe\n";
    
    return 0;
}

