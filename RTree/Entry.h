#ifndef ENTRY_H
#define ENTRY_H
#include "Mbr.h"

#include <iostream>

/*cada entrada almacena un mbr y un puntero vacio
si entrada pertenece nodo hoja, apuntara a objeto de clase data
sino apuntara a su hijo.*/

class Entry{

public:
    Entry(Mbr,void*);
private:
    Mb* e_mbr;
    void* e_child;
};
Entry::Entry(Mbr* e_mbr, void * e_child){
//Entry::Entry(Mbr e_mbr, void * e_child){
    this->e_mbr=e_mbr;
    this->e_child=e_child;
}


#endif //ENTRY_H