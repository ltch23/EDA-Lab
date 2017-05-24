#ifndef CPERSISTENCE_H
#define CPERSISTENCE_H

#include <iostream>

template <class G>
class CPersistence{
public:
    typedef typename G::Edge Edge;
    typedef typename G::E E;

    CPersistence(Edge *m_edge,bool m_op){
    this->m_edge= m_edge;
    this->m_op=m_op;
    }

    Edge* m_edge;
    bool m_op;
    /*
    op=1 -> insert
    op=0 -> delete
    */
};

#endif //CPERSISTENCE_H