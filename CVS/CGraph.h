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
    bool find_node_b(N, Node* &);
    bool find_edge(E,Edge* &);
    void find_last(Node*&);
    bool find_branch(N data);
    string consult(Node*, Node*);
    bool insert();
    bool remove();
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
        cout<<m_edges[i]->m_node[0]->m_data<<": ";
        cout<<m_edges[i]->m_node[0]->m_branch;
        cout<<" - "<<m_edges[i]->m_data;
        cout<<" -> "<<m_edges[i]->m_node[1]->m_data<<": ";
        cout<<m_edges[i]->m_node[1]->m_branch<<endl;
        }

    cout<<"\nRamas:"<<endl;
       for (int i=0; i<m_branches.size();i++)
            cout<<m_branches[i]<<" ";
        cout<<endl;
    // cout<<endl;

}
template<class Tr>
string CGraph<Tr>::consult(Node* begin, Node* last){
    cout<<"inicio: "<<begin->m_data<<"\t";
    cout<<"fin: "<<last->m_data<<"\n";
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
string data_before="";
string data_after="" ;
string data_tmp="";
Node* tmp=nullptr;
Node* tmp2=nullptr;
Edge* edge=nullptr;
int lenght;
char br; string name,pos;
cout<<"INSERT\n";

if(m_nodes.size()==0){
    cout<<"create branch: ";cin>>name;
    m_branches.push_back(name);
    data_before=cfile.read_file(file);
    insert_node(data_before,name);
    lenght=data_before.size();
    tmp=m_nodes.back();
}
else{
    cout<<"nuevo branch 'n' | select branch 's': ";cin>>br;
    if(br=='n'){
        cout<<"branch: ";cin>>name;
        cout<<"tiempo: "; cin>>pos;
        m_branches.push_back(name);
        find_edge(pos,edge);
        tmp2=m_nodes.front();
        tmp=edge->m_node[1];
    }
    else if(br=='s'){
        cout<<"branch: ";cin>>name;
        //find_branch(name);
        find_node_b(name,tmp);
        tmp2= tmp;
        find_last(tmp);
        data_tmp="";

        if(name!=m_branches.front()){
            cout<<"entro\n";
            data_tmp=consult(m_nodes.front(),tmp2->m_nedges[0]->m_node[0]);
        }
    }
    
    data_before=data_tmp+consult(tmp2,tmp);
    cfile.save_file(file,data_before);
    // return cfile.read_file(file);
    cout<<"data_b: "<<data_before<<endl;
    lenght=data_before.size();
    }   
    int aux=lenght;
    while(aux==lenght){
        data_after= cfile.read_file(file);
        aux=data_after.size();
    }
    bool op=cfile.get_change(data_before, data_after);
    insert_node(data_after,name);     
    insert_edge("t"+to_string(m_nodes.size()-1),
    tmp->m_data, m_nodes.back()->m_data,op);
    // m_edges.front()->print();
    
    tmp=nullptr;
    tmp2=nullptr;

    return true;


}

template<class Tr>
bool CGraph<Tr>::remove(){
string pos="",data_before="";
Node *tmp=nullptr;
Node *begin=nullptr;

Edge *edge=nullptr;
stack<Node*> m_stack;

cout<<"tiempo: "; cin>>pos;
find_edge(pos,edge);
tmp=edge->m_node[1];
cout<<"data: "<<tmp->m_data<<endl;
begin=edge->m_node[0];
m_stack.push(tmp);
while(tmp->m_nedges.size()>1  or tmp==m_nodes.front()){
        cout<<"entre\n";
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp==tmp->m_nedges[i]->m_node[0] ){
                tmp=tmp->m_nedges[i]->m_node[1];
                m_stack.push(tmp);
            }
        }
    }

    while(!m_stack.empty()){
        tmp =m_stack.top();
        remove_node(tmp->m_data);
        m_stack.pop();
    }

    data_before=consult(m_nodes.front(),begin);
    cfile.save_file(file,data_before);
    cout<<"data: "<<data_before<<endl;
    return true;
    
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
bool CGraph<Tr>::find_node_b(N data, Node* &tmp){
    for(int i=0; i<m_nodes.size(); i++)
        if(m_nodes[i]->m_branch==data){
            tmp=(m_nodes[i]);
            return 1;
        }
    return 0;
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
    cout<<"branch: "<<branch<<endl;
    tmp =m_nodes.front();
    stack<Node*> m_stack;
    Node* aux =nullptr;
    int length=tmp->m_nedges.size();
    // while (length>1){
    while (tmp->m_branch!= branch){
            if(length>2) m_stack.push(tmp);
        for(int i=0;i<length;i++){
            if(tmp == tmp->m_nedges[i]->m_node[0]  and
                tmp->m_nedges[i]->m_node[1]->m_branch == branch){
                tmp = tmp->m_nedges[i]->m_node[1];break;
            }
        }
        if(tmp!= m_nodes.front() and length!=1){
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
                            cout<<"data find "<<tmp->m_data<<endl;
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
        cout<<"no find"<<endl;
        return false;
        }
    }
    cout<<"data find "<<tmp->m_data<<endl;
    return true;
}

template<class Tr>
void CGraph<Tr>::find_last(Node* &tmp){

    string branch=tmp->m_branch;
    cout<<"branch: "<<branch<<endl;
    while(tmp->m_nedges.size()>1  or tmp==m_nodes.front()){
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp==tmp->m_nedges[i]->m_node[0] and 
            tmp->m_nedges[i]->m_node[1]->m_branch==branch)
                tmp=tmp->m_nedges[i]->m_node[1];
        }
    }
    cout<<"data last: "<<tmp->m_data<<endl; 
     
    
}


#endif //CGRAPH_H