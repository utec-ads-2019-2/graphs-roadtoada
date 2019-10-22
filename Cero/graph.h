#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>
#include <iterator>
#include "node.h"
#include "edge.h"

using namespace std;

template <typename G>
class Graph {
  float dense[2]={0,1};
public:
    map<string,Node<G>*> nodes;

    void addNode(G data){
      dense[1]=0;
      if(!nodes[data->id])
        nodes[data->id]=new Node<G>(data);
      else
        nodes[data->id]->data=data;
      for(auto i:data->destinos)
      {
        if(!nodes[i])
          nodes[i]=new Node<G>();
        addEdge(data->id,i);
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
/*
    bool conexo(){
      vector<Node<G>*> temp={};
      for(auto it=nodes.begin();it!=nodes.end();++it){
        temp.push_back(it->second);
      }
      for(auto it=nodes.begin();it!=nodes.end();++it){
        it->second
      }
    }
*/
};

#endif
