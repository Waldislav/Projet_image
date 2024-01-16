#ifndef __COURBEBEZIER
#define __COURBEBEZIER
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "point.h"
#include <random>
//#include <GL/glut.h>
using namespace std;

class CourbeBezier
{
private:
    vector<Point> controlPoints;

public:
    void addControlPoint(const Point& point);
    void construire();

    vector<Point> generateRandomControlPoints(int numPoints);
    vector<Point> generateCurvePoints();
    
};







#endif
