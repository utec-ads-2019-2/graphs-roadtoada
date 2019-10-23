#ifndef EDGE_H
#define EDGE_H

template <typename G>
class Edge {
    typedef typename G::E E;
    typedef typename G::node node;

    E* data=nullptr;
    node* nodes[2]={nullptr,nullptr};
    public:
    Edge(){};
    Edge(node* &inicio, node* &fin){
      nodes[0]=inicio;
      nodes[1]=fin;
      cout<<"Inicio es "<<inicio<<endl;
      cout<<"Fin es "<<fin<<endl;
      cout<<"Inicio es "<<nodes[0]<<endl;
      cout<<"Fin es "<<nodes[1]<<endl;
      data=nullptr;
      cout<<"hm"<<endl;
    }
};

#endif
