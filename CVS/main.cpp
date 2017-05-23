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
    if(cgraph.insert_node("1.txt"));
    if(cgraph.insert_node("2.txt"));
    if(cgraph.insert_node("3.txt"));
    if(cgraph.insert_node("4.txt"));
    if(cgraph.insert_node("5.txt"));
    if(cgraph.insert_node("6.txt"));

    // if(cgraph.insert_node(file.create("3")));
    // if(cgraph.insert_node(file.create("4")));
    
    if(cgraph.insert_edge("a","1.txt","2.txt"));
    if(cgraph.insert_edge("b","2.txt","3.txt"));
    if(cgraph.insert_edge("c","3.txt","4.txt"));
    if(cgraph.insert_edge("d","3.txt","5.txt"));
    if(cgraph.insert_edge("e","3.txt","6.txt"));
    // if(cgraph.insert_edge("d",2,3));
    // if(cgraph.insert_edge("e",2,4));
    // if(cgraph.insert_edge("f",3,4));
    cgraph.print();

    cout<<"Buscando nodo 5"<<endl;
    if(cgraph.foo("7.txt")) cout<<"existe\n";
    else cout<<"no existe\n";
    // cout<<"Buscando nodo 5"<<endl;
    // if(cgraph.find(5)) cout<<"existe\n";
    // else cout<<"no existe\n";

    // cout<<"Buscando arista c"<<endl;
    // if(cgraph.find("c")) cout<<"existe\n";
    // else cout<<"no existe\n";
    // cout<<"Buscando arista x"<<endl;
    // if(cgraph.find("x")) cout<<"existe\n";
    // else cout<<"no existe\n";

    // if(cgraph.remove_node(4));
    // cout<<"eliminando nodo 4\n";
    // cgraph.print();
    
    // if(cgraph.remove_edge("a",1,2));
    // if(cgraph.remove_edge("b",1,3));
    // cout<<"eliminando aristasa a, b\n";
    // cgraph.print();
    
    return 0;
}

