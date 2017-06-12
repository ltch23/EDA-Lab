#ifndef CEDGE_H
#define CEDGE_H

#include <iostream>

template <class G>

class CEdge{
public:
    typedef typename G::Node Node;
    typedef typename G::E E;

    CEdge(E e,Node *a, Node *b,bool _op){
        //Node 'a' -- edge 'e' --> Node 'b'     edge a hacia b
        m_node[0]=a;
        m_node[1]=b;
        m_data=e;
        m_op=_op;
        /*
        op=1 -> insert
        op=0 -> delete
        */
    }
    bool m_op;
    E m_data;
    Node* m_node[2];
    
    void print(){
    cout<<m_node[0]->m_data<<" "<<m_node[1]->m_data<<" "<<m_data<<" "<<m_op<<endl;
    }

};

#endif //CEDGE_H