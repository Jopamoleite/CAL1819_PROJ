/*
 * Bus.cpp
 */

#include "Bus.h"

void Bus::addPOI(VertexInfo poi){
	this->pois.push_back(poi);
}

void Bus::addPOIs(vector<VertexInfo> pois){
	if(this->pois.size() == 0)
		this->pois = pois;
	else{
		for(size_t i = 0; i < pois.size(); i++){
			this->pois.push_back(pois[i]);
		}
	}

}

void Bus::addVertex(Vertex* v){
	this->path.push_back(v);
}
