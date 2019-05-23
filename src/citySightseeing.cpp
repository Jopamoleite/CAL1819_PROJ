/*
 * citySightseeing.cpp
 */

#include <unordered_map>
#include <queue>
#include <utility>

#include "citySightseeing.h"
#include "Graph.h"

using namespace std;

/*template <class T>
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

		while(cap > 0){
			Helper h = pq.top();
			pq.pop();
			/*
			 * Add persons to here
			 */
			/*if(pq.empty()){
				break;
			}
		}
	}
	return result;
}*/

void firstIteration(VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

}

void secondIteration(VertexInfo start, vector<VertexInfo> pois, VertexInfo finish){

}
