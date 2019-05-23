/*
 * citySightseeing.h
 */

#ifndef SRC_CITYSIGHTSEEING_H_
#define SRC_CITYSIGHTSEEING_H_

#include <vector>

#include "VertexInfo.h"
<<<<<<< HEAD
#include "Graph.h"
=======
#include "Person.h"
>>>>>>> 6bb9e3060698bb9a6fbb686823f2671fbd6bc199

std::vector<std::vector<unsigned long>> dividePeople(std::vector<Person> people, int bus_capacity);

<<<<<<< HEAD
void firstIteration(Graph graph, VertexInfo start, vector<VertexInfo> pois, VertexInfo finish);
=======
void firstIteration(VertexInfo start, std::vector<VertexInfo> pois, VertexInfo finish);
>>>>>>> 6bb9e3060698bb9a6fbb686823f2671fbd6bc199

void secondIteration(VertexInfo start, std::vector<VertexInfo> pois, VertexInfo finish); //Caixeiro-viajante

#endif /* SRC_CITYSIGHTSEEING_H_ */
