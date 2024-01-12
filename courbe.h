#ifndef __COURBE
#define __COURBE
#include <string>
#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Courbe
{

    private :
    Point pointControle[];
    public:
    Courbe();
    void construire(Point ptsCourbe[]);
};



#endif
