#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "graph.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  Graph<airport*> test;
  ifstream ifs("prueba.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  for(int i=0;i<obj.size();i++){
      std::vector<string> destinos;
      test.addNode(new airport(obj[i]["Id"].asString(),obj[i]["City"].asString(),obj[i]["Name"].asString(),obj[i]["Country"].asString(),stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString())));
  }
  for(int i=0;i<obj.size();i++){
      for(int j=0;j<obj[i]["destinations"].size();j++){

        if(test.findNode(obj[i]["destinations"][j].asString())!=0){
          test.addEdge(obj[i]["Id"].asString(),obj[i]["destinations"][j].asString());
          // test.addEdge(obj[i]["destinations"][j].asString(),obj[i]["Id"].asString());
        }
      }
  }
  for(auto i:test.nodes){
    for(auto j:i.second->edges){
      if(test.findEdge(j.second->nodes[1]->data->id,i.first)==nullptr)
        test.dirigido=true;
    }
  }
  // test.~Graph();
  test.imprimir();

  // test.nodes.size();
  // cout<<"Done"<<endl;
  // test.nedges();
  // cout<<test.densidad();
    // auto a=test.prim("2731");
    // cout<<test.nodes.size()<<" "<<a.nodes.size()<<endl;
    // a.nedges();

}
