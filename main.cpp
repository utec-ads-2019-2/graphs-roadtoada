#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "graph.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  graph test;
  map<string,airport*> hola;
  ifstream ifs("profile.json");
  Json::Reader reader;
  Json::Value obj;
  reader.parse(ifs, obj);
  for(int i=0;i<obj.size();i++){
      std::vector<string> destinos;
      for(int j=0;j<obj[i]["destinations"].size();j++){
        destinos.push_back(obj[i]["destinations"][j].asString());
        // cout<<obj[i]["destinations"][j]<<endl;
      }

      // v.push_back(new airport(obj[i]["Id"].asString(),obj[i]["City"].asString(),obj[i]["Name"].asString(),obj[i]["Country"].asString(),stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString()),destinos));

      test.addNode(new airport(obj[i]["Id"].asString(),obj[i]["City"].asString(),obj[i]["Name"].asString(),obj[i]["Country"].asString(),stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString()),destinos));
      // n.push_back(new airport(stoi(obj[i]["Id"].asString()),obj[i]["City"].asString(),obj[i]["Name"].asString(),obj[i]["Country"].asString()),stof(obj[i]["Longitude"],stof(obj[i]["Latitude"])))
      // auto n=new Node<airpot>(o,stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString()));
      // test.nodes.push_back(n);
  }

  // cout<<hola["156"]<<endl;
  // hola["156"]=new airport("dasd","sda")

  // for(auto i:v)
    // cout<<i->name<<" "<<i->x<<" "<<i->y<<endl;


//    graph test;
//    return EXIT_SUCCESS;
}
