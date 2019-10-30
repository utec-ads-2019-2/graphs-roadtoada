#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
#include "node.h"

using namespace std;


class airport;


template <typename G>
class Graph {
  float dense[2]={0,1};

public:
    bool dirigido=0;
    typedef class Node<G*> node;
    map<string,Node<G>*> nodes;

    ~Graph(){
      for(auto aux=nodes.begin();aux!=nodes.end();aux++)
      {
        removeNode(aux->first);
      }

    }

    void nedges(){
      int aristas=0;
      for(auto it=nodes.begin();it!=nodes.end();++it){
        aristas+=it->second->edges.size();
      }
      cout<<aristas<<endl;
    }
    void addNode(G data){
      dense[1]=0;
      if(!nodes[data->id])
        nodes[data->id]=new Node<G>(data);
      else{
        nodes[data->id]->data=data;
      }

    }


    void addEdge(string from, string to){
      if(nodes[from]!=0 && nodes[to]!=0){
        auto aux=new Edge<G>(nodes[from],nodes[to]);
        nodes[from]->edges[to]=(aux);
        if(nodes[from]->data!=0 && nodes[to]->data!=0)
          aux->set_data();

        dense[1]=0;
      }
    }

    Node<G>* findNode(string id){
        if(nodes[id]!=nullptr)
          return nodes[id];
        else
          nodes.erase(id);
        return nullptr;
    }

    Edge<G>* findEdge(string from, string to){
        if(nodes[from]!=0 && nodes[to]!=0){
          if(nodes[from]->edges[to] != 0)
            return nodes[from]->edges[to];
          else
            nodes[from]->edges.erase(to);
        }
        if(nodes[from]==0)
          nodes.erase(from);
        if(nodes[to]==0)
          nodes.erase(to);
        return nullptr;
    }

    void removeEdge(string from,string to){
      if(findEdge(from,to)!=0){
        dense[1]=0;
        delete nodes[from]->edges[to];
        nodes[from]->edges.erase(to);
      }
      if(findEdge(to,from)!=0){
        dense[1]=0;
        delete nodes[to]->edges[from];
        nodes[to]->edges.erase(from);
      }
    }

    void removeNode(string id){
      if (nodes[id]!=0){
        dense[1]=0;
        for(auto it=nodes.begin();it!=nodes.end();++it){
          removeEdge(it->first,id);
        }
      }
      delete nodes[id];
      nodes.erase(id);
    }

    void imprimir(){
      for(auto i=nodes.begin();i!=nodes.end();++i){
        cout<<"El id: "<<i->first<<endl;
        cout<<"Aristas"<<endl;
        i->second->print_edges();
        cout<<endl;
      }
    }


    Graph<G> prim(string id){
      if(dirigido | !conexo()){
      cout<<"NO ES DIRIGIDO Y CONEXO"<<endl;
      throw exception();
      }
      Graph<G> prim;
      std::vector<Edge<G>*> edges;
      map<string,Node<G>*> nod;
      vector<Node<G>*>prueba;
      prueba.push_back(nodes[id]);
      auto inicio=*(nodes[id]->data);
      // inicio.destinos.clear();
      nod[id]=new Node<G>(&inicio);
      while(prueba.size()!=nodes.size()){
        auto aux=menor_arista_nodos(prueba);
        if(aux==nullptr){
          cout<<"F"<<endl;
          break;
        }
        // cout<<aux->nodes[0]->data->id<<" "<<aux->nodes[1]->data->id<<" "<aux->data<<endl;
        edges.push_back(aux);
        prueba.push_back(aux->nodes[1]);
        auto guardar=*(aux->nodes[1]->data);
        nod[aux->nodes[1]->data->id]=new Node<G>(&guardar);
      }

      for(auto aux:edges){
        nod[aux->nodes[0]->data->id]->edges[aux->nodes[1]->data->id]=aux;
        auto reversa=new Edge<G>(aux->nodes[1],aux->nodes[0]);
        reversa->set_data();
        nod[aux->nodes[1]->data->id]->edges[aux->nodes[0]->data->id]=reversa;
      }
      prim.nodes=nod;
      return prim;
    }

    Edge<G>* menor_arista_nodos(vector<Node<G>*> recorridos){
      double minimo=2147483647;
      Edge<G>* arista=nullptr;
      for(auto i:recorridos){
        for(auto j=i->edges.begin();j!=i->edges.end();++j){
          if(j->second->data<=minimo && (find(recorridos.begin(), recorridos.end(), j->second->nodes[1]) == recorridos.end()))
          {
            minimo=j->second->data;
            arista=j->second;
          }
        }
      }
      return arista;

    }

