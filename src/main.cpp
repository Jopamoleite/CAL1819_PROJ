#include "Graph.h"
#include "map.h"
#include "MutablePriorityQueue.h"
#include "VertexInfo.h"
#include "graphviewer.h"
#include "citySightseeing.h"
#include "Person.h"
#include "ViewableGraph.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int NUMBER_OF_OPTIONS = 5;
unsigned long Person::seq_id = 1;

void show_menu_options();
void show_add_person_options();

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
	do {
		show_menu_options();
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
		cout << endl << endl;


		switch (option) {
		case 1:{
			cout << "Name of the city: ";
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
			break;
		}
		case 2:{
			vector<unsigned long> temp_pois;
			do {
				show_add_person_options();
				cout << "Option: ";
				do {
					cin >> optionAdd;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Invalid option. Try again: ";
						continue;
					} else if (optionAdd < 1 || optionAdd > 5) {
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
					//ADICIONAR A PESSOA A ALGUM LADO
					break;
				}
				case 5:{
					break;
				}
				default:
					cerr << "ERROR!!!!" << endl;
					return -1;
				}

			} while (optionAdd != 5 && optionAdd != 4);

			break;
		}
		case 3:{
			if(graph.getNumVertex() == 0){
				cout << "Graph doesn't exist yet!" << endl;
				break;
			}

			for(unsigned int i = 0; i < graph.getSCCs().size(); i++){
				for(unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++){
					view.getGraphViewer()->setVertexColor(graph.getSCCs().at(i).at(j), "red");
				}
			}

			//TEST DIVIDE PEOPLE
			/*vector<unsigned long> pois = {25504003, 1243857999};
			vector<unsigned long> tmp_pois = {25504003, 1243857999, 25504005, 281726450, 25504011};
			Person p(pois);
			pois.clear();
			pois = {25504003, 25504005};
			Person p1(pois);
			pois.clear();
			pois = {25504003, 1243857999};
			Person p2(pois);
			pois.clear();
			pois = {281726450, 1243857999};
			Person p3(pois);
			pois.clear();
			pois = {281726450, 25504011};
			Person p4(pois);
			vector<Person> people = {p, p1, p2, p3, p4};
			vector<pair<vector<unsigned long>, vector<Person>>> pairs = dividePeople(people, tmp_pois, 4);
			for(size_t i = 0; i < pairs.size(); i++){
				cout << "Path: ";
				for(size_t j = 0; j < (pairs[i].first).size(); j++){
					cout << pairs[i].first[j] << " ";
				}
				cout << endl;
			}*/

			//TEST DIJKSTA
			VertexInfo v(1223751712);
			view.getGraphViewer()->setVertexColor(1223751712, "blue");
			VertexInfo v1(430012058);
			view.getGraphViewer()->setVertexColor(430012058, "blue");
			VertexInfo v2(430012046);
			view.getGraphViewer()->setVertexColor(430012046, "blue");
			VertexInfo v3(430012039);
			view.getGraphViewer()->setVertexColor(430012039, "blue");
			VertexInfo v4(1223751572);
			view.getGraphViewer()->setVertexColor(1223751572, "blue");
			VertexInfo v5(420807840);
			view.getGraphViewer()->setVertexColor(420807840, "blue");
			vector<VertexInfo> vec = {v1, v3, v2, v4};
			vec = dijkstraShortestRoute(graph, v, vec, v5);
			cout << vec.size() << endl;
			for(size_t i = 0; i < vec.size(); i++){
				if(!(vec[i] == v) && !(vec[i] == v1) && !(vec[i] == v2) && !(vec[i] == v3) && !(vec[i] == v4) && !(vec[i] == v5))
					view.getGraphViewer()->setVertexColor(vec[i].getID(), "black");
				else cout << "POI: ";
				cout << vec.at(i).getID() << endl;
			}
			break;
		}
		case 4:
			if (graph.getNumVertex() == 0) {
				cout << "Graph doesn't exist yet!" << endl;
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
		case 5:
			break;
		default:
			cerr << "ERROR!!!!" << endl;
			return -1;
		}
	} while (option != NUMBER_OF_OPTIONS);

	return 0;
}

void show_menu_options() {
	cout << "Options: " << endl;
	cout << "	1- Import Graph;" << endl;
	cout << "	2- Import Client Information;" << endl;
	cout
	<< "	3- Create Routes (make sure you have imported one graph and the client information);"
	<< endl;
	cout << "	4- See Imported City (make sure you have imported one graph);"
			<< endl;
	cout << "	5- Exit." << endl;
}

void show_add_person_options() {
	cout << "Options: " << endl;
	cout << "	1- Add POI;" << endl;
	cout << "	2- See POI connected to existing ones;" << endl;
	cout << "	3- Show all POIs connected to each other;" << endl;
	cout << "	4- Finish adding person;" << endl;
	cout << "	5- Abort adding person." << endl;
}
