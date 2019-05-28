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
#include <utility>

#include "MutablePriorityQueue.h"
#include "Person.h"

class BigraphEdge;
class Bigraph;
class PersonVertex;
class POIVertex;

#define INF std::numeric_limits<double>::max()

/************************* PersonVertex  **************************/

class PersonVertex {
	Person info;                // contents
	std::vector<BigraphEdge*> outgoing;
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
	std::vector<BigraphEdge*>  getOutgoing() const;
	PersonVertex *getPath() const;
	void addOutgoingEdge(BigraphEdge *be);
	friend class Bigraph;
	friend class MutablePriorityQueue<PersonVertex>;
};

/************************* POIVertex  **************************/

class POIVertex {
	unsigned long info;                // contents
	std::vector<BigraphEdge*> incoming;
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
	std::vector<BigraphEdge*>  getIncoming() const;
	POIVertex *getPath() const;
	void addIncomingEdge(BigraphEdge *be);
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
	bool operator==(const BigraphEdge& be);
	friend class Bigraph;
	friend class POIVertex;
	friend class PersonVertex;
};


/*************************** Bigraph  **************************/

struct bigraph_idHash
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

typedef std::unordered_map<unsigned long, int, bigraph_idHash, bigraph_idHash> bigraph_idHashTable;
typedef std::unordered_map<Person, int, personHash, personHash> personHashTable;

class Bigraph {
	std::vector<PersonVertex *> people;    // people set
	std::vector<POIVertex *> pois; 		  // pois set
	std::vector<BigraphEdge> edges;		  // bigraph edges

	personHashTable personIds;
	bigraph_idHashTable poisIds;

public:
	PersonVertex *findPersonVertex(const Person &in);
	POIVertex *findPOIVertex(const unsigned long &in);
	bool addPersonVertex(const Person &in);
	bool addPOIVertex(const unsigned long &in);
	bool addBigraphEdge(const Person &person, const unsigned long &poi);
	int getNumPersonVertex() const;
	int getNumPOIVertex() const;
	int getNumEdges() const;

	std::vector<PersonVertex *> getPeople() const;
	std::vector<POIVertex *> getPOIs() const;
	std::vector<BigraphEdge> getEdges() const;

	PersonVertex * initSingleSource(const Person &origin);
	POIVertex * initSingleSource(const unsigned long &origin);

	std::pair<std::vector<unsigned long>, std::vector<Person>>getPeopleForBus(int &numEdges, int bus_capacity = INT_MAX);
};


#endif /* GRAPH_H_ */
