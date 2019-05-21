#ifndef TYPES_H
#define TYPES_H

#include <string>

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

        unsigned long getID(){return id;}

        bool operator == (VertexInfo const &obj){
            return id == obj.getID;
        }
};

#endif