#ifndef POINT_H
#define POINT_H

struct Point {
    float x,y,z;
    Point(float a=0, float b=0, float c=0) {set(a,b,c);}
    void set(float a, float b, float c) {x=a;y=b;z=c;}
    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getZ() const {
        return z;
    }
};

#endif
