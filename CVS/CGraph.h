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
    bool find(N);
    bool find(E);
    bool find_node(N, Node* &);
    bool find_edge(E,Edge* &);
    
    void print();
    void foo();

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
bool CGraph<Tr>::find(N data){
    Node* tmp;
    if(!find_node(data, tmp))
        return 0;
    return 1;
}
template <class Tr>
bool CGraph<Tr>::find(N data){
    Edge* tmp;
    if(!find_edge(data, tmp))
        return 0;
    return 1;
}

template <class Tr>
bool CGraph<Tr>::find_node(N data, Node* &tmp){
    for(int i=0; i<m_nodes.size(); i++)
        if(m_nodes[i]->m_data==data){
            tmp=(m_nodes[i]);
            return 1;
        }
    return 0;
}

template <class Tr>
bool CGraph<Tr>::find_edge(E data,Edge* &tmp){
    for(int i=0; i<m_edges.size(); i++)
        if(m_edges[i]->m_data==data){
            tmp=m_edges[i];
            return 1;
        }
    return 0;
}

template <class Tr>
bool CGraph<Tr>::insert_node(N _data){
    Node* new_node=new Node(_data);
    m_nodes.push_back(new_node);
    return 1;
}

template <class Tr>
bool CGraph<Tr>::insert_edge(E _data,N a,N b){
    Node* Nodea,* Nodeb;
    if(!find_node(a, Nodea) or !find_node(b, Nodeb))    return 0;
    Edge* new_edge=new Edge(_data, Nodea, Nodeb);
    Nodea->m_nedges.push_back(new_edge);
    Nodeb->m_nedges.push_back(new_edge);
    m_edges.push_back(new_edge);
    return 1;
}

template <class Tr>
bool CGraph<Tr>::remove_node(N _data){
    Node* delete_node;
    for(int i=0; i<m_nodes.size(); i++){
        if((m_nodes[i])->m_data == _data){
            delete_node= m_nodes[i];
            int size=m_nodes[i]->m_nedges.size();
            for(int j=0; j<size; j++)
                remove_edge(((m_nodes[i])->m_nedges[0])->m_data,((m_nodes[i])->m_nedges[0])->m_node[0]->m_data,((m_nodes[i])->m_nedges[0])->m_node[1]->m_data);
            m_nodes.erase(m_nodes.begin()+i);
            delete delete_node;
            return 1;
        }
    } 
    return 0;
}

template <class Tr>
bool CGraph<Tr>::remove_edge(E _data,N a,N b){
    Node *Na,*Nb;
    if(!find_node(a,Na) or !find_node(b,Nb))    return 0;
    Edge* delete_node;
    for(int i=0; i<m_nodes.size(); i++)
        for(int j=0; j<m_nodes[i]->m_nedges.size(); j++)
            if( (m_nodes[i]->m_nedges[j])->m_data == _data and 
                (m_nodes[i]->m_nedges[j])->m_node[0] == Na and 
                (m_nodes[i]->m_nedges[j])->m_node[1] == Nb )
                m_nodes[i]->m_nedges.erase(m_nodes[i]->m_nedges.begin()+j);

    for(int i=0; i<m_edges.size(); i++)
        if((m_edges[i])->m_data==_data and (m_edges[i])->m_node[0]==Na and (m_edges[i])->m_node[1]==Nb){
            delete_node= m_edges[i];
            m_edges.erase(m_edges.begin()+i);
            delete delete_node;
        }
    return 1;
}

template<class Tr>
void CGraph<Tr>::foo(){
    for(int i=0;i<m_nodes.size();i++){
        for(int j=0;j<m_nodes[i]->m_nedges.size();j++){
            cout<<"n "<<m_nodes[i]->m_data<<" ";
            cout<<m_nodes[i]->m_nedges[j]->m_data<<" ";
            cout<<"- "<<m_nodes[i]->m_nedges[j]->m_node[0]->m_data<<" ";
            cout<<"-> "<<m_nodes[i]->m_nedges[j]->m_node[1]->m_data<<" ";
            cout<<endl;
            if(m_nodes[i]->m_data==m_nodes[i]->m_nedges[j]->m_node[0]->m_data)
            cout<<"sale\n";
            else cout<<"entra\n";
        }
            cout<<endl;
    }
}


#endif //CGRAPH_H