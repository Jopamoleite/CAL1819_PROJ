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
    string map_dir = "mapas/"+name+"/";
    ifstream f(map_dir+"T03_nodes_X_Y_"+name+".txt");

    int lines = 0;
    string file_line;
    
    getline(f, file_line);
    lines = stoi(file_line);

    f.close();
}

#endif