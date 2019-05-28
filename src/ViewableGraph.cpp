#include "ViewableGraph.h"
#include "map.h"

ViewableGraph::ViewableGraph(){}

ViewableGraph::ViewableGraph(Graph graph){
	this->graph = graph;
	this->gv = nullptr;
}

GraphViewer* ViewableGraph::getGraphViewer(){
	return this->gv;
}

Graph ViewableGraph::getGraph(){
	return this->graph;
}

void ViewableGraph::setGraph(Graph graph){
	this->graph = graph;
}

bool ViewableGraph::openViewGraph(){
	if(this->graph.getVertexSet().size() == 0)
		return false;
	this->gv = viewGraph(this->graph);
		return true;
}


