/*
 * citySightseeing.h
 */

#ifndef SRC_CITYSIGHTSEEING_H_
#define SRC_CITYSIGHTSEEING_H_

#include <vector>

#include "VertexInfo.h"
#include "Graph.h"

void dividePeople();

void firstIteration(Graph graph, VertexInfo start, vector<VertexInfo> pois, VertexInfo finish);

void secondIteration(VertexInfo start, vector<VertexInfo> pois, VertexInfo finish); //Caixeiro-viajante

#endif /* SRC_CITYSIGHTSEEING_H_ */
