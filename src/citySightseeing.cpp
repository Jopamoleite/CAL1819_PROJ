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

	/*route.push_back(start);

	for(size_t i = 0; i < pois.size(); i++){
		route.push_back(pois.at(i));
	}



	route.push_back(finish);

	for(size_t i = 0; i < route.size()-1; i++){
		graph.dijkstraShortestPath(route.at(i), route.at(i+1));
		vector<VertexInfo> tmp_path = graph.getPath(route.at(i), route.at(i+1));
		for(size_t j = 0; j < tmp_path.size(); j++){
			if(shortest_path.size() == 0 || shortest_path.at(shortest_path.size()-1).getID() != tmp_path.at(j).getID()){
				shortest_path.push_back(tmp_path.at(j));
			}
		}
	}*/

	//return shortest_path;
}


vector<vector<unsigned long>> dividePeople(vector<Person> people, vector<unsigned long> pois, int bus_capacity){

}

void secondIteration(VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

}
