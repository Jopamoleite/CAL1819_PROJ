/*
 * Graph.cpp
 */
#include <iostream>
#include <algorithm>
#include <utility>

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

/*void Graph::dijkstraShortestPath(const VertexInfo &origin) {

	for(unsigned int i = 0; i<vertexSet.size(); i++){
		vertexSet.at(i)->dist = INF;
		vertexSet.at(i)->path = NULL;
		vertexSet.at(i)->processing = false;
		vertexSet.at(i)->visited = false;
	}

	Vertex* start = findVertex(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(start);
	start->dist = 0;

	Vertex *v;

	while (!q.empty()){
		v = q.extractMin();
		v->processing = false;
		v->visited = true;
		for(unsigned int i = 0; i<v->adj.size(); i++){
			if(v->adj.at(i).dest->dist > v->dist + v->adj.at(i).weight){
				v->adj.at(i).dest->dist = v->dist + v->adj.at(i).weight;
				v->adj.at(i).dest->path = v;
				if(!v->adj.at(i).dest->processing){
					q.insert(v->adj.at(i).dest->path);
					v->adj.at(i).dest->processing = true;
				}
				else
					q.decreaseKey(v->adj.at(i).dest->path);
			}
		}
	}


}*/

void Graph::dijkstraShortestPath(const VertexInfo &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while( ! q.empty() ) {
		auto v = q.extractMin();
		for(auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
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


void Graph::SCCUtil(Vertex* v, int discovered[], int early[], stack<int> *stck,
		bool stackMember[])
{
	static int time = 0;

	discovered[v->index] = early[v->index] = ++time;
	stck->push(v->index);
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

	int w = 0;  // To store stack extracted vertices
	if (early[v->index] == discovered[v->index])
	{
		while (stck->top() != v->index)
		{
			w = (int) stck->top();
			//cout << w << " ";
			stackMember[w] = false;
			stck->pop();
		}
		w = (int) stck->top();
		//cout << w << "\n";
		stackMember[w] = false;
		stck->pop();
	}
}


void Graph::SCC()
{
	int *discovered = new int[vertexSet.size()];
	int *early= new int[vertexSet.size()];
	bool *stackMember = new bool[vertexSet.size()];
	stack<int> *stck = new stack<int>();

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
