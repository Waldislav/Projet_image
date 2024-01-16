#include "courbeBezier.h"
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <string>

//using namespace arma;
using namespace std;


std::vector<Point>  CourbeBezier::generateCurvePoints()
{
    this->controlPoints = generateRandomControlPoints(10);
    vector<Point> curvePoints;
    
   
    // Générer les points de la courbe tous les 0.01 
    for (size_t i = 0; i < controlPoints.size() - 3; ++i) {
        const auto& p1 = controlPoints[i];
        const auto& p2 = controlPoints[i + 1];
        const auto& p3 = controlPoints[i + 2];
        const auto& p4 = controlPoints[i + 3];

        for (float t = 0.0; t < 1.0; t += 0.01) {
            float x = 0.5 * ((2 * p2.x) + (-p1.x + p3.x) * t + (2 * p1.x - 5 * p2.x + 4 * p3.x - p4.x) * pow(t, 2) + (-p1.x + 3 * p2.x - 3 * p3.x + p4.x) * pow(t, 3));
            float y = 0.5 * ((2 * p2.y) + (-p1.y + p3.y) * t + (2 * p1.y - 5 * p2.y + 4 * p3.y - p4.y) * pow(t, 2) + (-p1.y + 3 * p2.y - 3 * p3.y + p4.y) * pow(t, 3));
            float z = 0.5 * ((2 * p2.z) + (-p1.z + p3.z) * t + (2 * p1.z - 5 * p2.z + 4 * p3.z - p4.z) * pow(t, 2) + (-p1.z + 3 * p2.z - 3 * p3.z + p4.z) * pow(t, 3));

            curvePoints.push_back({x, y, z});
        }
    }
    

    return curvePoints;
}

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

vector<Point> CourbeBezier::generateRandomControlPoints(int numPoints)
{
    vector<Point> controlPoints;
    float prevZ = 0.0;
    float prevY = 0.0;
    float prevX = 0.0;

    float firstY = 0.0;

    if (controlPoints.size() == 0) {
        float z = -3 * numPoints;
        float y = 0;
        float x = 0;

        prevX = x;
        prevY = y;
        prevZ = z;
        firstY = 0.0;

        controlPoints.push_back({x, y, z});
    }
    for (int i = 1; i < numPoints-1; ++i) {
    float x = randomFloat(prevX-2, prevX+2);
    float z = randomFloat(prevZ+4, prevZ+8);
    float y = 0;
    if (prevY <= 0){
           y = randomFloat(prevY+2, prevY+4);
    }
    else{
         y = randomFloat(prevY-2, prevY-4);
    }
    prevZ = z;
    prevY = y;
    prevX = x;

   
    controlPoints.push_back({x, y, z});
    }
    return controlPoints;
}

void CourbeBezier::addControlPoint(const Point& point)
{
    controlPoints.push_back(point);
}

void CourbeBezier::construire() {};