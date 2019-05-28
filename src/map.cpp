/**
 * map.cpp
 *
 * Defined functions of map.h header file
 */

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "map.h"
#include "edgetype.h"

using namespace std;

Graph readGraph(string name){

	Graph g;

	string map_dir = "mapas/"+name+"/";
	ifstream f(map_dir+"T03_nodes_X_Y_"+name+".txt");
	ifstream f1(map_dir+"T03_nodes_lat_lon_"+name+".txt");

	int lines = 0;
	string file_line;

	getline(f, file_line);

	lines = stoi(file_line);

	getline(f1, file_line);

	unsigned long ID;
	double X, Y, lat, lon;

	while(lines > 0){
		getline(f, file_line);
		file_line = file_line.substr(1);
		ID = stoi(file_line.substr(0, file_line.find(",")));
		file_line = file_line.substr(file_line.find(",")+1);
		X = stod(file_line.substr(0, file_line.find(",")));
		file_line = file_line.substr(file_line.find(",")+1);
		Y = stod(file_line.substr(0, file_line.find(")")));

		getline(f1, file_line);
		file_line = file_line.substr(file_line.find(",")+1);
		lat = stod(file_line.substr(0, file_line.find(",")));
		file_line = file_line.substr(file_line.find(",")+1);
		lon = stod(file_line.substr(0, file_line.find(")")));

		VertexInfo v(ID, X, Y, lat, lon);
		g.addVertex(v);

		lines--;
	}

	f.close();
	f1.close();

	f.open(map_dir+"T03_edges_"+name+".txt");

	getline(f, file_line);
	lines = stoi(file_line);

	unsigned long ID_origin, ID_destiny;

	while(lines > 0){
		getline(f, file_line);
		file_line = file_line.substr(1);

		ID_origin = stoi(file_line.substr(0, file_line.find(",")));
		file_line = file_line.substr(file_line.find(",")+1);

		ID_destiny = stod(file_line.substr(0, file_line.find(")")));

		VertexInfo origin(ID_origin, 0, 0, 0, 0);
		VertexInfo destiny(ID_destiny, 0, 0, 0, 0);

		g.addEdge(origin, destiny);

		lines--;
	}

	f.close();

	f.open(map_dir+"T03_tags_"+name+".txt");
	getline(f, file_line);
	lines = stoi(file_line);

	int number_nodes = 0;
	string tag;

	while(lines > 0){
		getline(f, file_line);
		tag = file_line.substr(file_line.find("=")+1);

		getline(f, file_line);
		number_nodes = stoi(file_line);

		while(number_nodes > 0){
			getline(f, file_line);
			ID = stoi(file_line);
			Vertex *v = g.findVertex(VertexInfo(ID, 0, 0, 0, 0));
			VertexInfo vi = v->getInfo();
			vi.addTag(tag);
			v->setInfo(vi);
			number_nodes--;
		}

		lines--;
	}

	f.close();
	return g;
}

int viewGraph(Graph graph, GraphViewer* gv){

	gv->createWindow(2000, 2000);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	vector<Vertex*> vertexSet = graph.getVertexSet();
	Vertex* currentVertex = new Vertex(VertexInfo(0,0,0,0,0));
	int edgeID = 0;
	double offsetX = vertexSet.at(0)->getInfo().getX();
	double offsetY = vertexSet.at(0)->getInfo().getY();

	vector<Edge> edges;
	vector<Vertex> auxiliar_edges;
	vector<Edge> currentEdges;

	for(size_t i = 0; i < vertexSet.size(); i++){
		currentVertex = vertexSet.at(i);
		gv->addNode(currentVertex->getInfo().getID(), currentVertex->getInfo().getX()-offsetX, currentVertex->getInfo().getY()-offsetY);
		/*if(currentVertex->getInfo().getIsPOI()){
			if(currentVertex->getInfo().getTag() == "*"){
				gv->setVertexIcon(currentVertex->getInfo().getID(), "tourism.jpg");
			}
			else{
				gv->setVertexIcon(currentVertex->getInfo().getID(), currentVertex->getInfo().getTag()+".jpg");
			}
		}*/
		currentEdges = currentVertex->getAdjEdges();
		auxiliar_edges.insert(auxiliar_edges.end(), currentEdges.size(), *currentVertex);
		edges.insert(edges.end(), currentEdges.begin(), currentEdges.end());
	}

	for(size_t i = 0; i < edges.size(); i++){
		gv->addEdge(edgeID, auxiliar_edges[i].getInfo().getID(), edges[i].getDest()->getInfo().getID(), EdgeType::DIRECTED);
		edgeID++;
	}

	gv->rearrange();

	return 0;
}
