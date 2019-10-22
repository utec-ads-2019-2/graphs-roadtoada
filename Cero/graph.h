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
public:
    map<string,Node<G>*> nodes;

    void addNode(G data){
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
      if(nodes[from]!=0 && nodes[to]!=0)
        nodes[from]->edges[to]=(new Edge<G>(nodes[from],nodes[to]));
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
        delete nodes[from]->edges[to];
        nodes[from]->edges.erase(to);
      }
    }

    void removeNode(string id){
      if (nodes[id]!=0){
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
};


#endif
