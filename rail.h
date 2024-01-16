#ifndef __RAIL
#define __RAIL
#include <string>
#include "point.h"
#include <vector>
#include <GL/gl.h>
#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Rail {
public:
    Rail();
    Rail(double tubeRadius, double spaceBetweenRails, const std::vector<Point>curvePoints);
    void drawRail(double radius, int numSides);
    void construire();
    void setPoints(const std::vector<Point> curvePoints);
    void setTubeRadius(double tubeRadius);
    void setSpaceBetweenRails(double spaceBetweenRails);

private:
    double tubeRadius;
    double spaceBetweenRails;
    std::vector<Point> curvePoints;

    void drawCylinderBetweenPoints(Point p1, Point p2, double radius, int numSides, float r, float g, float b);

    
};


#endif
