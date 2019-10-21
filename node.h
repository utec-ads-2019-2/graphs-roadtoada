#ifndef NODE_H
#define NODE_H
#include<map>
#include<iostream>
#include<vector>
using namespace std;


template <typename G>
class Node {
public:
    typedef G N;
    // typedef typename G::N N;
    typedef typename G::EdgeSeq EdgeSeq;

    N data;
    EdgeSeq edges;
    Node(){};
    // Node(N data_, EdgeSeq aristas):data(data_),edges(aristas){};
};

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

#endif
