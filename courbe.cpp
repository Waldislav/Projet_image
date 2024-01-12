#include "courbe.h"
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


Courbe::Courbe()
{
    // Initialisation des points de contrôle
}
void Courbe::construire(Point ptsCourbe[])
{
    // Construction des courbes et renvoie les points de la courbe dans ptsCourbe
}

