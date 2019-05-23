/*
 * citySightseeing.cpp
 */

#include<iostream>

#include "citySightseeing.h"

using namespace std;

void firstIteration(Graph graph, VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

	vector<VertexInfo> route;
	vector<VertexInfo> shortest_path;
	route.push_back(start);

	for(size_t i = 0; i < pois.size(); i++){
		route.push_back(pois.at(i));
	}

	route.push_back(finish);

	for(size_t i = 0; i < route.size()-1; i++){
		graph.dijkstraShortestPath(route.at(i));
		vector<VertexInfo> tmp_path = graph.getPath(route.at(i), route.at(i+1));
		for(size_t j = 0; j < tmp_path.size(); j++)
			shortest_path.push_back(tmp_path.at(j));
	}

	for(size_t i = 0; i < shortest_path.size(); i++)
		cout << shortest_path.at(i).getID() << endl;
}

void secondIteration(VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

}
