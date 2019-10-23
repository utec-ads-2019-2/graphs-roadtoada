#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>
#include <iterator>
#include "node.h"
#include "edge.h"

using namespace std;


class airport;


template <typename G>
class Graph {
  float dense[2]={0,1};
public:
    typedef class Node<G*> node;
    map<string,Node<G>*> nodes;

    void addNode(G data){
      dense[1]=0;
      if(!nodes[data->id])
        nodes[data->id]=new Node<G>(data);
      else{
        nodes[data->id]->data=data;
        for(auto i=nodes.begin();i!=nodes.end();i++){
            auto a=findEdge(i->first,data->id);
            if(a!=nullptr)
              a->set_data();
        }
      }
      for(auto i:data->destinos)
      {
        if(!nodes[i])
          nodes[i]=new Node<G>(nullptr);
        addEdge(data->id,i);
        if(nodes[i]->data!=nullptr){
          nodes[data->id]->edges[i]->set_data();


        }
        }
    }

    void addEdge(string from, string to){
      if(nodes[from]!=0 && nodes[to]!=0){
        nodes[from]->edges[to]=(new Edge<G>(nodes[from],nodes[to]));
        dense[1]=0;
      }
    }

    Node<G>* findNode(string id){
        return nodes[id];
    }

    Edge<G>* findEdge(string from, string to){
        if(nodes[from]!=0 && nodes[to]!=0)
          if(nodes[from]->edges[to] != 0)
            return nodes[from]->edges[to];
        else
          nodes[from]->edges.erase(to);
        return nullptr;
    }

    void removeEdge(string from,string to){
      if(findEdge(from,to)!=0){
        dense[1]=0;
        delete nodes[from]->edges[to];
        nodes[from]->edges.erase(to);
      }
    }

    void removeNode(string id){
      if (nodes[id]!=0){
        dense[1]=0;
        for(auto it=nodes.begin();it!=nodes.end();++it){
          removeEdge(it->first,id);
        }
      }
      nodes.erase(id);
    }

    void imprimir(){
      for(auto i=nodes.begin();i!=nodes.end();++i){
        cout<<"El id: "<<i->first<<endl;
        cout<<"Aristas"<<endl;
        nodes[i->first]->print_edges();
        // i->second->print_edges();
        cout<<endl;
      }
    }

    float densidad(){
      float margin=0.5;
      if(!dense[1]){
        float aristas=0;
        dense[0]=0;
        float vertices=nodes.size();
        for(auto it=nodes.begin();it!=nodes.end();++it){
          aristas+=it->second->edges.size();
        }
        dense[0]=aristas/(vertices*(vertices-1));
      }
      if(dense[0]>=margin)
        cout<<"Grafo es denso"<<endl;
      else
        cout<<"Grafo es disperso"<<endl;
      return dense[0];
    }

    void prim(string id){
      auto inicio=nodes[id];
      vector<node> recorridos;
      recorridos.push_back(inicio);
      while(recorridos.size()!=nodes.size()){
        while(true){
          for(auto i:recorridos){
          }
        }

      }

/*
  void deepen(Node<G>* &nodo, map<<Node<G>*>,bool> &nodos){
    for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++)

  }

    bool conexo(){
      map<<Node<G>*>,bool> temp={};
      for(auto it=nodes.begin();it!=nodes.end();++it){
        temp[it->second];
      }
      for(auto it=temp.begin();it!=temp.end();++it){
      }
    }
*/
};

#endif
