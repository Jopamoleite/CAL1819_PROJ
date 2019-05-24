/*
 * citySightseeing.cpp
 */

#include<iostream>
#include <unordered_map>
#include <queue>
#include <utility>
#include <algorithm>

#include "citySightseeing.h"
#include "Graph.h"

using namespace std;

vector<VertexInfo> dijkstraShortestRoute(Graph graph, VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

	//vector<VertexInfo> route;
	vector<VertexInfo> shortest_path = graph.dijkstraPathToNearestPOI(start, finish, pois);
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

	return shortest_path;
}

/*
class Helper{
	unsigned long id;
	vector<Person> people;
public:
	Helper(unsigned long id, vector<Person> people){
		this->id = id;
		this->people = people;
	}
	unsigned long getID() const { return this->id; }
	vector<Person> getPeople() const { return this->people; }
	void addPerson(const Person p) { this->people.push_back(p); }
	bool operator<(const Helper& h1) const{
		if(this->people.size() < h1.getPeople().size()){
			return true;
		}
		return false;
	}
};*/

vector<vector<unsigned long>> dividePeople(vector<Person> people, vector<unsigned long> pois, int bus_capacity){

}

void secondIteration(VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

}
