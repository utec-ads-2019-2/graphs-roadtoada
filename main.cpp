#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "graph.h"
#include <vector>

class P{
public:
  string id;
  P(string id):id(id){};
};

using namespace std;


int main(int argc, char *argv[]) {
  // Graph<airport*> test;
  // ifstream ifs("prueba.json");
  // Json::Reader reader;
  // Json::Value obj;
  // reader.parse(ifs, obj);
  // for(int i=0;i<obj.size();i++){
  //     std::vector<string> destinos;
  //     test.addNode(new airport(obj[i]["Id"].asString(),obj[i]["City"].asString(),obj[i]["Name"].asString(),obj[i]["Country"].asString(),stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString())));
  // }
  // for(int i=0;i<obj.size();i++){
  //     for(int j=0;j<obj[i]["destinations"].size();j++){
  //
  //       if(test.findNode(obj[i]["destinations"][j].asString())!=0){
  //         test.addEdge(obj[i]["Id"].asString(),obj[i]["destinations"][j].asString());
  //         // test.addEdge(obj[i]["destinations"][j].asString(),obj[i]["Id"].asString());
  //       }
  //     }
  // }
  // for(auto i:test.nodes){
  //   for(auto j:i.second->edges){
  //     if(test.findEdge(j.second->nodes[1]->data->id,i.first)==nullptr)
  //       test.dirigido=true;
  //   }
  // }
  // test.~Graph();
  //cout<<"KRUSKAL:"<<endl;
  //auto a=test.kruskal();
  //a.imprimir();
  Graph<P*>test;
  test.addNode(new P("A"));
  test.addNode(new P("B"));
  test.addNode(new P("C"));
  test.addNode(new P("D"));
  test.addNode(new P("E"));
  test.addNode(new P("F"));
  test.addNode(new P("G"));
  test.addNode(new P("H"));
  test.addNode(new P("I"));
  test.addNode(new P("J"));
  test.addEdge("B","J",15);
  test.addEdge("J","B",15);
  test.addEdge("H","J",15);
  test.addEdge("J","H",15);
  test.addEdge("J","D",15);
  test.addEdge("D","J",15);
  test.addEdge("B","G",2);
  test.addEdge("G","B",2);
  test.addEdge("B","E",24);
  test.addEdge("E","B",24);
  test.addEdge("B","H",29);
  test.addEdge("H","B",29);
  test.addEdge("D","H",5);
  test.addEdge("H","D",5);
  test.addEdge("D","A",12);
  test.addEdge("A","D",12);
  test.addEdge("D","C",39);
  test.addEdge("C","D",39);
  test.addEdge("C","A",4);
  test.addEdge("A","C",4);
  test.addEdge("C","I",37);
  test.addEdge("I","C",37);
  test.addEdge("C","F",9);
  test.addEdge("F","C",9);
  test.addEdge("G","E",2);
  test.addEdge("E","G",2);
  test.addEdge("G","I",39);
  test.addEdge("I","G",39);
  test.addEdge("I","F",7);
  test.addEdge("F","I",7);
  test.addEdge("F","A",11);
  test.addEdge("A","F",11);
  test.addEdge("E","A",13);
  test.addEdge("A","E",13);
  test.addEdge("A","H",5);
  test.addEdge("H","A",5);
  test.addEdge("E","I",26);
  test.addEdge("I","E",26);
  test.addEdge("E","H",19);
  test.addEdge("H","E",19);
  // test.addEdge("","",);
  // test.imprimir();
  // test.nedges();
  cout<<test.densidad();
  test.prim("I");

  // test.nodes.size();
  // cout<<"Done"<<endl;
  // test.nedges();
  // cout<<test.densidad();
    // auto a=test.prim("2731");
    // cout<<test.nodes.size()<<" "<<a.nodes.size()<<endl;
    // a.nedges();

}
