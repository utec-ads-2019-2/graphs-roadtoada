#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "graph.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  Graph<airport*> test;
  ifstream ifs("profile.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  for(int i=0;i<obj.size();i++){
      std::vector<string> destinos;
      for(int j=0;j<obj[i]["destinations"].size();j++){
        destinos.push_back(obj[i]["destinations"][j].asString());
      }
      test.addNode(new airport(obj[i]["Id"].asString(),obj[i]["City"].asString(),obj[i]["Name"].asString(),obj[i]["Country"].asString(),stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString()),destinos));
  }
    test.imprimir();

    cout<<"*Probando* \n"<<endl;
    test.addEdge("4026","4024");
    test.removeEdge("7252","4026");
    test.removeNode("4027");
    test.imprimir();

//    graph test;
//    return EXIT_SUCCESS;
}