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

class P{
public:
  string id;
  P(string id):id(id){};
};

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
class Graph;

template <typename G>
class Node {
public:
    G data;
    map<string,Edge<G>*> edges;
    double x=0,y=0;
    Node(){};
    Node(G data):data(data){};
    void set_c(double _x,double _y){
      x=_x;
      y=_y;
    };
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
    Edge(node inicio,node fin,float data_){
      nodes[0]=inicio;
      nodes[1]=fin;
      data=data_;

    }
    void set_data(float data_){data=data_;};
    void set_data(){
      data=distance(nodes[0]->data->y,nodes[0]->data->x,nodes[1]->data->y,nodes[1]->data->x);
      // data=sqrt(pow(nodes[1]->data->x-nodes[0]->data->x,2)+pow(nodes[1]->data->y-nodes[0]->data->y,2));
    };
};


template<typename G>
class Floyd_Warshall
{
private:
  vector<vector<double>> distancias;
  vector<vector<string>> recorridos;
  vector<vector<double>> inicial;
  map<string,int> posiciones;
  vector<Node<G>*>nodos;
  Graph<G> Grafo;
public:

  Floyd_Warshall(Graph<G> &grafo)
  {
    Grafo=grafo;
    int x=0,y=0;

    for(int i=0;i<grafo.nodes.size();i++)
    {
      vector<double> a(grafo.nodes.size());
      vector<double> c(grafo.nodes.size());
      vector<string> b(grafo.nodes.size());
      distancias.push_back(a);
      recorridos.push_back(b);
      inicial.push_back(c);
    }
    for(auto i=grafo.nodes.begin();i!=grafo.nodes.end();i++)
    {
        auto obj=*(i->second->data);
        posiciones[i->second->data->id]=x;
        nodos.push_back(i->second);
        for(auto j=grafo.nodes.begin();j!=grafo.nodes.end();j++)
        {
            if(i->second->data->id==j->second->data->id)
            {
                distancias[x][y]=0;
                inicial[x][y]=0;
                recorridos[x][y]="-";
            }
            else{
                recorridos[x][y]=j->second->data->id;
                auto aux=grafo.findEdge(i->second->data->id,j->second->data->id);
                if(aux== nullptr)
                {
                    distancias[x][y]=std::numeric_limits<float>::max();
                    inicial[x][y]=std::numeric_limits<float>::max();
                }
                else
                {
                    distancias[x][y]=aux->data;
                    inicial[x][y]=aux->data;
                }
            }

            y++;
        }
        y=0;
        x++;
    }
    /*
    cout<<"MATRICES INICIALES"<<endl;

    for(int i=0;i<grafo.nodes.size();i++)
    {
        for(int j=0;j<grafo.nodes.size();j++)
        {
            cout<<distancias[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    for(int i=0;i<grafo.nodes.size();i++)
    {
        for(int j=0;j<grafo.nodes.size();j++)
        {
            cout<<recorridos[i][j]<<" ";
        }
        cout<<endl;
    }
    */

    for(int k=0;k<grafo.nodes.size();k++)
    {
        for(int i=0;i<grafo.nodes.size();i++)
        {
            for(int j=0;j<grafo.nodes.size();j++)
            {
                if(distancias[i][k]!=std::numeric_limits<float>::max() && distancias[k][j]!=std::numeric_limits<float>::max()&&distancias[i][j]>distancias[i][k]+distancias[k][j])
                {
                    distancias[i][j]=distancias[i][k]+distancias[k][j];
                    recorridos[i][j]=nodos[k]->data->id;

                }
            }
        }
    }

    /*

    cout<<endl<<"DESPUES"<<endl;

    for(int i=0;i<grafo.nodes.size();i++)
    {
        for(int j=0;j<grafo.nodes.size();j++)
        {
            cout<<distancias[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    for(int i=0;i<grafo.nodes.size();i++)
    {
        for(int j=0;j<grafo.nodes.size();j++)
        {
            cout<<recorridos[i][j]<<" ";
        }
        cout<<endl;
    }
    */


  };

  Graph<G> find(string from, string to)
  {
    Graph<G> fw;
    string aux=from;
    string a,b;
    string t=to;
    int posx,posy;
    fw.addNode(Grafo.findNode(from)->data);
    cout<<endl<<"Imprimiendo camino de "<<from<<" a "<<to<<endl;
    while(aux!=to)
    {
        a=aux;
        cout<<aux<<" ";
        posx=posiciones[aux];
        posy=posiciones[to];
        aux=recorridos[posx][posy];
        cout<<aux<<endl;
        b=aux;
        fw.addNode(Grafo.findNode(b)->data);
        fw.addEdge(a,b,inicial[posiciones[a]][posiciones[b]]);
        if(Grafo.findEdge(b,a)!=nullptr)
        {
          fw.addEdge(b,a,inicial[posiciones[a]][posiciones[b]]);
        }
    }

    cout<<endl<<"Imprimiendo grafo"<< endl;
    fw.imprimir();
return fw;

  }

};





#endif
