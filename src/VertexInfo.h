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

        double distance_between_points(const VertexInfo &v) const;

    public:
        VertexInfo(unsigned long id, double x, double y, double latitude, double longitude);

        double getX() const {return x;}

        double getY() const {return y;}

        double getLatitude() const { return latitude; }

        double getLongitude() const { return longitude; }

        unsigned long getID() const {return id;}

        void addTag(string tag);

        bool operator== (const VertexInfo & obj) const;

        double operator-(const VertexInfo& v) const;
};

#endif
