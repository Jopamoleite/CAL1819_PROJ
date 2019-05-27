#include "Graph.h"
#include "map.h"
#include "MutablePriorityQueue.h"
#include "VertexInfo.h"
#include "graphviewer.h"
#include "citySightseeing.h"
#include "Person.h"

#include <iostream>
#include <string>

using namespace std;

const int NUMBER_OF_OPTIONS = 5;
unsigned long Person::seq_id = 1;

void show_menu_options();

void normalize(string &s){
	for(unsigned int i = 0; i < s.length(); i++){
		if(i == 0){
			s[i] = toupper(s[i]);
		}else{
			s[i] = tolower(s[i]);
		}
	}
}

int main(){
	cout << " ----------------" << endl;
	cout << "|CITY SIGHTSEEING|" << endl;
	cout << " ----------------" << endl << endl;

	GraphViewer *gv = new GraphViewer(2000, 2000, false);

	int option;
	Graph graph;
	do{
		show_menu_options();
		cout << "Option: ";
		do{
			cin >> option;
			if(cin.fail()){
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid option. Try again: ";
				continue;
			}
			else if(option < 1 || option > NUMBER_OF_OPTIONS){
				cout << "Invalid option. Try again: ";
				continue;
			}
			cin.ignore(10000, '\n');
			cin.clear();
			break;
		}while(true);
		cout << endl << endl;;

		switch(option){
		case 1:{
			cout << "Name of the city: ";
			string city;
			do{
				getline(cin, city);
				normalize(city);
				if(city == "Aveiro" || city == "Braga" || city == "Coimbra" || city == "Ermesinde" || city == "Fafe" || city == "Gondomar" || city == "Lisboa" || city == "Maia" || city == "Porto" || city == "Portugal" || city == "Viseu")
					break;
				cout << "Invalid city name. Try again with one of the following:\n" << ">Aveiro\n>Braga\n>Coimbra\n>Ermesinde\n>Fafe\n>Gondomar\n>Lisboa\n>Maia\n>Porto\n>Portugal\n>Viseu\nName the city: ";
			}while(true);
			graph = readGraph(city);
			break;
		}
		case 2:
			break;
		case 3:{
			if(graph.getNumVertex() == 0){
				cout << "Graph doesn't exist yet!" << endl;
				break;
			}
			graph.SCC();
			for(unsigned int i = 0; i < graph.getSCCs().size(); i++){
				for(unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++){
					gv->setVertexColor(graph.getSCCs().at(i).at(j), "red");
				}
			}

			//TEST DIVIDE PEOPLE
			vector<unsigned long> pois = {25504003, 1243857999};
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
			vector<vector<unsigned long>> div_pois = dividePeople(people, tmp_pois, 0);
			for(size_t i = 0; i < div_pois.size(); i++){
				cout << "Path: ";
				for(size_t j = 0; j < div_pois[i].size(); j++){
					cout << div_pois[i][j] << " ";
				}
				cout << endl;
			}

			//TEST DIJKSTA
			/*VertexInfo v(25504003);
			gv->setVertexColor(25504003, "blue");
			VertexInfo v1(1243857999);
			gv->setVertexColor(1243857999, "blue");
			VertexInfo v2(25504005);
			gv->setVertexColor(25504005, "blue");
			VertexInfo v3(25504006);
			gv->setVertexColor(25504006, "blue");
			VertexInfo v4(281726450);
			gv->setVertexColor(281726450, "blue");
			VertexInfo v5(25504011);
			gv->setVertexColor(25504011, "blue");
			vector<VertexInfo> vec = {v1, v3, v2, v4};
			vec = dijkstraShortestRoute(graph, v, vec, v5);
			cout << vec.size() << endl;
			for(size_t i = 0; i < vec.size(); i++){
				if(!(vec[i] == v) && !(vec[i] == v1) && !(vec[i] == v2) && !(vec[i] == v3) && !(vec[i] == v4) && !(vec[i] == v5))
					gv->setVertexColor(vec[i].getID(), "black");
			}*/
			break;
		}
		case 4:
			if(graph.getNumVertex() == 0){
				cout << "Graph doesn't exist yet!" << endl;
				break;
			}
			viewGraph(graph, gv);
			break;
		case 5:
			break;
		default:
			cerr << "ERROR!!!!" << endl;
			return -1;
		}
	}while(option != NUMBER_OF_OPTIONS);

	return 0;
}

void show_menu_options(){
	cout << "Options: " << endl;
	cout << "	1- Import Graph;" << endl;
	cout << "	2- Import Client Information;" << endl;
	cout << "	3- Create Routes (make sure you have imported one graph and the client information);" << endl;
	cout << "	4- See Imported City (make sure you have imported one graph);" << endl;
	cout << "	5- Exit." << endl;
}
