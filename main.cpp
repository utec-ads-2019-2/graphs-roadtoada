#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "graph.h"
#include <vector>


using namespace std;


int main(int argc, char *argv[]) {
  // charged data

    Graph<airport*> test;
    ifstream ifs("prueba.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    for(int i=0;i<obj.size();i++){
        std::vector<string> destinos;
        test.addNode(new airport(obj[i]["Id"].asString(),obj[i]["City"].asString(),obj[i]["Name"].asString(),obj[i]["Country"].asString(),stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString())));
        test.findNode(obj[i]["Id"].asString())->set_c(stof(obj[i]["Longitude"].asString()),stof(obj[i]["Latitude"].asString()));
    }
    for(int i=0;i<obj.size();i++){
        for(int j=0;j<obj[i]["destinations"].size();j++){
    //
          if(test.findNode(obj[i]["destinations"][j].asString())!=0){
            test.addEdge(obj[i]["Id"].asString(),obj[i]["destinations"][j].asString());
            test.addEdge(obj[i]["destinations"][j].asString(),obj[i]["Id"].asString());
          }
        }
    }
    for(auto i:test.nodes){
      for(auto j:i.second->edges){
        if(test.findEdge(j.second->nodes[1]->data->id,i.first)==nullptr)
          test.dirigido=true;
      }
    }

    // test.imprimir();
    // test.~Graph();
    //cout<<"KRUSKAL:"<<endl;
    //auto a=test.kruskal();
    //a.imprimir();
  //ejemplo del profe{}
  /*  Graph<P*>test;
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
//    test.addEdge("G","I",39);
//    test.addEdge("I","G",39);
    test.addEdge("I","F",7);
    test.addEdge("F","I",7);
    test.addEdge("F","A",11);
    test.addEdge("A","I",11);
    test.addEdge("E","A",13);
    test.addEdge("A","E",13);
    test.addEdge("A","H",5);
    test.addEdge("H","A",5);
//    test.addEdge("E","I",26);
//    test.addEdge("I","E",26);
    test.addEdge("E","H",19);
    test.addEdge("H","E",19);
    test.addEdge("I","A",11);
//    test.imprimir();
//    test.nedges();
//    cout<<test.densidad();
*/
// Graph<P*>test;
/*
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

  test.addEdge("E","D",1);
  test.addEdge("D","E",1);

*/

/*
    test.addNode(new P("A"));
    test.addNode(new P("B"));
    test.addNode(new P("C"));
    test.addNode(new P("D"));
    test.addNode(new P("E"));
    test.addEdge("A","B",4);
    test.addEdge("B","A",4);
    test.addEdge("A","C",8);
    test.addEdge("C","A",8);
    test.addEdge("B","C",1);
    test.addEdge("B","D",2);
    test.addEdge("D","B",2);
    test.addEdge("D","E",7);
    test.addEdge("E","D",7);
    test.addEdge("E","C",2);
    test.addEdge("C","E",2);
    test.addEdge("C","D",4);
    test.addEdge("D","C",4);
*/












    /*test.addNode(new P("A"));
    test.addNode(new P("B"));
    test.addNode(new P("C"));
    test.addNode(new P("D"));
    test.addNode(new P("E"));

    test.addEdge("A","B",1);
    test.addEdge("A","C",5);
    test.addEdge("B","D",3);
    test.addEdge("B","E",6);


    test.addEdge("B","A",1);
    test.addEdge("C","A",5);
    test.addEdge("D","B",3);
    test.addEdge("E","B",6);
*/
//  test.conexo();
  // test.imprimir();
  // test.Astar("679","7201").imprimir();
//  float max=std::numeric_limits<float>::max();
//  cout<<max;
// test.Floyd_Warshall("2731","1815");
// Floyd_Warshall<airport*> a(test);
// a.find("2731","1815");
// cout<<endl<<"OTRA PRUEBA"<<endl;
// a.find("679","7201");
test.imprimir();
test.Astar("2731","1815");
  // cout<<endl<<endl;
  //DFS test
    /*vector<pair<string,string>> answer=test.DFS("A");
    cout<<"Printing"<<endl;
    for(auto it=answer.begin();it!=answer.end();++it){

      cout<<it->first<<" "<<it->second<<endl;
    }*/
  // BFS test
//    cout<<endl<<endl<<"BFS:"<<endl;
//    vector<pair<string,string>> answer=test.BFS("C");
//    cout<<"Printing"<<endl;
//    for(auto it=answer.begin();it!=answer.end();++it){
//      cout<<it->first<<" "<<it->second<<endl;
//    }
//    cout<<endl<<endl<<"A star "<<endl;
//    test.Astar("A","E");

  // auto test_dijkstra= test.dijkstra("A");
}
