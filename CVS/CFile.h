#ifndef CFILE_H
#define CFILE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CFile{
public:
    void create_file(string &,string);
    void save_file(string &, string &);
    string read_file(string &);
    void merge_file(string & ,string &);
    bool get_change(string ,string &); 
};

void CFile::create_file(string & file_path,string str){
    ofstream os_file (file_path.c_str());
    os_file <<str;
    os_file.close();
}

void CFile::save_file(string & file_path, string & str){
    ofstream os_file ;
    os_file << str;
    os_file.close();
}

string CFile::read_file(string & file_path){
    string line,rpta;
    ifstream is_file(file_path.c_str());
    while (getline (is_file,line))
    rpta+=line;
    is_file.close(); 
    return rpta;
}
void CFile::merge_file(string & str1 ,string & str2){
    str1=str2;
}
bool CFile::get_change(string str1, string & str2){
    char op;
    int lenght;
    if(str1.size() > str2.size()){
        lenght=str2.size();
        str2=str1.erase(0,lenght);
        return false;
    }
    else{
    for(int i=0; i<str1.size();i++){
        if(str1[i]==str2[i])
            continue;
    }
    str2.erase(0,str1.size());
    return true;
    }
}
    

#endif //CEDGE_H