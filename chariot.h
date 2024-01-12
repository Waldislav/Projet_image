#ifndef __CHARIOT
#define __CHARIOT
#include <string>
#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Chariot
{

    private :
    Point pointsChariots[];
    public:
    Chariot();
    void construire();
};



#endif
