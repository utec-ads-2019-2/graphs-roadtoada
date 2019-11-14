#ifndef NODE_H
#define NODE_H
#include<map>
#include<iostream>
#include<vector>
#include<math.h>
#include <bits/stdc++.h>
using namespace std;

long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1, long double lat2, long double long2)
{
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));
    long double R = 6371;
    ans = ans * R;

    return ans;
}

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
  airport(string id_,string city_,string name_,string country_,double x,double y):id(id_),city(city_),name(name_),country(country_),x(x),y(y){};
};

class example{
public:
  char id;
  example(char _id):id(_id){};
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
        cout<<" Origen "<<it->second->nodes[0]->data->id<<" Destino "<<it->second->nodes[1]->data->id<<" Peso "<<it->second->data<<endl;
      }
    }
};

template <typename G>
class Edge {
public:
    typedef Node<G>* node;
    double data;
    node nodes[2];
    Edge(node inicio,node fin){
      nodes[0]=inicio;
      nodes[1]=fin;
      data=0;

    }
    void set_data(float data_){data=data_;};
    void set_data(){
      data=distance(nodes[0]->data->y,nodes[0]->data->x,nodes[1]->data->y,nodes[1]->data->x);
      // data=sqrt(pow(nodes[1]->data->x-nodes[0]->data->x,2)+pow(nodes[1]->data->y-nodes[0]->data->y,2));
    };
};





#endif
