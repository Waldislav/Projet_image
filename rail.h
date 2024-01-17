#ifndef __RAIL
#define __RAIL
#include <string>
#include "point.h"
#include <vector>
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Rail {
public:
    Rail();
    Rail(float tubeRadius, float spaceBetweenRails, const std::vector<Point>curvePoints);
    void construire();
    void setPoints(const std::vector<Point> curvePoints);
    void setTubeRadius(float tubeRadius);
    void setSpaceBetweenRails(float spaceBetweenRails);

private:
    float tubeRadius;
    float spaceBetweenRails;
    std::vector<Point> curvePoints;
    void drawRail(float radius, int numSides);
    void drawCylinderBetweenPoints(Point p1, Point p2, float radius, int numSides, float r, float g, float b);

    
};


#endif
