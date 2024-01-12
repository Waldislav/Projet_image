#include "cube.h"
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


Cube::Cube()
{
        cubeVertices[0].set(-0.25, -0.25, 0.25);
        cubeVertices[1].set(0.25, -0.25, 0.25);
        cubeVertices[2].set(0.25, 0.25, 0.25);
        cubeVertices[3].set(-0.25, 0.25, 0.25);
        cubeVertices[4].set(-0.25, -0.25, -0.25);
        cubeVertices[5].set(0.25, -0.25, -0.25);
        cubeVertices[6].set(0.25, 0.25, -0.25);
        cubeVertices[7].set(-0.25, 0.25, -0.25);
}
void Cube::construire()
{
    glBegin(GL_QUADS);

    // Face avant
    glVertex3f(cubeVertices[0].x, cubeVertices[0].y, cubeVertices[0].z);
    glVertex3f(cubeVertices[1].x, cubeVertices[1].y, cubeVertices[1].z);
    glVertex3f(cubeVertices[2].x, cubeVertices[2].y, cubeVertices[2].z);
    glVertex3f(cubeVertices[3].x, cubeVertices[3].y, cubeVertices[3].z);

    // Face arrière
    glVertex3f(cubeVertices[4].x, cubeVertices[4].y, cubeVertices[4].z);
    glVertex3f(cubeVertices[5].x, cubeVertices[5].y, cubeVertices[5].z);
    glVertex3f(cubeVertices[6].x, cubeVertices[6].y, cubeVertices[6].z);
    glVertex3f(cubeVertices[7].x, cubeVertices[7].y, cubeVertices[7].z);

    // Haut
    glVertex3f(cubeVertices[3].x, cubeVertices[3].y, cubeVertices[3].z);
    glVertex3f(cubeVertices[2].x, cubeVertices[2].y, cubeVertices[2].z);
    glVertex3f(cubeVertices[6].x, cubeVertices[6].y, cubeVertices[6].z);
    glVertex3f(cubeVertices[7].x, cubeVertices[7].y, cubeVertices[7].z);

    // Bas
    glVertex3f(cubeVertices[0].x, cubeVertices[0].y, cubeVertices[0].z);
    glVertex3f(cubeVertices[1].x, cubeVertices[1].y, cubeVertices[1].z);
    glVertex3f(cubeVertices[5].x, cubeVertices[5].y, cubeVertices[5].z);
    glVertex3f(cubeVertices[4].x, cubeVertices[4].y, cubeVertices[4].z);

    // Côté gauche
    glVertex3f(cubeVertices[0].x, cubeVertices[0].y, cubeVertices[0].z);
    glVertex3f(cubeVertices[3].x, cubeVertices[3].y, cubeVertices[3].z);
    glVertex3f(cubeVertices[7].x, cubeVertices[7].y, cubeVertices[7].z);
    glVertex3f(cubeVertices[4].x, cubeVertices[4].y, cubeVertices[4].z);

    // Côté droit
    glVertex3f(cubeVertices[1].x, cubeVertices[1].y, cubeVertices[1].z);
    glVertex3f(cubeVertices[2].x, cubeVertices[2].y, cubeVertices[2].z);
    glVertex3f(cubeVertices[6].x, cubeVertices[6].y, cubeVertices[6].z);
    glVertex3f(cubeVertices[5].x, cubeVertices[5].y, cubeVertices[5].z);

    glEnd();
}

