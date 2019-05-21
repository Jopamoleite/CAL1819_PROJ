#ifndef VERTEXINFO_H
#define VERTEXINFO_H

#include <string>

using namespace std;

class VertexInfo{
    private:
        unsigned long id;
        double x;
        double y;
        double latitude;
        double longitude;
        bool isPOI;
        string tag;

    public:
        VertexInfo(unsigned long id, double x, double y, double latitude, double longitude){
                    this->id = id;
                    this->x = x;
                    this->y = y;
                    this->latitude = latitude;
                    this->longitude = longitude;
                    this->isPOI = false;
        }

        double getX(){return x;}

        double getY(){return y;}

        double getLatitude(){ return latitude; }

        double getLongitude(){ return longitude; }

        void addTag(string tag){
            this->tag = tag;
            this->isPOI = true;
        }

        unsigned long getID() const {return id;}

        bool operator== (const VertexInfo & obj) const{
                	if(this->getID() == obj.getID()){
                		return true;
                	}
                    return false;
                }
};

#endif
