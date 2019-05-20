/*
 * map.h
 */
#ifndef MAP_H_
#define MAP_H_

#include <fstream>
#include <string>

#include "Graph.h"

template<class T>
Graph<T> readGraph(string name){
    
    Graph<VertexInfo> g;
    
    string map_dir = "mapas/"+name+"/";
    ifstream f(map_dir+"T03_nodes_X_Y_"+name+".txt");

    int lines = 0;
    string file_line;
    
    getline(f, file_line);
    lines = stoi(file_line);

    int ID;
    double X, Y;
    
    while(lines > 0){
        getline(f, file_line);
        file_line = file_line.substr(1);
        
        ID = stoi(file_line.substr(0, file_line.find(","));
        file_line = file_line.substr(file_line.find(",")+1);

        X = stod(file_line.substr(0, file_lind.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);

        Y = stod(file_line.substr(0, file_line.find(")")));
        
        VertexInfo v(X, Y, ID);
        
        g.addVertex(v);
        
        lines--;
    }

    f.close();

    f.open(map_dir+"T03_edges_"+name+".txt");
    
    f.close();
}

#endif