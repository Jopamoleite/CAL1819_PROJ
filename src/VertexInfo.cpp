/*
 * VertexInfo.cpp
 */
#include <math.h>

#include "VertexInfo.h"

using namespace std;

double VertexInfo::distance_between_points(const VertexInfo &v) const{
	return sqrt(pow(this->getX()-v.getX(), 2) + pow(this->getY()-v.getY(), 2));
}

VertexInfo::VertexInfo(unsigned long id){
	this->id = id;
	this->x = 0;
	this->y = 0;
	this->latitude = 0;
	this->longitude = 0;
	this->isPOI = false;
}

VertexInfo::VertexInfo(unsigned long id, double x, double y, double latitude, double longitude){
	this->id = id;
	this->x = x;
	this->y = y;
	this->latitude = latitude;
	this->longitude = longitude;
	this->isPOI = false;
}


void VertexInfo::addTag(string tag){
	this->tag = tag;
	this->isPOI = true;
}

bool VertexInfo::operator== (const VertexInfo & obj) const{
	if(this->getID() == obj.getID()){
		return true;
	}
	return false;
}

double VertexInfo::operator-(const VertexInfo& v) const{
	return distance_between_points(v);
}
