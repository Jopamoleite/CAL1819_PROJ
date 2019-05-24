/*
 * Graph.cpp
 */
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>

#include "Graph.h"

/************************* Vertex  **************************/

Vertex::Vertex(VertexInfo in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *d, double w) {
	this->adj.push_back(Edge(d, w));
}

bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}


VertexInfo Vertex::getInfo() const {
	return this->info;
}


void Vertex::setInfo(const VertexInfo info){
	this->info = info;
}


double Vertex::getDist() const {
	return this->dist;
}


Vertex *Vertex::getPath() const {
	return this->path;
}


vector<Edge> Vertex::getAdjEdges() const{
	return this->adj;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *d, double w): dest(d), weight(w) {}


Vertex * Edge::getDest() const {return dest;}

/*************************** Graph  **************************/

int Graph::getNumVertex() const {
	return vertexSet.size();
}


vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const VertexInfo &in) const {
	try{
		int index = ids.at(in.getID());
		return vertexSet[index];
	}catch(out_of_range &e){
		return NULL;
	}
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const VertexInfo &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex(in));
	pair<unsigned long, int> p = make_pair(in.getID(), vertexSet.size()-1);
	ids.insert(p);

	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const VertexInfo &sourc, const VertexInfo &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices.
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const VertexInfo &sourc, const VertexInfo &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,v2->getInfo()-v1->getInfo());
	return true;
}

/**************** Single Source Shortest Path algorithms ************/

/**
 * Initializes single-source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */

Vertex * Graph::initSingleSource(const VertexInfo &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}

/**
 * Analyzes an edge in single-source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */

bool Graph::relax(Vertex *v, Vertex *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}

/**
 * Dijkstra algorithm.
 */

void Graph::dijkstraShortestPath(const VertexInfo &origin, const VertexInfo &dest) {
	auto s = initSingleSource(origin);
	bool found_dest = false;
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while( !q.empty() && !found_dest) {
		auto v = q.extractMin();
		for(auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if(e.dest->getInfo() == dest)
				found_dest = true;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}

vector<VertexInfo> Graph::dijkstraPathToNearestPOI(const VertexInfo &origin, const VertexInfo &dest, const vector<VertexInfo> &pois) {
	unordered_set<VertexInfo, VertexInfoHash, VertexInfoComparator> pois_set;
	vector<VertexInfo> shortest_path;
	vector<VertexInfo> tmp;

	for(size_t i = 0; i < pois.size(); i++)
		pois_set.insert(pois.at(i));

	auto s = initSingleSource(origin);
	bool found = false;
	MutablePriorityQueue<Vertex> q;
	VertexInfo last_found = VertexInfo(0);
	q.insert(s);
	while( !q.empty() && !found) { //stops when nearest POI is found
		auto v = q.extractMin();
		for(auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if(pois_set.count(e.dest->getInfo())){
				found = true;
				pois_set.erase(e.dest->getInfo());
				last_found = e.dest->getInfo();
			}
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
	tmp = getPath(origin, last_found);
	for(size_t j = 0; j < tmp.size(); j++){
		if(shortest_path.size() == 0 || shortest_path.at(shortest_path.size()-1).getID() != tmp.at(j).getID()){
			shortest_path.push_back(tmp.at(j));
		}
	}

	found = false;

	while(!pois_set.empty()){
		s = initSingleSource(last_found);
		q.insert(s);
		while(!q.empty()) {
			auto v = q.extractMin();
			for(auto e : v->adj) {
				auto oldDist = e.dest->dist;
				if(pois_set.count(e.dest->getInfo())){
					pois_set.erase(e.dest->getInfo());
					last_found = e.dest->getInfo();
				}
				if (relax(v, e.dest, e.weight)) {
					if (oldDist == INF)
						q.insert(e.dest);
					else
						q.decreaseKey(e.dest);
				}
			}
		}
		tmp = getPath(origin, last_found);
			for(size_t j = 0; j < tmp.size(); j++){
				if(shortest_path.size() == 0 || shortest_path.at(shortest_path.size()-1).getID() != tmp.at(j).getID()){
					shortest_path.push_back(tmp.at(j));
				}
			}
	}

	dijkstraShortestPath(last_found, dest);
	tmp = getPath(last_found, dest);

	for(size_t j = 0; j < tmp.size(); j++){
		if(shortest_path.size() == 0 || shortest_path.at(shortest_path.size()-1).getID() != tmp.at(j).getID()){
			shortest_path.push_back(tmp.at(j));
		}
	}

	return shortest_path;
}

vector<VertexInfo> Graph::getPath(const VertexInfo &origin, const VertexInfo &dest) const{
	vector<VertexInfo> res;
	auto v = findVertex(dest);
	if  (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for ( ; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

vector<vector<unsigned long>> Graph::getSCCs(){
	return this->SCCs;
}

void Graph::SCCUtil(Vertex* v, int discovered[], int early[], stack<Vertex*> *stck,
		bool stackMember[])
{
	static int time = 0;

	discovered[v->index] = early[v->index] = ++time;
	stck->push(v);
	stackMember[v->index] = true;

	for (unsigned int i = 0; i < v->adj.size(); ++i)
	{
		Vertex* u = v->adj.at(i).dest;

		if (discovered[u->index] == -1)
		{
			SCCUtil(u, discovered, early, stck, stackMember);

			early[v->index]  = min(early[v->index], early[u->index]);
		}else if (stackMember[u->index] == true)
			early[v->index]  = min(early[v->index], discovered[u->index]);
	}

	Vertex* vert = 0;  // To store stack extracted vertices
	vector<unsigned long> component;
	if (early[v->index] == discovered[v->index])
	{
		while (stck->top() != v)
		{
			vert = (Vertex*) stck->top();
			//cout << w << " ";
			component.push_back(vert->info.getID());
			stackMember[vert->index] = false;
			stck->pop();
		}
		vert = (Vertex*) stck->top();
		//cout << w << "\n";
		component.push_back(vert->info.getID());
		if(component.size()>1)
			this->SCCs.push_back(component);
		stackMember[vert->index] = false;
		stck->pop();
	}
}


void Graph::SCC()
{
	int *discovered = new int[vertexSet.size()];
	int *early= new int[vertexSet.size()];
	bool *stackMember = new bool[vertexSet.size()];
	stack<Vertex*> *stck = new stack<Vertex*>();

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		vertexSet.at(i)->index = i;
		discovered[i] = -1;
		early[i] = -1;
		stackMember[i] = false;
	}

	for (unsigned int i = 0; i < vertexSet.size(); i++){
		if (discovered[i] == -1)
			SCCUtil(vertexSet.at(i), discovered, early, stck, stackMember);

	}
}
