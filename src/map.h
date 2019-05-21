/*
 * map.h
 */
#ifndef MAP_H_
#define MAP_H_

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#include "Graph.h"
#include "VertexInfo.h"

Graph<VertexInfo> readGraph(string name){
    
    Graph<VertexInfo> g;
    
    string map_dir = "../mapas/"+name+"/";
    ifstream f(map_dir+"T03_nodes_X_Y_"+name+".txt");
    ifstream f1(map_dir+"T03_nodes_lat_lon_"+name+".txt");

    int lines = 0;
    string file_line;

    getline(f, file_line);
    lines = stoi(file_line);

    unsigned long ID;
    double X, Y, lat, lon;
    
    while(lines > 0){
        getline(f, file_line);
        file_line = file_line.substr(1);
        ID = stoi(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);
        X = stod(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);
        Y = stod(file_line.substr(0, file_line.find(")")));

        getline(f1, file_line);
        file_line = file_line.substr(file_line.find(",")+1);
        lat = stod(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);
        lon = stod(file_line.substr(0, file_line.find(")")));
        
        VertexInfo v(ID, X, Y, lat, lon);
        
        g.addVertex(v);
        
        lines--;
    }

    f.close();
    f1.close();

    f.open(map_dir+"T03_edges_"+name+".txt");
    
    getline(f, file_line);
    lines = stoi(file_line);

    unsigned long ID_origin, ID_destiny;   
    
    while(lines > 0){
        getline(f, file_line);
        file_line = file_line.substr(1);
        
        ID_origin = stoi(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);

        ID_destiny = stod(file_line.substr(0, file_line.find(")")));
        
        VertexInfo origin(ID_origin, 0, 0, 0, 0);
        VertexInfo destiny(ID_destiny, 0, 0, 0, 0);

        g.addEdge(origin, destiny, 0);
        
        lines--;
    }

    f.close();

    f.open(map_dir+"T03_tags_"+name+".txt");
    getline(f, file_line);
    lines = stoi(file_line);

    int number_nodes = 0;
    string tag;

    while(lines > 0){
        getline(f, file_line);
        tag = file_line.substr(file_line.find("=")+1);

        getline(f, file_line);
        number_nodes = stoi(file_line);

        while(number_nodes > 0){
            getline(f, file_line);
            ID = stoi(file_line);
            Vertex<VertexInfo> *v = g.findVertex(VertexInfo(ID, 0, 0, 0, 0));
            VertexInfo vi = v->getInfo();
            vi.addTag(tag);
            v->setInfo(vi);
            number_nodes--;
        }

        lines--;
    }

    f.close();
    return g;
}

#endif
