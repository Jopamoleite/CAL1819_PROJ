#ifndef VIEWABLE_GRAPH_H_
#define VIEWABLE_GRAPH_H_

#include "Graph.h"
#include "graphviewer.h"

class ViewableGraph{
	Graph graph;
	GraphViewer *gv;
	bool viewerExists;

public:
	ViewableGraph();
	ViewableGraph(Graph graph);
	GraphViewer* getGraphViewer();
    Graph getGraph();
    bool getViewerExists();
    void setGraph(Graph graph);
    bool openViewGraph();
};


#endif
