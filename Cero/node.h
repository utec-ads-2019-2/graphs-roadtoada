#ifndef NODE_H
#define NODE_H
#include<map>
#include<iostream>
#include<vector>
#include "edge.h"
using namespace std;

template<typename G>
class Edge;

class airport{
public:
  string id;
  string city;
  string name;
  string country;
  double x;
  double y;
  std::vector<string> destinos;
  airport(string id_,string city_,string name_,string country_,double x,double y,vector<string> destinos_):id(id_),city(city_),name(name_),country(country_),x(x),y(y),destinos(destinos_){};
};


template <typename G>
class Node {
public:
    G data;
    map<string,Edge<G>*> edges;
    Node(){};
    Node(G data):data(data){};
    void print_edges(){
      for(auto it=edges.begin();it!=edges.end();++it){
        cout<<" Origen "<<it->second->nodes[0]->data->id<<" Destino "<<it->second->nodes[1]->data->id<<endl;
      }
    }
};


template <typename G>
class Edge {
public:
    typedef Node<G>* node;
    node nodes[2];
    Edge(node inicio,node fin){
      nodes[0]=inicio;
      nodes[1]=fin;
    }
};





#endif
