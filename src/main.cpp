#include "Graph.h"
#include "map.h"
#include "MutablePriorityQueue.h"
#include "VertexInfo.h"
#include "graphviewer.h"
#include "citySightseeing.h"
#include "Person.h"
#include "ViewableGraph.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

const int NUMBER_OF_OPTIONS = 4;
unsigned long Person::seq_id = 1;

void show_start_options();
void show_person_options();
void show_create_person_options();
void show_route_options();
void save_people(vector<Person> people, string city);
vector<Person> import_people(string city);

void normalize(string &s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (i == 0) {
			s[i] = toupper(s[i]);
		} else {
			s[i] = tolower(s[i]);
		}
	}
}

int main() {
	cout << " ----------------" << endl;
	cout << "|CITY SIGHTSEEING|" << endl;
	cout << " ----------------" << endl << endl;

	int option;
	int optionAdd;
	Graph graph;
	ViewableGraph view;
	vector<Person> people;
	srand(time(NULL));

	do {
		show_start_options();
		string city;
		do{
			getline(cin, city);
			normalize(city);
			if(city == "Aveiro" || city == "Braga" || city == "Coimbra" || city == "Ermesinde" || city == "Fafe" || city == "Gondomar" || city == "Lisboa" || city == "Maia" || city == "Porto"  || city == "Viseu")
				break;
			cout << "Invalid city name. Try again with one of the following:\n" << ">Aveiro\n>Braga\n>Coimbra\n>Ermesinde\n>Fafe\n>Gondomar\n>Lisboa\n>Maia\n>Porto\n>Viseu\nName the city: ";
		}while(true);
		graph = readGraph(city);
		graph.SCC();
		view.setGraph(graph);

		show_person_options();
		cout << "Option: ";
		do {
			cin >> option;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid option. Try again: ";
				continue;
			} else if (option < 1 || option > NUMBER_OF_OPTIONS) {
				cout << "Invalid option. Try again: ";
				continue;
			}
			cin.ignore(10000, '\n');
			cin.clear();
			break;
		} while (true);
		cout << endl;

		switch(option){
		case 1:{
			vector<unsigned long> temp_pois;
			do {
				show_create_person_options();
				cout << "Option: ";
				do {
					cin >> optionAdd;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Invalid option. Try again: ";
						continue;
					} else if (optionAdd < 1 || optionAdd > 7) {
						cout << "Invalid option. Try again: ";
						continue;
					}
					cin.ignore(10000, '\n');
					cin.clear();
					break;
				} while (true);
				cout << endl << endl;

				switch (optionAdd) {
				case 1:{
					cout << "Id of the POI: ";
					unsigned long poi;
					do {
						cin >> poi;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << "Please input a number: ";
							continue;
						}
						cin.ignore(10000, '\n');
						cin.clear();
						break;
					} while (true);

					bool leave = false;
					bool found = false;
					vector<unsigned long> SCC;

					for(unsigned int i = 0; i < temp_pois.size(); i++){
						if(temp_pois.at(i) == poi){
							leave = true;
							break;
						}
					}
					if(leave){
						cout << "POI already added!\n";
						break;
					}
					leave = false;

					for(unsigned int i = 0; i < graph.getSCCs().size(); i++){
						if(leave || found)
							break;
						SCC = graph.getSCCs().at(i);
						for(unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++){
							if(leave || found)
								break;
							VertexInfo v(graph.getSCCs().at(i).at(j));
							if(graph.getSCCs().at(i).at(j) == poi){
								if(graph.findVertex(v)->getInfo().getIsPOI()){
									found = true;
									SCC = graph.getSCCs().at(i);
								}else{
									cout << "Vertex is not a POI!\n";
									leave = true;
								}
							}
						}
					}
					if(leave)
						break;
					if(!found){
						cout << "Vertex is not reachable!\n";
						break;
					}
					if(temp_pois.size() == 0){
						temp_pois.push_back(poi);
						cout << "Added POI!\n";
						break;
					}

					leave = false;

					for(unsigned int i = 0; i < temp_pois.size(); i++){
						if(find(SCC.begin(),SCC.end(),temp_pois.at(i)) == SCC.end()){
							leave = true;
							found = false;
							break;
						}
					}

					if(!found){
						cout << "POI not connected to the other POI!\n";
						break;
					}

					if(found){
						cout << "POI added!\n";
						temp_pois.push_back(poi);
					}
					break;
				}
				case 2:{
					if(temp_pois.size() == 0){
						cout << "No POI added yet, check with option 3!\n";
						break;
					}

					bool found = false;
					vector<unsigned long> SCC;
					for(unsigned int i = 0; i < graph.getSCCs().size(); i++){
						if(found)
							break;
						for(unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++){
							if(graph.getSCCs().at(i).at(j) == temp_pois.at(0)){
								found = true;
								SCC = graph.getSCCs().at(i);
								break;
							}
						}
					}
					if(!found){
						cout << "Not found somehow?\n";
						break;
					}

					int counter = 0;
					vector<unsigned long> newPoi;
					sort(SCC.begin(), SCC.end());
					sort(temp_pois.begin(), temp_pois.end());
					set_difference(SCC.begin(), SCC.end(), temp_pois.begin(), temp_pois.end(), inserter(newPoi, newPoi.begin()));

					for(unsigned int i = 0; i < newPoi.size(); i++){
						VertexInfo v(newPoi.at(i));
						if(graph.findVertex(v)->getInfo().getIsPOI()){
							cout << "Possible POI " << newPoi.at(i) << endl;
							counter++;
						}
					}
					if(counter == 0){
						cout << "No more possible POI!\n";
					}
					break;
				}
				case 3:
				{
					vector<vector<unsigned long>> connectedPoi;
					for(unsigned int i = 0; i < graph.getSCCs().size(); i++){
						vector<unsigned long> v;
						connectedPoi.push_back(v);
						for(unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++){
							VertexInfo v(graph.getSCCs().at(i).at(j));
							if(graph.findVertex(v)->getInfo().getIsPOI())
								connectedPoi.at(i).push_back(graph.getSCCs().at(i).at(j));
						}
					}

					for(unsigned int i = 0; i < connectedPoi.size(); i++){
						if(connectedPoi.at(i).size()>1)
							cout << "Connected POI:";
						for(unsigned int j = 0; j < connectedPoi.at(i).size(); j++){
							if(connectedPoi.at(i).size()>1)
								cout << " " << connectedPoi.at(i).at(j);
						}
						if(connectedPoi.at(i).size()>1)
							cout << endl;
					}
					break;
				}
				case 4:{
					Person p(temp_pois);
					people.push_back(p);
					temp_pois.clear();
					break;
				}
				case 5:{
					save_people(people, city);
					break;
				}
				case 6:{
					continue;
				}
				case 7:{
					return 0;
				}
				default:
					return -1;
				}

			} while (optionAdd != 5);
			break;
		}
		case 2:{
			people = import_people(city);
			break;
		}
		case 3:{
			continue;
		}
		case 4:
			return 0;
		}

		do{
			show_route_options();
			cout << "Option: ";
			do {
				cin >> option;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid option. Try again: ";
					continue;
				} else if (option < 1 || option > 4) {
					cout << "Invalid option. Try again: ";
					continue;
				}
				cin.ignore(10000, '\n');
				cin.clear();
				break;
			} while (true);
			cout << endl;
			switch(option){
			case 1: {
				if (graph.getNumVertex() == 0) {
					cout << "Graph doesn't exist!" << endl;
					break;
				}
				view = ViewableGraph(graph);
				view.openViewGraph();
				for (unsigned int i = 0; i < graph.getSCCs().size(); i++) {
					for (unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++) {
						view.getGraphViewer()->setVertexColor(graph.getSCCs().at(i).at(j), "red");
					}
				}
				break;
			}
			case 2:{
				if(graph.getNumVertex() == 0){
					cout << "Graph doesn't exist!" << endl;
					break;
				}

				cout << "Bus capacity (-1 not considers capacity): " << endl;
				int bus_capacity = 0;
				do {
					cin >> bus_capacity;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Invalid option. Try again: ";
						continue;
					}
					cin.ignore(10000, '\n');
					cin.clear();
					break;
				} while (true);
				cout << endl;

				vector<unsigned long> tmp_pois;
				for(size_t i = 0; i < people.size(); i++){
					for(size_t j = 0; j < people[i].getPois().size(); j++){
						tmp_pois.push_back(people[i].getPois().at(j));
					}
				}

				clock_t beginDivide = clock();

				vector<pair<vector<unsigned long>, vector<Person>>> pairs = dividePeople(people, tmp_pois, bus_capacity);

				clock_t endDivide = clock();
				double elapsed_secsDivide = double(endDivide - beginDivide) / CLOCKS_PER_SEC;
				cout << "Elapsed time for algorithm that groups turists: " << elapsed_secsDivide << endl;


				for(size_t i = 0; i < pairs.size(); i++){
					vector<VertexInfo> v;
					for(size_t j = 0; j < (pairs[i].first).size(); j++){
						v.push_back(VertexInfo(pairs[i].first[j]));
					}

					bool found = false;
					vector<unsigned long> SCC;
					for(unsigned int i = 0; i < graph.getSCCs().size(); i++){
						if(found)
							break;
						for(unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++){
							if(graph.getSCCs().at(i).at(j) == v.at(0).getID()){
								found = true;
								SCC = graph.getSCCs().at(i);
								break;
							}
						}
					}
					vector<unsigned long> notPOI;
					for(unsigned int i = 0; i < SCC.size(); i++){
						VertexInfo vert(SCC.at(i));
						if(!graph.findVertex(vert)->getInfo().getIsPOI()){
							notPOI.push_back(SCC.at(i));
						}
					}
					int originIndex, destinyIndex;
					originIndex = rand() % notPOI.size();
					destinyIndex = rand() % notPOI.size();
					VertexInfo origin(notPOI.at(originIndex));
					VertexInfo destiny(notPOI.at(destinyIndex));

					clock_t beginDijkstra = clock();

					vector<VertexInfo> path = dijkstraShortestRoute(graph, origin , v, destiny);

					clock_t endDijkstra = clock();
					double elapsed_secsDijkstra = double(endDijkstra - beginDijkstra) / CLOCKS_PER_SEC;
					cout << "Elapsed time for Dijkstra: " << elapsed_secsDijkstra << endl;
					if(view.getViewerExists()){
						for(size_t i = 0; i < path.size(); i++){
							view.getGraphViewer()->setVertexColor(path[i].getID(), "black");
						}
						for(size_t i = 0; i < v.size(); i++){
							view.getGraphViewer()->setVertexColor(v[i].getID(), "blue");
						}
					}

				}
				break;
			}
			case 3:{
				break;
			}
			case 4:{
				return 0;
			}
			}
		}while(option != 3 && option != 4);
	}while(true);

	return 0;
}

