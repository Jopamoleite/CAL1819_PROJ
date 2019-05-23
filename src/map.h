/*
 * map.h
 */
#ifndef MAP_H_
#define MAP_H_

#include <string>

#include "Graph.h"
#include "VertexInfo.h"
#include "graphviewer.h"

Graph readGraph(std::string name);
int viewGraph(Graph graph, GraphViewer* gv);

#endif
