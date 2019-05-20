#ifndef TYPES_H
#define TYPES_H

class VertexInfo{
    private:
        double x;
        double y;
        double id;

    public:
        VertexInfo(double x, double y, double id){
            this->x = x;
            this->y = y;
            this->id = id;
        }

        double getX(){return x;}

        double getY(){return y;}

        double getID(){return id;}

        bool operator == (VertexInfo const &obj){
            return (x == obj.getX && y == obj.getY && id == obj.getID);
        }
};

#endif