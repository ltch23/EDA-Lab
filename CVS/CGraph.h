#ifndef CGRAPH_H
#define CGRAPH_H

#include "CNode.h"
#include "CEdge.h"
#include "CFile.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <list>
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
    int lenght=0;

    bool insert_node(N,N);
    bool insert_edge(E,N,N,bool);
    bool remove_edge(E,N,N);
    bool remove_node(N);
    bool remove_branch(N);
    
    bool find_N(N);
    bool find_E(E);
    bool find_node(N, Node* &);
    bool find_node_b(N, Node* &);
    bool find_edge(E,Edge* &);
    bool find_last(Node*&);
    bool find_branch(N data);
    bool find_(N,Node*&);
    
    bool consult(string);
    string read(Node*, Node*);
    string read2(list<Node*>);

    bool get_path1(Node*,list<Node*>&);
    bool get_path2(Node*&,list<Node*>&);
    bool get_path3(Node*,list<Node*>&);
    
    bool insert(char, string, string, string);
    bool remove(string);
    bool restore(string);
    bool merge(string);
    
    void print();
    void draw_graph();

};

template<class Tr>
void CGraph<Tr>::draw_graph(){
    ofstream file ("graph.dot");
    file<<"digraph G{\n" ;
    
    for(int i=0; i<m_edges.size(); i++){
    // file<<m_edges[i]->m_node[0]->m_data<<": ";
    file<<m_edges[i]->m_node[0]->m_data+" -> ";
    if(m_edges[i]->m_status==true)
        file<<m_edges[i]->m_node[1]->m_data+"[label=\"";
    else if(m_edges[i]->m_status==false)
        file<<m_edges[i]->m_node[1]->m_data+"[color=red,label=\"";
    
    file<<m_edges[i]->m_data+"-"+m_edges[i]->m_node[1]->m_branch+"\"];\n";
    
    }
    file<<"}\n";
    file.close();
    system("dot graph.dot -Tpng -o graph.png");
}

template<class Tr>
void CGraph<Tr>::print(){
    cout<<"----------------Grafo----------------"<<endl;
    cout<<"Nodos:\n";
    for(int i=0; i<m_nodes.size();i++){
        cout<<m_nodes[i]->m_data<<" ";
        cout<<m_nodes[i]->m_branch<<"\n";
    }
    cout<<endl;
    draw_graph();
    cout<<"\nAristas:"<<endl;
        for(int i=0; i<m_edges.size(); i++){
        cout<<m_edges[i]->m_node[0]->m_data<<": ";
        cout<<m_edges[i]->m_node[0]->m_branch;
        cout<<" - "<<m_edges[i]->m_data<<" = ";
        cout<<m_edges[i]->m_status;
        cout<<" -> "<<m_edges[i]->m_node[1]->m_data<<": ";
        cout<<m_edges[i]->m_node[1]->m_branch<<endl;
        }
    cout<<"\nRamas:"<<endl;
       for (int i=0; i<m_branches.size();i++)
            cout<<m_branches[i]<<" ";
        cout<<endl;

}

template<class Tr>
bool CGraph<Tr>::get_path1(Node* node,list<Node*>& lista){
    lista.clear();
    Node* tmp=node;
    while (tmp!=m_nodes.front()) {
        lista.push_front(tmp);
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp== tmp->m_nedges[i]->m_node[1])
                tmp=tmp->m_nedges[i]->m_node[0];
        }
    }
    lista.push_front(tmp);
}

template<class Tr>
bool CGraph<Tr>::get_path3(Node* node,list<Node*>& lista){
    lista.clear();
    Node* tmp=node;
    while (tmp!=m_nodes.front()) {
        lista.push_front(tmp);
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp== tmp->m_nedges[i]->m_node[1]){
                tmp->m_nedges[i]->m_status=false;
                tmp=tmp->m_nedges[i]->m_node[0];
            }
        }
    }
    lista.push_front(tmp);
}
template<class Tr>
bool CGraph<Tr>::get_path2(Node* &node,list<Node*>& lista){
    lista.clear();
    Node* tmp=node;
    while (tmp!=m_nodes.front()) {
        lista.push_front(tmp);
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp== tmp->m_nedges[i]->m_node[1])
                tmp=tmp->m_nedges[i]->m_node[0];
        }
    }
    lista.push_front(tmp);

    string branch=node->m_branch;
    if(m_nodes.size()==1)
    return true;
    while(node->m_nedges.size()>1 or node==m_nodes.front() ){
        for(int i=0;i<node->m_nedges.size();i++){
            if(node==node->m_nedges[i]->m_node[0] and 
                node->m_nedges[i]->m_node[1]->m_branch==branch and
                node->m_nedges[i]->m_status==true){
                // if(node->m_nedges[i]->m_status==false)
                    // return true;
                node=node->m_nedges[i]->m_node[1];
                lista.push_back(node);
                }

            else if(i == node->m_nedges.size()-1)
                return true;
            // }
           }
            
    }
    // lista.push_back(node);
    return true;
}


template<class Tr>
string CGraph<Tr>::read2(list<Node*> lista){
    string rpta="";
    Node* tmp=nullptr;
    while(!lista.empty()){
        tmp=lista.front();
        // cout<<tmp->m_data<<endl;
        rpta+=tmp->m_data;
        lista.pop_front();
    }
    cout<<rpta<<endl;
    return rpta;
}

