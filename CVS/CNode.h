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
    N m_branch;
    vector<Edge*> m_nedges;
    CFile file;
    CNode(N _data,N _branch){
        m_data=_data;
        m_branch=_branch;
    }

};


    


#endif //CNODE_H