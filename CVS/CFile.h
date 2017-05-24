#ifndef CFILE_H
#define CFILE_H

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class CFile{
public:
void create_file(string &,string);
void save_file(string &, string &);
string read_file(string &);

};

void CFile::create_file(string & file_path,string str){
    ofstream os_file (file_path.c_str());
    os_file <<str;
    os_file.close();
    // return os_file*;

}
void CFile::save_file(string & file_path, string & str){
    ofstream os_file ;
    // if (!os_file.is_open()) return 0;
    os_file << str;
    os_file.close();
    // return os_file*;
}

string CFile::read_file(string & file_path){
    string line,rpta;
    ifstream is_file(file_path.c_str());
    // if (!is_file.is_open() ) return "";
    while (getline (is_file,line))
    rpta+=line;
    is_file.close(); 
    return rpta;
}

#endif //CEDGE_H