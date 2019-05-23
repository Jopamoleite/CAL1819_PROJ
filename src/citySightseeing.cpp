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
		for(size_t j = 0; j < tmp_path.size(); j++){
			if(shortest_path.at(shortest_path.size()-1).getID() != tmp_path.at(j).getID())
				shortest_path.push_back(tmp_path.at(j));
		}
	}

	return shortest_path;
}

template <class T>
bool compareValues(const T &t1, const T &t2){
	return t1.second.size() < t2.second.size();
}

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
};

vector<vector<unsigned long>> dividePeople(vector<Person> people, int bus_capacity){
	typedef unordered_map<unsigned long, vector<Person>, idHash, idHash> POIS_MAP;

	POIS_MAP pois_numbers;

	for(size_t i = 0; i < people.size(); i++){
		vector<unsigned long> pois = people[i].getPois();
		for(size_t j = 0; j < pois.size(); j++){
			try{
				vector<Person>& person = pois_numbers.at(pois[j]);
				person.push_back(people[i]);
			}
			catch(out_of_range &e){
				vector<Person> v;
				v.push_back(people[i]);
				pair<unsigned long, vector<Person>> p = make_pair(pois[j], v);
				pois_numbers.insert(p);
			}
		}
	}

	priority_queue<Helper> pq;
	for(POIS_MAP::iterator it = pois_numbers.begin(); it != pois_numbers.end(); it++){
		Helper h((*it).first, (*it).second);
		pq.push(h);
	}

	vector<vector<unsigned long>> result;
	vector<unsigned long> points;

	while(!pq.empty()){
		int cap = bus_capacity;
		points.clear();
		while(cap > 0){
			Helper h = pq.top();
			pq.pop();
			vector<Person> vp = h.getPeople();
			while(cap > 0 && vp.size() > 0){
				Person p1 = vp.back();
				vp.pop_back();
				vector<unsigned long> pois = p1.getPois();
				for(size_t i = 0; i < pois.size(); i++){
					if(find(points.begin(), points.end(), pois[i]) == points.end()){
						points.push_back(pois[i]);
					}
				}
				cap--;
			}

			if(pq.empty()){
				break;
			}
		}
		result.push_back(points);
	}
	return result;
}

void secondIteration(VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

}
