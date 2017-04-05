#ifndef RTREE_H
#include "Entry.h"
#include "Mbr.h"
#include "Node.h"

#include <iostream>
#include <math.h>
#include <vector> 
typedef DataType int;

using namespace std;

class RTree{
public:
	RTree( int , int );
	Node* chooseLeaf( Mbr );
	void search();
	void delete( Entry );
	void insert( Mbr , Data);
	~RTree();

private:
	/*
		Tenemos como parte de la estructura los valores constantes:
			N - numero de dimensiones
			M - numero de entradas máximas por nodo
			m - numero de entradas minimas por nodo (M/2)
	*/
	const int N;
	const int M;
	const int m;
	Node* root;

	/* metodo insert */
	void splitNode( Node& , Node& , Entry& , Mbr& , Mbr& );
	void pickSeeds( int* , int* , vector<Entry*> );
	void pickNext( Mbr* , Mbr* , int* , vector<Entry*> );
	bool adjustTree( Node& , Node& , Mbr& , Mbr& );
	void putEntry( Node* , Mbr , Data );

	/* metodo delete */
	Node* findLeaf( Entry );
	void condenseTree( Node& );
};












#endif //RTREE_H