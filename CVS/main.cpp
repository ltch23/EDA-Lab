#include <iostream>
#include "CGraph.h"
#include "CTraits.h"
#include <fstream>
#include <string>

using namespace std;
#define file foo

/*string read_file(ifstream &file){
    string aux,str;
    file.open();
    while (!file.eof()) {
		 getline(file,aux);
	 str+=aux+"\n";
	 }
	file.close();
	cout<<"string leido:\n"<<str<<endl;
	return str;
}

void write_file(fstream &file){
	//file.open();
    string aux="writing";
    file<<aux;
    file.close();

}*/

int main(){
/*fstream file1 ;
file1.open("foo_3.txt", std::fstream::in | std::fstream::out| std::fstream::app);
file1.close();
//("foo_1.txt");
//file1<<"file";
//ofstream file1("foo_3.txt");
ifstream file("foo.txt");
write_file(file1);
//remove("foo_3.txt");

/*fstream file_tmp ("foo_tmp.txt", std::fstream::in | std::fstream::out);

file_tmp=file;*/


    
	CGraph<Traits_1> cgraph;
    if(cgraph.insert_node(1));
    if(cgraph.insert_node(2));
    if(cgraph.insert_node(3) );
    if(cgraph.insert_node(4));
    if(cgraph.insert_edge("a",1,2));
    if(cgraph.insert_edge("b",1,3)); 
    if(cgraph.insert_edge("c",1,4));
    if(cgraph.insert_edge("d",2,3));
    if(cgraph.insert_edge("e",2,4));
    if(cgraph.insert_edge("f",3,4));

	cgraph.print();
    
    
    if(cgraph.remove_node(4));
    if(cgraph.remove_edge("a",1,2)) cout<<"eliminado"<<endl;
    if(cgraph.remove_edge("b",1,3));
    if(cgraph.remove_edge("c",1,4));
    cgraph.print();
    
    cgraph.foo();
	

    return 0;
}

