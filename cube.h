#ifndef __CUBE
#define __CUBE
#include <string>
#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Cube
{

    private :
    Point cubeVertices[8];
    public:
    Cube();
    void construire();
};



#endif