    Graph<G> kruskal(){
      if(dirigido | !conexo()){
      cout<<"NO ES DIRIGIDO Y CONEXO"<<endl;
      throw exception();
      }
      Graph<G> kruskal;
      map<string,Node<G>*>  nod;
      double minimo=0;
      int nodos=0;
      vector<vector<Node<G>*>>recorridos;
      vector<Edge<G>*>recorridas;
      vector<Edge<G>*>edges_kruskal;
      vector<Node<G>*>nodes_kruskal;
      while(nodes.size()!=(edges_kruskal.size()/2)+1){
        auto edge=siguiente_menor(minimo,recorridas);
        // if(edge==nullptr)
        recorridas.push_back(edge);
        recorridas.push_back(findEdge(edge->nodes[1]->data->id,edge->nodes[0]->data->id));
        Node<G>* inicio=nullptr;
        int i1,i2,j1,j2;
        Node<G>*  fin=nullptr;
        for(int i=0;i<recorridos.size();i++)
        {
          for(int j=0;j<recorridos[i].size();j++)
          {
            if(recorridos[i][j]->data->id==edge->nodes[0]->data->id){
              inicio=edge->nodes[0];
              i1=i;
            }

            if(recorridos[i][j]->data->id==edge->nodes[1]->data->id){
              fin=edge->nodes[1];
              i2=i;
            }
          }
        }
        if(inicio==nullptr && fin==nullptr)
        {
                  cout<<edge->nodes[0]->data->id<<" "<<edge->nodes[1]->data->id<<" "<<edge->data<<endl;
          vector<Node<G>*> n;
          n.push_back(edge->nodes[0]);
          n.push_back(edge->nodes[1]);
          recorridos.push_back(n);
          edges_kruskal.push_back(findEdge(edge->nodes[1]->data->id,edge->nodes[0]->data->id));
          edges_kruskal.push_back(edge);
          nodos+=2;
          nodes_kruskal.push_back(edge->nodes[0]);
          nodes_kruskal.push_back(edge->nodes[1]);
        }
        else if(inicio!=nullptr && fin!=nullptr)
        {

          if(i1!=i2)
            {
                                cout<<edge->nodes[0]->data->id<<" "<<edge->nodes[1]->data->id<<" "<<edge->data<<endl;
                for(int i=0;i<recorridos[i2].size();i++)
                {
                  recorridos[i1].push_back(recorridos[i2][i]);
                }
                recorridos[i2].clear();
                edges_kruskal.push_back(findEdge(edge->nodes[1]->data->id,edge->nodes[0]->data->id));
                edges_kruskal.push_back(edge);
            }
        }
        else if(inicio!=nullptr && fin==nullptr)
        {
                            cout<<edge->nodes[0]->data->id<<" "<<edge->nodes[1]->data->id<<" "<<edge->data<<endl;
          recorridos[i1].push_back(edge->nodes[1]);
          recorridos[i1].push_back(edge->nodes[0]);
          edges_kruskal.push_back(findEdge(edge->nodes[1]->data->id,edge->nodes[0]->data->id));
          edges_kruskal.push_back(edge);
          nodos++;
          nodes_kruskal.push_back(edge->nodes[1]);
        }
        else if(inicio==nullptr && fin!=nullptr)
        {
                            cout<<edge->nodes[0]->data->id<<" "<<edge->nodes[1]->data->id<<" "<<edge->data<<endl;
          recorridos[i2].push_back(edge->nodes[0]);
          recorridos[i2].push_back(edge->nodes[1]);
          edges_kruskal.push_back(findEdge(edge->nodes[1]->data->id,edge->nodes[0]->data->id));
          edges_kruskal.push_back(edge);
          nodos++;
          nodes_kruskal.push_back(edge->nodes[0]);
        }
      }
      for(auto i:edges_kruskal){

      }
      for(int t=0;t<nodes_kruskal.size();t++){
        auto ag=*(nodes_kruskal[t]->data);
        nod[nodes_kruskal[t]->data->id]=new Node<G>(&ag);
      }
      for(auto aux:edges_kruskal){
        nod[aux->nodes[0]->data->id]->edges[aux->nodes[1]->data->id]=aux;
        auto reversa=new Edge<G>(aux->nodes[1],aux->nodes[0]);
        reversa->set_data();
        nod[aux->nodes[1]->data->id]->edges[aux->nodes[0]->data->id]=reversa;
      }
      kruskal.nodes=nod;

      return kruskal;

    }

    Edge<G>* siguiente_menor(double n,vector<Edge<G>*> recorridas){
      double a=2147483647;
      Edge<G>* edge;
      for(auto i=nodes.begin();i!=nodes.end();++i)
      {
          for(auto j=i->second->edges.begin();j!=i->second->edges.end();++j)
          {
            if(a>j->second->data && j->second->data>=n && find(recorridas.begin(),recorridas.end(),j->second)==recorridas.end()){
              a=j->second->data;
              edge=j->second;
            }
          }
      }
      return edge;
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
    for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++){
      if(nodos[it->second->nodes[1]]==!status){
        return false;
      }
      if(nodos[it->second->nodes[1]]==-1){
        nodos[it->second->nodes[1]]=status;
      }
    }
    for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++){
      for(auto it2=it->second->nodes[1]->edges.begin();it2!=it->second->nodes[1]->edges.end();it2++){
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
      if(!coloreo(it->first,temp,0)){
        return false;
      };
      while(it!=temp.end()){
        if(it->second==-1){
          temp[it->first]=1;
          if(!coloreo(it->first,temp,0)){
            return false;
          }
        }
        it++;
      }



      return(true);
  }

};

#endif
