#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
#include <queue>
#include "node.h"
using namespace std;


class airport;
class example;



template <typename G>
class Graph {
  float dense[2]={0,1};
  typedef class Node<G>* node;
  typedef class Edge<G>* edge;

private:
  void deepen(node nodo, map<node ,bool> &nodos){
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

  edge siguiente_menor(double n,vector<edge> recorridas){
    double a=2147483647;
    edge edge;
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

  edge menor_arista_nodos(vector<node> recorridos){
    double minimo=2147483647;
    edge arista=nullptr;
    for(auto i:recorridos){
      for(auto j=i->edges.begin();j!=i->edges.end();++j){
        if(j->second->data<=minimo && (find(recorridos.begin(), recorridos.end(), j->second->nodes[1]) == recorridos.end())){
          minimo=j->second->data;
          arista=j->second;
        }
      }
    }
    return arista;
  }

  bool coloreo(node nodo, map<node ,int> &nodos, int status){
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

  void DFSLoop(node nodo, map<node ,node> &nodos, map<node,bool> &checker){
      for(auto it=nodo->edges.begin();it!=nodo->edges.end();it++){
        if(checker[it->second->nodes[1]])
          continue;
        checker[it->second->nodes[1]]=1;
        nodos[it->second->nodes[1]]=nodo;
        DFSLoop(it->second->nodes[1], nodos, checker);
      }
    return;
  }

  
public:
  bool dirigido=0;
  map<string,node> nodes;

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

  node findNode(string id){
      if(nodes[id]!=nullptr)
        return nodes[id];
      else
        nodes.erase(id);
      return nullptr;
  }

  edge findEdge(string from, string to){
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
  };

  void addEdge(string from, string to,float valor){
    if(nodes[from]!=0 && nodes[to]!=0){
      auto aux=new Edge<G>(nodes[from],nodes[to],valor);
      nodes[from]->edges[to]=(aux);
      if(nodes[from]->data!=0 && nodes[to]->data!=0)
        aux->set_data(valor);

      dense[1]=0;
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

  void removeEdge(string from,string to){
      if(findEdge(from,to)!=0){
        dense[1]=0;
        delete nodes[from]->edges[to];
        nodes[from]->edges.erase(to);
      }
      if(findEdge(to,from)!=0 && !dirigido){
        dense[1]=0;
        delete nodes[to]->edges[from];
        nodes[to]->edges.erase(from);
      }
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
    std::vector<edge> edges;
    map<string,node> nod;
    vector<node> prueba;
    prueba.push_back(nodes[id]);
    auto inicio=*(nodes[id]->data);
    // inicio.destinos.clear();
    nod[id]=new Node<G>(&inicio);
    while(prueba.size()!=nodes.size()){
      auto aux=menor_arista_nodos(prueba);
      edges.push_back(aux);
      prueba.push_back(aux->nodes[1]);
      auto guardar=*(aux->nodes[1]->data);
      nod[aux->nodes[1]->data->id]=new Node<G>(&guardar);
    }

    for(auto aux:edges){
      nod[aux->nodes[0]->data->id]->edges[aux->nodes[1]->data->id]=aux;
      auto reversa=new Edge<G>(aux->nodes[1],aux->nodes[0]);
      reversa->set_data(aux->data);
      nod[aux->nodes[1]->data->id]->edges[aux->nodes[0]->data->id]=reversa;
    }
    prim.nodes=nod;
    return prim;
  }

  bool bipartito(){
      map<node,int> temp={};
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

  Graph<G> kruskal(){
    if(dirigido | !conexo()){
    cout<<"NO ES DIRIGIDO Y CONEXO"<<endl;
    throw exception();
    }
    Graph<G> kruskal;
    map<string,node>  nod;
    double minimo=0;
    int nodos=0;
    vector<vector<node>>recorridos;
    vector<edge>recorridas;
    vector<edge>edges_kruskal;
    vector<node>nodes_kruskal;
    while(nodes.size()!=(edges_kruskal.size()/2)+1){
      auto edge=siguiente_menor(minimo,recorridas);
      // if(edge==nullptr)
      recorridas.push_back(edge);
      recorridas.push_back(findEdge(edge->nodes[1]->data->id,edge->nodes[0]->data->id));
      node inicio=nullptr;
      int i1,i2,j1,j2;
      node  fin=nullptr;
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
        cout<<"{"<<edge->nodes[0]->data->id<<" - "<<edge->nodes[1]->data->id<<"} => "<<edge->data<<endl;
        vector<node> n;
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
            cout<<"{"<<edge->nodes[0]->data->id<<" - "<<edge->nodes[1]->data->id<<"} => "<<edge->data<<endl;
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
        cout<<"{"<<edge->nodes[0]->data->id<<" - "<<edge->nodes[1]->data->id<<"} => "<<edge->data<<endl;
        recorridos[i1].push_back(edge->nodes[1]);
        recorridos[i1].push_back(edge->nodes[0]);
        edges_kruskal.push_back(findEdge(edge->nodes[1]->data->id,edge->nodes[0]->data->id));
        edges_kruskal.push_back(edge);
        nodos++;
        nodes_kruskal.push_back(edge->nodes[1]);
      }
      else if(inicio==nullptr && fin!=nullptr)
      {
        cout<<"{"<<edge->nodes[0]->data->id<<" - "<<edge->nodes[1]->data->id<<"} => "<<edge->data<<endl;
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
    for(auto aux:edges_kruskal){
        nod[aux->nodes[0]->data->id]->edges[aux->nodes[1]->data->id]=aux;
        auto reversa=new Edge<G>(aux->nodes[1],aux->nodes[0]);
        reversa->set_data(aux->data);
        nod[aux->nodes[1]->data->id]->edges[aux->nodes[0]->data->id]=reversa;
    }
    kruskal.nodes=nod;

    return kruskal;

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

  bool conexo(){
    map<node,bool> temp={};
    for(auto it=nodes.begin();it!=nodes.end();++it){
      temp[it->second];
    }
    for(auto it=temp.begin();it!=temp.end();++it){
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

  vector<pair<string,string>> DFS(string id){
    map<node,node> temp={};
    map<node,bool> check={};
    vector<pair<string,string>> answer={};
    for(auto it=nodes.begin();it!=nodes.end();++it){
      temp[it->second]=0;
      check[it->second]=0;
    }
    check[nodes[id]]=1;
    temp.erase(nodes[id]);
    DFSLoop(nodes[id],temp,check);
    for(auto it=temp.begin();it!=temp.end();++it){
      if(check[it->first])
        answer.push_back(make_pair(it->second->data->id,it->first->data->id));
      else
        answer.push_back(make_pair(it->first->data->id,"no way"));
    }
    
    return answer;
  }
  vector<pair<string,string>> BFS(string id){
    map<node,node> temp={};
    queue<node> check;
    map<node,bool> checker;
    vector<pair<string,string>> answer={};
    check.push(nodes[id]);
    node current;
    for(auto it=nodes.begin();it!=nodes.end();++it){
      checker[it->second]=0;
      temp[it->second]=0;
    }
    checker[nodes[id]]=1;
    temp.erase(nodes[id]);
    while (!check.empty()){
      current=check.front();
      check.pop();
      for(auto it=current->edges.begin();it!=current->edges.end();++it){
        if(!checker[it->second->nodes[1]]){
          temp[it->second->nodes[1]]=current;
          checker[it->second->nodes[1]]=1;
          check.push(it->second->nodes[1]);
        }
      }
    }
    for(auto it=temp.begin();it!=temp.end();++it){
      if(checker[it->first])
        answer.push_back(make_pair(it->second->data->id,it->first->data->id));
      else
        answer.push_back(make_pair(it->first->data->id,"no way"));
    }    
    return answer;
  }

  Graph<G> dijkstra(string id){
    Graph<G> a;
    map<node,int> final;
    map<node,node> answer;
    map<node,bool> done;
    for(auto it=nodes.begin();it!=nodes.end();it++){
      final[it->second]=-1;
    }
    auto temp=nodes[id];
    int prev=0;
    final[nodes[id]]=0;
    done[nodes[id]]=1;
    for(int i=0;i<nodes.size();i++){
      for(auto it=temp->edges.begin();it!=temp->edges.end();it++){
        if((final[it->second->nodes[1]]==-1 || final[it->second->nodes[1]]>(prev+it->second->data)) && !done[it->second->nodes[1]]){
          final[it->second->nodes[1]]=prev+it->second->data;
          answer[it->second->nodes[1]]=temp;
        }
      }
      auto it=final.begin();
      node prevnode=it->first;
      while(it!=final.end()){
        if(!done[it->first]){
          prevnode=it->first;
          it++;
          break;
        }
        it++;
      }
      while(it!=final.end()){
        if(!done[it->first])
          if((final[it->first] != -1 && final[it->first]<final[prevnode]))
            prevnode=it->first;
        it++;
      }
      temp=prevnode;
      prev=final[temp];
      done[prevnode]=1;
    }
    for(auto it=final.begin();it!=final.end();it++)
      a.addNode(new P(it->first->data->id));
    for(auto it=answer.begin();it!=answer.end();it++){
      for(auto it2=it->second->edges.begin();it2!=it->second->edges.end();it2++){
        if(it2->second->nodes[1]==it->first){
          a.addEdge(it->second->data->id,it->first->data->id,it2->second->data);
          a.addEdge(it->first->data->id,it->second->data->id,it2->second->data);
          break;
        }
      }
    }
    return a;
  };

  Graph<G> BellmanFord(string id){
    Graph<G> a;
    vector<node> final;
    map<node,float> values;
    map<node,node> answer;
    map<node,bool> inreach;
    bool changed=1;
    auto it2 = nodes.find(id);
    for(auto it=it2;it!=nodes.end();it++){
      final.push_back(it->second);
      values[it->second]=std::numeric_limits<float>::max();
      inreach[it->second]=0;
    };
    for(auto it=nodes.begin();it!=it2;it++){
      final.push_back(it->second);
      values[it->second]=std::numeric_limits<float>::max();
      inreach[it->second]=0;
    };
    inreach[nodes[id]]=1;
    values[nodes[id]]=0;
    while(changed){
      changed=0;
      for(auto it=final.begin();it!=final.end();it++)
        if(inreach[*it])
          for(auto it2=(*it)->edges.begin();it2!=(*it)->edges.end();it2++)
            if(it2->second->data + values[*it] < (values[it2->second->nodes[1]])){
              values[it2->second->nodes[1]]=it2->second->data+values[*it];
              inreach[it2->second->nodes[1]]=1;
              answer[it2->second->nodes[1]]=(*it);
              changed=1;
            }
    }
    for(auto it=final.begin();it!=final.end();it++)
      a.addNode(new P((*it)->data->id));
    for(auto it=answer.begin();it!=answer.end();it++)
      for(auto it2=it->second->edges.begin();it2!=it->second->edges.end();it2++){
        if(it2->second->nodes[1]==it->first){
          a.addEdge(it->second->data->id,it->first->data->id,it2->second->data);
          a.addEdge(it->first->data->id,it->second->data->id,it2->second->data);
          break;
        }
    }
    return a;
  }

};

#endif
