#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include "node.h"
#include "edge.h"

using namespace std;

struct Traits {
	typedef airport N;
	typedef float E;
};

template <typename Tr>
class Graph {
public:
    typedef Graph<Tr> self;
    typedef Node<self> node;
    typedef Edge<self> edge;
    typedef map<string,node*> NodeSeq;
    typedef vector<edge*> EdgeSeq;

    typedef typename Tr::N N;
    typedef typename Tr::E E;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;


    NodeSeq nodes;
	NodeIte ni;
    EdgeIte ei;

		void crear_aristas(node* temp){
			cout<<"Inicio crear arista"<<endl;
			for(auto i:temp->data->destinos)
			{
				cout<<"Data is "<<i<<endl;
				if(!nodes[i]){
					cout<<"No node found"<<endl;
					nodes[i]=new node();
					cout<<"Nodo creado en dir "<<nodes[i]<<endl;
				}
				cout<<"Begin const"<<endl;
				cout<<"Nodes[i] is "<<nodes[i]<<endl;
				edge tempedge(temp,nodes[i]);
				//edge* tempedge();
				cout<<"1"<<endl;
				(temp->edges).push_back(temp2);
				//cout<<"Finish const"<<endl;
				return;
			}
		}


		void addNode(N* nuevo){
			if(!nodes[nuevo->id]){
				node* temp;
				temp->data=nuevo;
				//node* temp(nuevo);
				crear_aristas(temp);
				nodes[nuevo->id]=temp;
			}
			else{
				nodes[nuevo->id]->data=nuevo;
				crear_aristas(nodes[nuevo->id]);
			}
		}
};

typedef Graph<Traits> graph;

#endif
