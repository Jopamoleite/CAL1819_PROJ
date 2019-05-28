#include "ViewableGraph.h"
#include "map.h"

ViewableGraph::ViewableGraph(){this->viewerExists = false;}

ViewableGraph::ViewableGraph(Graph graph){
	this->graph = graph;
	this->gv = nullptr;
	this->viewerExists = false;
}

GraphViewer* ViewableGraph::getGraphViewer(){
	return this->gv;
}

Graph ViewableGraph::getGraph(){
	return this->graph;
}

bool ViewableGraph::getViewerExists(){
	return this->viewerExists;
}

void ViewableGraph::setGraph(Graph graph){
	this->graph = graph;
}

bool ViewableGraph::openViewGraph(){
	if(this->graph.getVertexSet().size() == 0)
		return false;
	this->viewerExists = true;
	this->gv = viewGraph(this->graph);
		return true;
}


