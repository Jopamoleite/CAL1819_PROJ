/*
 * Person.h
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include <vector>

#include "VertexInfo.h"

class Person {
	vector<VertexInfo> pois;
public:
	Person(vector<VertexInfo> pois){ this->pois = pois;	}
	vector<VertexInfo> getPois(){ return this->pois; }
	void addPOI(VertexInfo poi) { this->pois.push_back(poi); }
};

#endif /* SRC_PERSON_H_ */
