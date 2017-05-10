#ifndef CNODE_H
#define CNODE_H

#include <iostream>
#include <vector>

using namespace std;

template <class G>
class CNode{
public:
    typedef typename G::N N;
    typedef typename G::Edge Edge;

    CNode(N _data){
        m_data=_data;
    }
    
    N m_data;
    vector<Edge*> m_nedges;
};

#endif //CNODE_H