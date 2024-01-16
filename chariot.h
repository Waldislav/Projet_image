#ifndef __CHARIOT
#define __CHARIOT
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Chariot
{

    private :
    //Point pointsChariots[];
    public:
    Chariot();
    void drawWheel(float x, float y, float z, float radius, float height, int slices);
    void loadTexture(const char* filename);
    void construire();
};



#endif
