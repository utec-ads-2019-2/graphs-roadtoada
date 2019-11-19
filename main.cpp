#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "graph.h"
#include <vector>


using namespace std;


int main(int argc, char *argv[]) {
  Graph<P*>test;
  // charged data
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
  //ejemplo del profe{}
    /*Graph<P*>test;
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
    test.addEdge("","",);
    test.imprimir();
    test.nedges();
    cout<<test.densidad();*/
  /*test1{}
    test.addNode(new P("A"));
    test.addNode(new P("B"));
    test.addNode(new P("C"));
    test.addNode(new P("D"));
    test.addNode(new P("E"));
    test.addNode(new P("F"));
    test.addEdge("A","B",4);
    test.addEdge("A","C",2);
    test.addEdge("C","B",1);
    test.addEdge("B","D",5);
    test.addEdge("C","D",8);
    test.addEdge("C","E",10);
    test.addEdge("E","F",2);
    test.addEdge("E","D",2);
    test.addEdge("D","F",6);

    test.addEdge("B","A",4);
    test.addEdge("C","A",2);
    test.addEdge("B","C",1);
    test.addEdge("D","B",5);
    test.addEdge("D","C",8);
    test.addEdge("E","C",10);
    test.addEdge("F","E",2);
    test.addEdge("D","E",2);
    test.addEdge("F","D",6);
  */
  /*test2{}*/
    test.addNode(new P("A"));
    test.addNode(new P("B"));
    test.addNode(new P("C"));
    test.addNode(new P("D"));
    test.addNode(new P("E"));
    test.addNode(new P("F"));
    test.addEdge("A","B",10);
    test.addEdge("A","E",11);
    test.addEdge("A","C",2);
    test.addEdge("C","D",3);
    test.addEdge("B","F",4);
    test.addEdge("A","F",3);
    test.addEdge("F","E",2);

    test.addEdge("B","A",10);
    test.addEdge("E","A",11);
    test.addEdge("C","A",2);
    test.addEdge("D","C",3);
    test.addEdge("F","B",4);
    test.addEdge("F","A",3);
    test.addEdge("E","F",2);
  

  test.conexo();
  test.BFS("A");
  test.DFS("A");
  test.densidad();
  //test.kruskal();
  test.prim("A");
  test.conexo();
  test.bipartito();
  test.imprimir();
  cout<<endl<<endl;
  //DFS test
    /*vector<pair<string,string>> answer=test.DFS("A");
    cout<<"Printing"<<endl;
    for(auto it=answer.begin();it!=answer.end();++it){
      cout<<it->first<<" "<<it->second<<endl;
    }*/
  //BFS test
    /*cout<<endl<<endl<<"BFS:"<<endl;
    vector<pair<string,string>> answer=test.BFS("A");
    cout<<"Printing"<<endl;
    for(auto it=answer.begin();it!=answer.end();++it){
      cout<<it->first<<" "<<it->second<<endl;
    }*/

  auto test_dijkstra= test.dijkstra("A");
  test_dijkstra.imprimir();
}
