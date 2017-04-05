#ifndef NODE_H
#define NODE_H

#include "Entry.h"

#include <iostream>
#include <vector>

using namespace std;
class Node{
    
    public:
    Node(Node*,int);
    private:
    int n_level;
    Node* n_parent;
    vector<Entry*> n_entries;
};

Node::NodeNode*n_parent,int n_level){
    this->n_level=level;
    this->n_parent=n_parent;
    cout<<"Node created"<<endl;
}


#endif NODE_H