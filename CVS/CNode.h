#ifndef CNODE_H
#define CNODE_H

#include <iostream>
#include <vector>
#include "CFile.h"

using namespace std;

template <class G>
class CNode{
public:
    typedef typename G::N N;
    typedef typename G::Edge Edge;
    
    N m_data;
    vector<Edge*> m_nedges;
    CFile file;
    CNode(N _data){
        m_data=_data;
    }

};


    


#endif //CNODE_H