#ifndef CPERSISTENCE_H
#define CPERSISTENCE_H

#include <iostream>

template <class G>
class CPersistence{
public:
    typedef typename G::Edge Edge;
    typedef typename G::E E;

    CPersistence(Edge *m_edge, E m_data, bool m_op){
    this->m_edge= m_edge;
    this->m_data=m_data;
    this->m_op=m_op;
    }

    E* m_edge;
    bool m_op;
    E m_data;
};

#endif //CPERSISTENCE_H