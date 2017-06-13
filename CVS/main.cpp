#include <iostream>
#include "CGraph.h"
#include "CTraits.h"
#include <fstream>
#include <string>
#include <cstring>

#include "CFile.h"

using namespace std;
#define N 25
#define B 65

CGraph<Traits_1> cgraph;

void parser(vector<string> m_parser);

void generar(){
    string tmp="";
    string all="";
    ofstream osfile ("script.txt");
    //osfile<<"insert select master "+all+"\n";
    for(int i = B; i < B+N; i++){
        tmp= i;
        all+=tmp;
        osfile<<"insert select master, "+all+"\n";
    }
    osfile.close(); 
}

void tokenize(){
    string script= "script.txt";
    string line,aux;
    vector<string> m_parser;    
    ifstream file(script.c_str());
    while ( getline(file,line) ){
        m_parser.clear();
        char *str =new char[line.size()+1];
        strcpy(str, line.c_str());
        char *pch = strtok (str,",");
        char *aux = strtok (NULL,",");
        char *pch2 = strtok (pch," ");

        while (pch2 != NULL){
            m_parser.push_back(pch2);
            pch2 = strtok (NULL, " ");
        }
        m_parser.push_back(aux);

        parser(m_parser);
    }
    file.close(); 
}    

void parser(vector<string> m_parser){
        
        for(int i=0;i<m_parser.size();i++)
            cout<<m_parser[i]<<endl;
        cout<<endl;

        if(m_parser[0]== "insert" ){
                if(m_parser[1]=="new")
                cgraph.insert('n', m_parser[2], m_parser[3], m_parser[4]);
                else if(m_parser[1]=="select")
                cgraph.insert('s',m_parser[2],"",m_parser[3]);
            return;
        }
        else if(m_parser[0]== "delete" ){
            cgraph.remove(m_parser[1]);
        }
        else if(m_parser[0]== "restore" ){
        }    
        else
        cout<<"Error, mal ingreso";

    }


int main(){

    generar();
    tokenize();
    cgraph.print();
    
    
    return 0;
}

