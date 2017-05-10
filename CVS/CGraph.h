#ifndef CGRAPH_H
#define CGRAPH_H

#include "CNode.h"
#include "CEdge.h"

#include <iostream>
#include <vector>

using namespace std;

template <class Tr>
class CGraph{

public:

    typedef CGraph<Tr> self;
    typedef CNode<self> Node;
    typedef CEdge<self> Edge;
    typedef typename Tr::n N;
    typedef typename Tr::e E;
   
    vector<Node*> m_nodes;
    vector<Edge*> m_edges;

    bool insert_node(N);
    bool insert_edge(E,N,N);
    bool remove_edge(E,N,N);
    bool remove_node(N);

    void print();
};

template<class Tr>
void CGraph<Tr>::print(){
    cout<<"Grafo"<<endl;
    cout<<"Nodos:";
    for(int i=0; i<m_nodes.size();i++)
        cout<<m_nodes[i]->m_data<<" ";
    cout<<"\nAristas:"<<endl;
        for(int i=0; i<m_edges.size(); i++){
        cout<<m_edges[i]->m_node[0]->m_data;
        cout<<"  -- "<<m_edges[i]->m_data;
        cout<<" -->   "<<m_edges[i]->m_node[1]->m_data<<endl;
        }
}

template <class Tr>
bool CGraph<Tr>::insert_node(N _data){
    Node* new_node=new Node(_data);
    m_nodes.push_back(new_node);
    return 1;
}

template <class Tr>
bool CGraph<Tr>::insert_edge(E _data,N a,N b){
    Node *Nodea,*Nodeb;
    for(int i=0; i<m_nodes.size(); i++){
        if(m_nodes[i]->m_data==a) Nodea=m_nodes[i];
        if(m_nodes[i]->m_data==b) Nodeb=m_nodes[i];
    }
    Edge* new_edge=new Edge(_data,Nodea,Nodeb);
    Nodea->m_nedges.push_back(new_edge);
    Nodeb->m_nedges.push_back(new_edge);
    m_edges.push_back(new_edge);
    return 1;
}

template <class Tr>
bool CGraph<Tr>::remove_node(N _data){
/*    Node* delete_node;
    for(int i=0; i<m_nodes.size(); i++)
        if((m_nodes[i])->m_data==_data){
            delete_node= m_nodes[i];
            for(int j=0; j<(m_nodes[i])->m_nedges.size(); j++)
                remove_edge(((m_nodes[i])->m_nedges[j])->m_data,((m_nodes[i])->m_nedges[j])->m_node[0]->m_data,((m_nodes[i])->m_nedges[j])->m_node[1]->m_data);
            m_nodes.erase(m_nodes.begin()+i);
            delete delete_node;
    }
    return 1;
    */
}

template <class Tr>
bool CGraph<Tr>::remove_edge(E _data,N a,N b){
/*    Node *Na,*Nb;
    for(int i=0; i<m_nodes.size(); i++){
        if(m_nodes[i]->m_data==a) Na=m_nodes[i];
        if(m_nodes[i]->m_data==b) Nb=m_nodes[i];
    }
    Edge* delete_node;
    for(int i=0; i<m_nodes.size(); i++)
        for(int j=0; j<m_nodes[i]->m_nedges.size(); j++)
            if((m_nodes[i]->m_nedges[j])->m_data==_data and (m_nodes[i]->m_nedges[j])->m_node[0]==Na and (m_nodes[i]->m_nedges[j])->m_node[1]==Nb)
                m_nodes[i]->m_nedges.erase(m_nodes[i]->m_nedges.begin()+j);

    for(int i=0; i<m_edges.size(); i++)
        if((m_edges[i])->m_data==_data and (m_edges[i])->m_node[0]==Na and (m_edges[i])->m_node[1]==Nb)
        {
            delete_node= m_edges[i];
            m_edges.erase(m_edges.begin()+i);
            delete delete_node;
        }
    return 1;
*/
}

#endif //CGRAPH_H