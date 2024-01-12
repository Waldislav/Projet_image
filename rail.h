#ifndef __RAIL
#define __RAIL
#include <string>
#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Rail
{

    private :
    Point ptsCourbe[1];
    Point ptsRails[1];
    public:
    Rail(Point ptsCourbe[]);
    void construire();
};



#endif
