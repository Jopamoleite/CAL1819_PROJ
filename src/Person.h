/*
 * Person.h
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include <vector>

class Person {
	std::vector<unsigned long> pois;
	unsigned long id;
	static unsigned long seq_id;
public:
	static void initialize_seq_id() { Person::seq_id = 1; }
	Person(std::vector<unsigned long> pois){ this->pois = pois;	this->id = Person::seq_id; Person::seq_id++;}
	std::vector<unsigned long> getPois() const{ return this->pois; }
	void addPOI(const unsigned long poi) { this->pois.push_back(poi); }
	bool operator<(const Person& p1) const{
		if(this->pois.size() > p1.getPois().size())
			return true;
		return false;
	}
	unsigned int getID() const { return this->id; }
	bool operator == (const Person &p1) const{
		if(this->id == p1.getID())
			return true;
		return false;
	}
};

#endif /* SRC_PERSON_H_ */
