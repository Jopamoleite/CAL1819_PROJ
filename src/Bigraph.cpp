/*
 * Bigraph.cpp
 */

#include "Bigraph.h"
#include "Person.h"

#include <utility>

using namespace std;

PersonVertex::PersonVertex(Person& in) {
	this->info = in;
}

bool PersonVertex::operator<(PersonVertex & vertex) const{
	return this->info < vertex.info;
}

Person PersonVertex::getInfo() const{
	return this->info;
}

void PersonVertex::setInfo(const Person p){
	this->info = p;
}

double PersonVertex::getDist() const{
	return this->dist;
}

PersonVertex* PersonVertex::getPath() const{
	return this->path;
}


POIVertex::POIVertex(unsigned long in){
	this->info = in;
}

bool POIVertex::operator<(POIVertex & vertex) const{
	return this->info < vertex.info;
}

unsigned long POIVertex::getInfo() const{
	return this->info;
}

void POIVertex::setInfo(const unsigned long p){
	this->info = p;
}

double POIVertex::getDist() const{
	return this->dist;
}

POIVertex *POIVertex::getPath() const{
	return this->path;
}


BigraphEdge::BigraphEdge(PersonVertex* o, POIVertex *d, double w){
	this->origin = o;
	this->dest = d;
	this->weight = w;
}

POIVertex * BigraphEdge::getDest() const{
	return this->dest;
}

PersonVertex* BigraphEdge::getOrigin() const{
	return this->origin;
}


PersonVertex *Bigraph::findPersonVertex(const Person &in){
	try{
		int index = this->personIds.at(in);
		return people[index];
	}catch(out_of_range &e){
		return NULL;
	}
}

POIVertex *Bigraph::findPOIVertex(const unsigned long &in){
	try{
		int index = this->poisIds.at(in);
		return pois[index];
	}catch(out_of_range &e){
		return NULL;
	}
}

bool Bigraph::addPersonVertex(const Person &in){
	if ( findPersonVertex(in) != NULL)
		return false;
	Person person = in;
	PersonVertex *p = new PersonVertex(person);
	this->people.push_back(p);

	pair<Person, int> pi = make_pair(in, people.size()-1);
	this->personIds.insert(pi);

	return true;
}

bool Bigraph::addPOIVertex(const unsigned long &in){
	if ( findPOIVertex(in) != NULL)
		return false;
	POIVertex *p = new POIVertex(in);
	this->pois.push_back(p);

	pair<unsigned int, int> pi = make_pair(in, pois.size()-1);
	this->poisIds.insert(pi);

	return true;
}

int Bigraph::getNumPersonVertex() const{
	return this->people.size();
}

int Bigraph::getNumPOIVertex() const{
	return this->pois.size();
}

vector<PersonVertex *> Bigraph::getPeople() const{
	return this->people;
}

vector<POIVertex *> Bigraph::getPOIs() const{
	return this->pois;
}

PersonVertex * Bigraph::initSingleSource(const Person &origin){
	for (auto v : people) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findPersonVertex(origin);
	s->dist = 0;
	return s;
}

POIVertex * Bigraph::initSingleSource(const unsigned long &origin){
	for (auto v : pois) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findPOIVertex(origin);
	s->dist = 0;
	return s;
}






