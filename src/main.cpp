#include "Graph.h"
#include "map.h"
#include "MutablePriorityQueue.h"
#include "VertexInfo.h"

#include <iostream>

using namespace std;

int main(){

	cout << "Ola\n";
	Graph<VertexInfo> graph = readGraph("Porto");

	cout << "Ola";

	for(unsigned int i = 0; i < graph.getVertexSet().size(); i++){
		cout << graph.getVertexSet().at(i)->getInfo().getID();
		cout << "   " << graph.getVertexSet().at(i)->getInfo().getX();
		cout << "   " << graph.getVertexSet().at(i)->getInfo().getY();
	}

	return 0;
}
