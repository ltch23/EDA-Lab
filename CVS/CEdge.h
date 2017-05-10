#ifndef CEDGE_H
#define CEDGE_H

#include <iostream>

template <class G>

class CEdge{
public:
    typedef typename G::Node Node;
    typedef typename G::E E;

    CEdge(E e,Node *a, Node *b){
        //Node 'a' -- edge 'e' --> Node 'b'     edge a hacia b
        m_node[0]=a;
        m_node[1]=b;
        m_data=e;
    }

    E m_data;
    Node* m_node[2];
};

#endif //CEDGE_H