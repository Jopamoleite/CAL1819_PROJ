/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited = false;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	void setInfo(const T);
	double getDist() const;
	Vertex *getPath() const;
	vector<Edge<T>> getAdjEdges() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
void Vertex<T>::setInfo(const T info){
	this->info = info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template<class T>
vector<Edge<T>> Vertex<T>::getAdjEdges() const{
	return this->adj;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	Vertex<T> * getDest() const;
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const {return dest;}
/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool addEdge(const T &sourc, const T &dest);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	Vertex<T> * initSingleSource(const T &origin);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
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
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest) {
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
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) { 
	for (auto v : vertexSet) {
		v->dist = INF;v->path = nullptr; 
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
template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) { 
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
template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {

	for(unsigned int i = 0; i<vertexSet.size(); i++){
		vertexSet.at(i)->dist = INF;
		vertexSet.at(i)->path = NULL;
		vertexSet.at(i)->processing = false;
		vertexSet.at(i)->visited = false;
	}

	Vertex<T>* start = findVertex(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(start);
	start->dist = 0;

	Vertex<T> *v;

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


}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;
	auto v = findVertex(dest);
	if  (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for ( ; v != nullptr; v = v->path) 
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

/*
void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st,
                    bool stackMember[])
{
    static int time = 0;

    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;

    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;  // v is current adjacent of 'u'

        // If v is not visited yet, then recur for it
        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, st, stackMember);

            low[u]  = min(low[u], low[v]);
        }else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }

    int w = 0;  // To store stack extracted vertices
    if (low[u] == disc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
            cout << w << " ";
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        cout << w << "n";
        stackMember[w] = false;
        st->pop();
    }
}

void Graph::SCC()
{
    int *disc = new int[V];
    int *low = new int[V];
    bool *stackMember = new bool[V];
    stack<int> *st = new stack<int>();

    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }

    for (int i = 0; i < V; i++)
        if (disc[i] == -1)
            SCCUtil(i, disc, low, st, stackMember);
} */


#endif /* GRAPH_H_ */