void show_start_options() {
	cout << "IMPORT GRAPH: " << endl;
	cout << "   Select city: ";
}

void show_person_options() {
	cout << "PERSON OPTIONS: " << endl;
	cout << "   1: Create tourist;" << endl;
	cout << "   2: Import tourist from file;" << endl;
	cout << "   3: Import new graph;" << endl;
	cout << "   4: Exit." << endl;
}

void show_create_person_options(){
	cout << "Options: " << endl;
	cout << "   1: Add POI to Person;" << endl;
	cout << "   2: See POI connected to existing ones;" << endl;
	cout << "   3: Show all POIs connected to each other;" << endl;
	cout << "   4: Add actual Person to the solution;" << endl;
	cout << "   5: Save Persons to file and continue;" << endl;
	cout << "   6: Go back to Person options;" << endl;
	cout << "   7: Exit from program." << endl;
}

void show_route_options(){
	cout << "CREATE ROUTE OPTIONS: " << endl;
	cout << "   1: Show graph;" << endl;
	cout << "   2: Divide people and create routes for buses;" << endl;
	cout << "   3: Import new graph;" << endl;
	cout << "   4: Exit from program." << endl;
}

void save_people(vector<Person> people, string city){
	ofstream f("people_"+city+".txt");
	f << people.size() << endl;
	for(size_t i = 0; i < people.size(); i++){
		f << people[i].getID() << endl;
		vector<unsigned long> pois = people[i].getPois();
		f << pois.size() << endl;
		for(size_t j = 0; j < pois.size(); j++){
			f << pois[j] << endl;
		}
	}
	f.close();
}

vector<Person> import_people(string city){
	vector<Person> v;
	unsigned long id, poi;
	size_t numPersons, numPOIs;
	vector<unsigned long> pois;

	string line;
	ifstream f("people_"+city+".txt");
	getline(f, line);
	numPersons = stoul(line);
	for(size_t i = 0; i < numPersons; i++){
		getline(f, line);
		id = stoul(line);
		getline(f, line);
		numPOIs = stoul(line);
		for(size_t j = 0; j < numPOIs; j++){
			getline(f, line);
			poi = stoul(line);
			pois.push_back(poi);
		}
		Person p(id, pois);
		v.push_back(p);
		pois.clear();
	}
	f.close();

	return v;
}
