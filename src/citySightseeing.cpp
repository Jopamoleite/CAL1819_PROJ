/*
 * citySightseeing.cpp
 */

#include<iostream>
#include <unordered_map>
#include <queue>
#include <utility>
#include <algorithm>
#include <unordered_set>

#include "citySightseeing.h"
#include "Graph.h"
#include "Bigraph.h"

using namespace std;

vector<VertexInfo> dijkstraShortestRoute(Graph graph, VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

	vector<VertexInfo> tmp;
	vector<VertexInfo> shortest_path;
	unordered_set<VertexInfo, VertexInfoHash, VertexInfoComparator> pois_set;
	VertexInfo last_found;

	for(size_t i = 0; i < pois.size(); i++)
		pois_set.insert(pois.at(i));

	graph.dijkstraPathToNearestPOI(start, pois_set, last_found, shortest_path);

	while(!pois_set.empty()){
		start = last_found;
		graph.dijkstraPathToNearestPOI(start, pois_set, last_found, shortest_path);
	}

	graph.dijkstraShortestPath(last_found, finish);
	tmp = graph.getPath(last_found, finish);

	for(size_t j = 0; j < tmp.size(); j++){
		if(shortest_path.size() == 0 || shortest_path.at(shortest_path.size()-1).getID() != tmp.at(j).getID()){
			shortest_path.push_back(tmp.at(j));
		}
	}

	return shortest_path;
}


vector<pair<vector<unsigned long>, vector<Person>>> dividePeople(vector<Person> people, vector<unsigned long> pois, int bus_capacity){
	Bigraph graph;
	for(size_t i = 0; i < pois.size(); i++){
		graph.addPOIVertex(pois[i]);
	}
	for(size_t i = 0; i < people.size(); i++){
		graph.addPersonVertex(people[i]);
		vector<unsigned long> vp = people[i].getPois();
		for(size_t j = 0; j < vp.size(); j++){
			graph.addBigraphEdge(people[i], vp[j]);
		}
	}

	vector<pair<vector<unsigned long>, vector<Person>>> result;
	pair<vector<unsigned long>, vector<Person>> p;

	int numEdges = 0;
	vector<POIVertex*> vpois = graph.getPOIs();
	for(size_t i = 0; i < vpois.size(); i++){
		numEdges += (vpois[i]->getIncoming()).size();
	}

	while(numEdges > 0){
		if(bus_capacity < 0){
			p = graph.getPeopleForBus(numEdges);
		}
		else{
			p = graph.getPeopleForBus(numEdges, bus_capacity);
		}
		result.push_back(p);
	}

	return result;
}
