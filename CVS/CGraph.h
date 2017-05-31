#ifndef CGRAPH_H
#define CGRAPH_H

#include "CNode.h"
#include "CEdge.h"
#include "CPersistence.h"
#include "CFile.h"

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

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
    vector<string> m_branches;
    CFile cfile;
    string file="foo.txt";
    bool insert_node(N,N);
    bool insert_edge(E,N,N,bool);
    bool remove_edge(E,N,N);
    bool remove_node(N);
    bool find_N(N);
    bool find_E(E);
    bool find_node(N, Node* &);
    bool find_edge(E,Edge* &);
    void find_last(Node*&);
    bool find_branch(N data);
    string consult(Node*, Node*);
    bool insert();
    bool remove(string);
    bool restore(string);
    void print();
    bool find_(N,Node*&);

};

template<class Tr>
void CGraph<Tr>::print(){
    cout<<"Grafo"<<endl;
    
    cout<<"Nodos:\n";
    for(int i=0; i<m_nodes.size();i++){
        cout<<m_nodes[i]->m_data<<" ";
        cout<<m_nodes[i]->m_branch<<"\n";
    }
    cout<<endl;
    cout<<"\nAristas:"<<endl;
        for(int i=0; i<m_edges.size(); i++){
        cout<<m_edges[i]->m_node[0]->m_data;
        cout<<"  -- "<<m_edges[i]->m_data;
        cout<<" -->   "<<m_edges[i]->m_node[1]->m_data<<endl;
        }

    cout<<"\nRamas:"<<endl;
       for (int i=0; i<m_branches.size();i++)
        cout<<m_branches[i]<<" ";cout<<endl;
    // cout<<endl;

}
template<class Tr>
string CGraph<Tr>::consult(Node* begin, Node* last){
    string branch=begin->m_branch;
    string m_rpta=begin->m_data;
    while(begin!=last){
        for(int i=0;i<begin->m_nedges.size();i++){
            if(begin == begin->m_nedges[i]->m_node[0] 
            and begin->m_nedges[i]->m_node[1]->m_branch==branch){
                if(begin->m_nedges[i]->m_op==1)
                    m_rpta+=begin->m_nedges[i]->m_node[1]->m_data;
                else if(begin->m_nedges[i]->m_op==0){
                    int l1= m_rpta.size();
                    int l2= begin->m_nedges[i]->m_node[1]->m_data.size();
                    m_rpta.erase(l1-l2,l1);            
                }
            begin = begin->m_nedges[i]->m_node[1];
            break;
            }       
        }
    }
    return m_rpta;
}

template<class Tr>
bool CGraph<Tr>::insert(){
string data_before="-";
string data_after;
Node* tmp=nullptr;
Node* tmp2=nullptr;
int lenght;
char br; string name="b1";
cout<<"INSERT\n";
// cout<<"nuevo branch 'n': ";cin>>br;
// if(br=='n'){
//     cout<<"nombre: ";cin>>name;
//     m_branches.push_back(name);
// }
// else{
// cout<<"select branch: ";cin>>name;
// if(find_branch(name)==true)
//    find_(name,tmp);
// else{
//     cout<<"no existe branch\n";    
//     return false;
//     }
// }

if(m_nodes.size()==0){
    data_before=cfile.read_file(file);
    insert_node(data_before,name);
    lenght=data_before.size();
    tmp=m_nodes.back();
}
else{
    find_(name,tmp);
    tmp2= tmp;
    find_last(tmp);
    data_before=consult(tmp2,tmp);
    cout<<"data_b: "<<data_before;
    lenght=data_before.size();
    }   
 
    int aux=lenght;
    while(aux==lenght){
        // cout<<"modifique"<<endl;
        data_after=cfile.read_file(file);
        aux=data_after.size();
        // cout<<"aux: "<<aux<<endl;
        // cout<<"len:"<<lenght<<endl;
    }
    bool op=cfile.get_change(data_before, data_after);
    // cout<<"after:   "<<data_after<<endl;
    insert_node(data_after,name);     
    insert_edge("t"+to_string(m_nodes.size()-1),
    m_nodes[m_nodes.size()-2]->m_data,
    m_nodes.back()->m_data,op);
    // m_times.push_back(new Pers(m_edges.back(),op));
    
    return true;


}

template<class Tr>
bool CGraph<Tr>::remove(string t){


}

template<class Tr>
bool CGraph<Tr>::restore(string data){
// Edge* tmp=nullptr;
// Edge* nodo=m_nodes.back();

// for(int i=0; i<m_edges.size(); i++)
//     if(m_edges[i]->m_data==data)
//             tmp=m_edges[i];

// while (nodo!= tmp){
//     m_rpta+=nodo->m_data;
//     int length= nodo->m_nedges.size();
//     for(int i=0;i<length;i++){
//         if(nodo == nodo->m_nedges[i]->m_node[0] ){
//             nodo = nodo->m_nedges[i]->m_node[1];
//         }
//     }
// }



}

template <class Tr>
bool CGraph<Tr>::find_branch(N data){
    for(int i=0; i<m_branches.size(); i++)
        if(m_branches[i]==data){
            return 1;
        }
    return 0;
}
template <class Tr>
bool CGraph<Tr>::find_N(N data){
    Node* tmp;
    if(!find_node(data, tmp))
        return 0;
    return 1;
}
template <class Tr>
bool CGraph<Tr>::find_E(E data){
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
bool CGraph<Tr>::insert_node(N _data, N _branch){
    Node* new_node=new Node(_data,_branch);
    m_nodes.push_back(new_node);
    return 1;
}

template <class Tr>
bool CGraph<Tr>::insert_edge(E _data,N a,N b,bool op){
    Node* Nodea,* Nodeb;
    if(!find_node(a, Nodea) or !find_node(b, Nodeb))    return 0;
    Edge* new_edge=new Edge(_data, Nodea, Nodeb,op);
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
bool CGraph<Tr>::find_(N branch, Node* &tmp){
    tmp =m_nodes.front();
    stack<Node*> m_stack;
    Node* aux =nullptr;
    while (tmp->m_branch != branch){
        int length=tmp->m_nedges.size();
        if(length>2) m_stack.push(tmp);
        for(int i=0;i<length;i++){
            if(tmp == tmp->m_nedges[i]->m_node[0] ){
                tmp = tmp->m_nedges[i]->m_node[1];break;
            }
        }
        if(length==1){
            while(!m_stack.empty()){
                tmp =m_stack.top();
                int i=2,j=i;
                while(i<tmp->m_nedges.size()){
                    aux=tmp;
                    while(aux->m_nedges.size()>1){
                        if(aux==aux->m_nedges[i]->m_node[0]){
                            aux=aux->m_nedges[i]->m_node[1];
                            if(aux->m_branch==branch){
                            tmp=aux;
                            return true;
                            } 
                                
                            else{
                                if(aux->m_nedges.size()>2)
                                m_stack.push(aux);
                            i=0;
                            }
                        }
                    }
                    i=j++;
            }
            m_stack.pop();
            } 
        return false;
        }
    }
    return true;
}

template<class Tr>
void CGraph<Tr>::find_last(Node* &tmp){
    string branch=tmp->m_branch;
    while(tmp->m_nedges.size()>1  or tmp==m_nodes.front()){
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp==tmp->m_nedges[i]->m_node[0] and 
            tmp->m_nedges[i]->m_node[1]->m_branch==branch)
                tmp=tmp->m_nedges[i]->m_node[1];
        }
    } 
    
}


#endif //CGRAPH_H