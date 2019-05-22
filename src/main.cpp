#include "Graph.h"
#include "map.h"
#include "MutablePriorityQueue.h"
#include "VertexInfo.h"

#include <iostream>

using namespace std;

int main(){
	Graph<VertexInfo> graph = readGraph("Porto");
	viewGraph(graph);
	getchar();
	return 0;
}
