/*
 * Bigraph.h
 */
#ifndef BIGRAPH_H_
#define BIGRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <limits>
#include <cmath>
#include <unordered_map>

#include "MutablePriorityQueue.h"
#include "Person.h"

using namespace std;

class BigraphEdge;
class Bigraph;
class PersonVertex;
class POIVertex;

#define INF std::numeric_limits<double>::max()

/************************* PersonVertex  **************************/

class PersonVertex {
	Person info;                // contents
	bool visited = false;          // auxiliary field
	double dist = 0;
	PersonVertex *path = NULL;
	int index = 0;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;

public:
	PersonVertex(Person &in);
	bool operator<(PersonVertex & vertex) const; // // required by MutablePriorityQueue
	Person getInfo() const;
	void setInfo(const Person p);
	double getDist() const;
	PersonVertex *getPath() const;
	friend class Bigraph;
	friend class MutablePriorityQueue<PersonVertex>;
};

/************************* POIVertex  **************************/

class POIVertex {
	unsigned long info;                // contents
	bool visited = false;          // auxiliary field
	double dist = 0;
	POIVertex *path = NULL;
	int index = 0;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;

public:
	POIVertex(unsigned long in);
	bool operator<(POIVertex & vertex) const; // // required by MutablePriorityQueue
	unsigned long getInfo() const;
	void setInfo(const unsigned long p);
	double getDist() const;
	POIVertex *getPath() const;
	friend class Bigraph;
	friend class MutablePriorityQueue<POIVertex>;
};

/********************** BigraphEdge  ****************************/


class BigraphEdge {
	PersonVertex * origin; // origin vertex
	POIVertex * dest;      // destination vertex
	double weight;         // edge weight
public:
	BigraphEdge(PersonVertex* o, POIVertex *d, double w);
	POIVertex * getDest() const;
	PersonVertex* getOrigin() const;
	friend class Bigraph;
	friend class POIVertex;
	friend class PersonVertex;
};


/*************************** Bigraph  **************************/

struct idHash
{
	int operator() (const unsigned long & id) const
	{
		return id;
	}

	bool operator() (const unsigned long & id1, const unsigned long & id2) const
	{
		return id1 == id2;
	}
};

struct personHash{
	int operator() (const Person & p1) const
	{
		return p1.getID();
	}

	bool operator() (const Person & p1, const Person & p2) const
	{
		return p1 == p2;
	}
};

typedef unordered_map<unsigned long, int, idHash, idHash> idHashTable;
typedef unordered_map<Person, int, personHash, personHash> personHashTable;

class Bigraph {
	vector<PersonVertex *> people;    // people set
	vector<POIVertex *> pois; 		  // pois set
	vector<BigraphEdge> edges;		  // bigraph edges

	personHashTable personIds;
	idHashTable poisIds;

public:
	PersonVertex *findPersonVertex(const Person &in);
	POIVertex *findPOIVertex(const unsigned long &in);
	bool addPersonVertex(const Person &in);
	bool addPOIVertex(const unsigned long &in);
	int getNumPersonVertex() const;
	int getNumPOIVertex() const;

	vector<PersonVertex *> getPeople() const;
	vector<POIVertex *> getPOIs() const;

	PersonVertex * initSingleSource(const Person &origin);
	POIVertex * initSingleSource(const unsigned long &origin);
};


#endif /* GRAPH_H_ */
