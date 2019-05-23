#include "Graph.h"
#include "map.h"
#include "MutablePriorityQueue.h"
#include "VertexInfo.h"

#include <iostream>
#include <string>

using namespace std;

const int NUMBER_OF_OPTIONS = 5;

void show_menu_options();

int main(){
	cout << " ----------------" << endl;
	cout << "|CITY SIGHTSEEING|" << endl;
	cout << " ----------------" << endl << endl;

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
			break;
		}while(true);
		cout << endl << endl;;

		switch(option){
		case 1:{
			cout << "Name of the city: ";
			string city;
			cin >> city;
			graph = readGraph(city);
			break;
		}
		case 2:
			break;
		case 3:
			if(graph.getNumVertex() == 0){
				cout << "Graph doesn't exist yet!" << endl;
				break;
			}
			graph.SCC();
			/*for(unsigned int i = 0; i < graph.getSCCs().size(); i++){
				for(unsigned int j = 0; j < graph.getSCCs().at(i).size(); j++){
					cout << graph.getSCCs().at(i).at(j) << " ";
				}
				cout << endl;
			}*/
			break;
		case 4:
			if(graph.getNumVertex() == 0){
				cout << "Graph doesn't exist yet!" << endl;
				break;
			}
			viewGraph(graph);
			break;
		case 5:
			break;
		default:
			cerr << "ERROR!!!!" << endl;
			return -1;
		}
	}while(option != NUMBER_OF_OPTIONS);

	getchar();
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
