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
    }

    
void deepen(Node<G>* nodo, map<Node<G>* ,bool> &nodos){
    nodos[nodo]=1;
    for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++){
      nodos[it->second->nodes[1]]=1;
    }
    for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++){
      for(auto it2=it->second->nodes[1]->edges.begin();it2!=it->second->nodes[1]->edges.end();it2++){
        if(nodos[it2->second->nodes[1]]==0){
          (deepen(it2->second->nodes[1],nodos));
        }
      }
    }
    return;
  }

    bool conexo(){
      map<Node<G>*,bool> temp={};
      for(auto it=nodes.begin();it!=nodes.end();++it){
        temp[it->second];
      }
      for(auto it=temp.begin();it!=temp.end();++it){
        //cout<<"ANALYZING "<<it->first->data->id<<endl;
        deepen(it->first,temp);
        for(auto it2=temp.begin();it2!=temp.end();++it2){
          if(it2->second==0)
            return false;
        }
        for(auto it2=temp.begin();it2!=temp.end();++it2){
          it2->second=0;
        }
      }
      return true;
  }




bool coloreo(Node<G>* nodo, map<Node<G>* ,int> &nodos, int status){
    cout<<"Status para adyacentes a nodo "<<nodo->data->id<<" es "<<status<<endl;
    for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++){
      if(nodos[it->second->nodes[1]]==!status){
        cout<<"Returning false on "<<it->second->nodes[1]->data->id<<endl;
        return false;
      }
      if(nodos[it->second->nodes[1]]==-1){
        nodos[it->second->nodes[1]]=status;
      }
    }
    for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++){
      for(auto it2=it->second->nodes[1]->edges.begin();it2!=it->second->nodes[1]->edges.end();it2++){
        cout<<"Comprobando si colorear adyacentes "<<nodos[it2->second->nodes[1]]<<endl;
        if(nodos[it2->second->nodes[1]]==status){
          return false;
        }
        if(nodos[it2->second->nodes[1]]==-1){
          if(coloreo(it->second->nodes[1],nodos,!status))
            break;
          else
            return false;
        }
      }
    }
    return true;
  }

  bool bipartito(){
      map<Node<G>*,int> temp={};
      for(auto it=nodes.begin();it!=nodes.end();++it){
        temp[it->second]=-1;
      }
      auto it=temp.begin();
      temp[it->first]=1;
      return(coloreo(it->first,temp,0));
  }

};

#endif
