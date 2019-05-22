/*
 * Bus.h
 */

#ifndef SRC_BUS_H_
#define SRC_BUS_H_

#include <vector>

#include "Graph.h"
#include "VertexInfo.h"

class Bus {
	vector<VertexInfo> pois;
	vector<Vertex<VertexInfo>*> path;
	int capacity;
public:
	Bus(int capacity);
	int getCapacity(){ return this->capacity;}
	vector<VertexInfo> getPOIs() { return this->pois; };
	vector<Vertex<VertexInfo>*> getPath() { return this->path; }

	void addPOI(VertexInfo poi);
	void addPOIs(vector<VertexInfo> pois);
	void addVertex(Vertex<VertexInfo>* v);
};

#endif /* SRC_BUS_H_ */
