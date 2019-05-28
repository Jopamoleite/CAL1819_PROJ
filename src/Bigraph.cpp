/*
 * Bigraph.cpp
 */

#include "Bigraph.h"

#include <unordered_set>
#include <utility>
#include <limits.h>
#include <iostream>

using namespace std;

PersonVertex::PersonVertex(Person &in) {
	this->info = in;
}

bool PersonVertex::operator<(PersonVertex & vertex) const {
	return this->info < vertex.info;
}

Person PersonVertex::getInfo() const {
	return this->info;
}

void PersonVertex::setInfo(const Person p) {
	this->info = p;
}

double PersonVertex::getDist() const {
	return this->dist;
}

PersonVertex* PersonVertex::getPath() const {
	return this->path;
}

void PersonVertex::addOutgoingEdge(BigraphEdge *be){
	this->outgoing.push_back(be);
}

POIVertex::POIVertex(unsigned long in) {
	this->info = in;
}

bool POIVertex::operator<(POIVertex & vertex) const {
	return this->info < vertex.info;
}

unsigned long POIVertex::getInfo() const {
	return this->info;
}

void POIVertex::setInfo(const unsigned long p) {
	this->info = p;
}

double POIVertex::getDist() const {
	return this->dist;
}

POIVertex *POIVertex::getPath() const {
	return this->path;
}

void POIVertex::addIncomingEdge(BigraphEdge *be){
	this->incoming.push_back(be);
}

BigraphEdge::BigraphEdge(PersonVertex* o, POIVertex *d, double w) {
	this->origin = o;
	this->dest = d;
	this->weight = w;
}

POIVertex * BigraphEdge::getDest() const {
	return this->dest;
}

PersonVertex* BigraphEdge::getOrigin() const {
	return this->origin;
}

PersonVertex *Bigraph::findPersonVertex(const Person &in) {
	try {
		int index = this->personIds.at(in);
		return people[index];
	} catch (out_of_range &e) {
		return NULL;
	}
}

POIVertex *Bigraph::findPOIVertex(const unsigned long &in) {
	try {
		int index = this->poisIds.at(in);
		return pois[index];
	} catch (out_of_range &e) {
		return NULL;
	}
}

bool Bigraph::addPersonVertex(const Person &in) {
	if (findPersonVertex(in) != NULL)
		return false;
	Person person = in;
	PersonVertex *p = new PersonVertex(person);
	this->people.push_back(p);

	pair<Person, int> pi = make_pair(in, people.size() - 1);
	this->personIds.insert(pi);

	return true;
}

bool Bigraph::addPOIVertex(const unsigned long &in) {
	if (findPOIVertex(in) != NULL)
		return false;
	POIVertex *p = new POIVertex(in);
	this->pois.push_back(p);

	pair<unsigned int, int> pi = make_pair(in, pois.size() - 1);
	this->poisIds.insert(pi);

	return true;
}

int Bigraph::getNumPersonVertex() const {
	return this->people.size();
}

int Bigraph::getNumPOIVertex() const {
	return this->pois.size();
}

vector<PersonVertex *> Bigraph::getPeople() const {
	return this->people;
}

vector<POIVertex *> Bigraph::getPOIs() const {
	return this->pois;
}

PersonVertex * Bigraph::initSingleSource(const Person &origin) {
	for (auto v : people) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findPersonVertex(origin);
	s->dist = 0;
	return s;
}

POIVertex * Bigraph::initSingleSource(const unsigned long &origin) {
	for (auto v : pois) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findPOIVertex(origin);
	s->dist = 0;
	return s;
}

bool Bigraph::addBigraphEdge(const Person &person, const unsigned long &poi){
	PersonVertex* pev = findPersonVertex(person);
	if(pev == NULL)
		return false;
	POIVertex* poiv = findPOIVertex(poi);
	if(poiv == NULL)
		return false;
	BigraphEdge* be = new BigraphEdge(pev, poiv, 1);
	pev->addOutgoingEdge(be);
	poiv->addIncomingEdge(be);
	this->edges.push_back(*be);
	return true;
}

pair<vector<unsigned long>, vector<Person>> Bigraph::getPeopleForBus(int bus_capacity){
	if(this->edges.size() == 0){
		cout << "NO MORE EDGES" << endl;
		return pair<vector<unsigned long>, vector<Person>>();
	}
	vector<unsigned long> vpois;
	vector<Person> vperson;

	vector<POIVertex*>::iterator most_requested_point = (this->pois).begin();
	for(vector<POIVertex*>::iterator it = (this->pois).begin()++; it != (this->pois).end(); it++){
		if(((*it)->incoming).size() > ((*most_requested_point)->incoming).size()){
			most_requested_point = it;
		}
	}
	vpois.push_back((*most_requested_point)->info);
	for(vector<BigraphEdge*>::iterator it = ((*most_requested_point)->incoming).begin(); it != ((*most_requested_point)->incoming).end(); it++){
		vperson.push_back(((*it)->origin)->info);
		for(vector<BigraphEdge*>::iterator it1 = ((*it)->origin)->outgoing.begin(); it1 != (((*it)->origin)->outgoing).end(); it1++){
			vpois.push_back(((*it1)->dest)->info);
			(((*it)->origin)->outgoing).erase(it1);
			it1--;
		}
		((*most_requested_point)->incoming).erase(it);
		it--;
	}

	//Remove duplicates
	unordered_set<unsigned long> us;
	for (unsigned long i : vpois)
	    us.insert(i);
	vpois.assign(us.begin(), us.end());

	return make_pair(vpois, vperson);
}

