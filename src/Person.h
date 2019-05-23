/*
 * Person.h
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include <vector>

class Person {
	std::vector<unsigned long> pois;
public:
	Person(std::vector<unsigned long> pois){ this->pois = pois;	}
	std::vector<unsigned long> getPois(){ return this->pois; }
	void addPOI(unsigned long poi) { this->pois.push_back(poi); }
};

#endif /* SRC_PERSON_H_ */