template<class Tr>
string CGraph<Tr>::read(Node* begin, Node* last){
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
bool CGraph<Tr>::consult(string pos){

    string data_tmp="";
    Node* tmp=nullptr;
    Edge* edge=nullptr;
    list<Node*> lista;
    lista.clear();

    find_edge(pos,edge);
    tmp=edge->m_node[1];
    
    get_path1(tmp,lista);
        
    data_tmp=read2(lista);
    cfile.save_file(file,data_tmp);

}

template<class Tr>
bool CGraph<Tr>::insert(char br, string _branch, string pos, string _data){
    string data_before="";
    string data_tmp="";
    Node* tmp=nullptr;
    Edge* edge=nullptr;
    list<Node*> lista;
    lista.clear();

    if(m_nodes.size()==0){
        cout<<"create branch\n";
        m_branches.push_back(_branch);
        insert_node(_data,_branch);
    }
    else{
        if(br== 'n'){
            m_branches.push_back(_branch);
            find_edge(pos,edge);
            tmp=edge->m_node[1];
            get_path1(tmp,lista);
        }
        else if(br== 's'){
            find_node_b(_branch,tmp);   
            get_path2(tmp,lista);
        }
        
        data_before=read2(lista);
        cfile.save_file(file,data_before);
        
    bool op=cfile.get_change(data_before, _data);
    insert_node(_data, _branch);     
    insert_edge("t"+to_string(lenght-1),
    tmp->m_data, m_nodes.back()->m_data,op);
    }
    tmp=nullptr;

    return true;
}

template<class Tr>
bool CGraph<Tr>::remove(string pos){
    string data_before="";
    Node *tmp=nullptr;
    Node *tmp2=nullptr;
    Node *begin=nullptr;

    Edge *edge=nullptr;
    vector<Node*> m_stack;
    stack<Node*> stack_tmp;
    stack<Node*> m_clear;
    
    find_edge(pos,edge);
    
    tmp=edge->m_node[1];
    
    while(tmp->m_nedges.size()>1  or tmp==m_nodes.front()){
        m_stack.push_back(tmp);
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp->m_nedges.size()>2) stack_tmp.push(tmp);
            if(tmp==tmp->m_nedges[i]->m_node[0])
                tmp=tmp->m_nedges[i]->m_node[1];
            }
        }
    m_stack.push_back(tmp);

    while(!stack_tmp.empty()){
        tmp=stack_tmp.top();
        int size=tmp->m_nedges.size();
        for(int i=0;i<size;i++){
            if(tmp==tmp->m_nedges[i]->m_node[0] ){
                tmp2=tmp->m_nedges[i]->m_node[1];
                int size2=tmp2->m_nedges.size();      
                while(size2>1){
                m_stack.push_back(tmp2);
                    for(int j=0;j<size2;j++){
                        // if(size2>2){ stack_tmp.push(tmp2);}
                        if(tmp2==tmp2->m_nedges[j]->m_node[0] ){
                            tmp2=tmp2->m_nedges[j]->m_node[1];
                            j=size2-1;
                            }
                        }
                        size2=tmp2->m_nedges.size();      
                }
                m_stack.push_back(tmp2);
             
             }
        }
        stack_tmp.pop();
    }
    

    for(int i=0;i<m_stack.size();i++)
        for(int j=i+1;j<m_stack.size();j++)
            if(m_stack[i]->m_data==m_stack[j]->m_data)
                m_stack.erase(m_stack.begin()+j);

        while(!m_stack.empty()){
            tmp =m_stack.back();
            remove_branch(tmp->m_branch);    
            // cout<<tmp->m_data<<"\n";
            remove_node(tmp->m_data);
            m_stack.pop_back();
        }
        
    return true;
}

template<class Tr>
bool CGraph<Tr>::restore(string pos){
    cout<<"RESTORE"<<endl;
    string data_before="";
    int posi=stoi(pos.erase(0,1));
    cout<<posi<<endl;
    cout <<m_edges.size()<<endl;
    for(int i=posi; i<m_edges.size();i++){
        cout<<"data: "<<m_edges[i]->m_data<<" ";
        cout<<m_edges[i]->m_data<<" ";
        if(m_edges[i]->m_data=="t"+to_string(i+1)){
            m_edges[i]->m_status= not m_edges[i]->m_status;
        //    m_edges[i]->m_status= false;
        }   
    }
    cout<<endl;

    return true;
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
bool CGraph<Tr>::remove_branch(N data){
    for(int i=0; i<m_branches.size(); i++)
        if(m_branches[i]==data){
            m_branches[i]="";
            return 1;
        }
    return 0;
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
        return false;
        }
    }
    return true;
}

template<class Tr>
bool CGraph<Tr>::find_last(Node* &tmp){
    string branch=tmp->m_branch;
    // cout<<"find_last: "<<endl;
    while(tmp->m_nedges.size()>1  or tmp==m_nodes.front()){
        for(int i=0;i<tmp->m_nedges.size();i++){
            if(tmp==tmp->m_nedges[i]->m_node[0] and 
            tmp->m_nedges[i]->m_node[1]->m_branch==branch)
                tmp=tmp->m_nedges[i]->m_node[1];
            else if(i == i<tmp->m_nedges.size() and
                tmp==tmp->m_nedges[i]->m_node[0] and 
                tmp->m_nedges[i]->m_node[1]->m_branch!=branch)
                return true;
           }
    }
    // cout<<"data last: "<<tmp->m_data<<endl; 
    return true;
}



template <class Tr>
bool CGraph<Tr>::insert_node(N _data, N _branch){
    Node* new_node=new Node(_data,_branch);
    m_nodes.push_back(new_node);
    lenght++;
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
    Node* delete_node=nullptr;
    for(int i=0; i<m_nodes.size(); i++){
        if(m_nodes[i]->m_data == _data){
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


#endif //CGRAPH_H