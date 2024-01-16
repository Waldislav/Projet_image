#include "chariot.h"
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <string>
#include <cmath>
#include <jpeglib.h>
#include <jerror.h>

GLuint texObject;  // Identifiant de la texture

static GLubyte checkImage0[256][256][3];
static unsigned char image[894*894*3];

void loadJpegImage(char *fichier,int larg, int haut, unsigned char* img);


Chariot::Chariot()
{
    // Initialisation des points du chariot
}




void Chariot::drawWheel(float x, float y, float z, float radius, float height, int slices) {
    glColor3f(0.5, 0.7, 0.2);

    // Dessiner le côté du cylindre
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; ++i) {
        float theta = (2.0 * M_PI * i) / slices;
        float y_cylinder = y + radius * cos(theta);
        float z_cylinder = z + radius * sin(theta);

        glVertex3f(x, y_cylinder, z_cylinder);
        glVertex3f(x + height, y_cylinder, z_cylinder);
    }
    glEnd();

    // Dessiner les extrémités du cylindre
    glBegin(GL_POLYGON);
    for (int i = 0; i <= slices; ++i) {
        float theta = (2.0 * M_PI * i) / slices;
        float y_cylinder = y + radius * cos(theta);
        float z_cylinder = z + radius * sin(theta);

        glVertex3f(x, y_cylinder, z_cylinder);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i <= slices; ++i) {
        float theta = (2.0 * M_PI * i) / slices;
        float y_cylinder = y + radius * cos(theta);
        float z_cylinder = z + radius * sin(theta);

        glVertex3f(x + height, y_cylinder, z_cylinder);
    }
    glEnd();
}

void Chariot::construire()
{
    GLfloat basePoint[] = {0.0, 0.0, 0.0};

    GLfloat vertices[][3] = {
        {-0.5, -0.5, -0.5},  // 0
        {0.5, -0.5, -0.5},   // 1
        {0.5, 0.5, -0.5},    // 2
        {-0.5, 0.5, -0.5},   // 3
        {-0.5, -0.5, 1},   // 4
        {0.5, -0.5, 1},    // 5
        {0.5, 0.5, 1},     // 6
        {-0.5, 0.5, 1},     // 7

        //Creuser le cube pour avoir un chariot

        {-0.25, -0.5, -0.25},    // 8
        {0.25, -0.5, -0.25},     // 9
        {0.25, 0.5, -0.25},      // 10
        {-0.25, 0.5, -0.25},     // 11
        {-0.25, -0.5, 0.9},     // 12
        {0.25, -0.5, 0.9},      // 13
        {0.25, 0.5, 0.9},       // 14
        {-0.25, 0.5, 0.9}       // 15
    };

    // Définir les faces du cube
    GLint faces[][4] = {
        {0, 1, 2, 3},  // Face arrière
        {4, 5, 6, 7},  // Face avant
        {0, 4, 5, 1},  // Face inférieure
        //{2, 6, 7, 3},  // Face supérieure
        {0, 3, 7, 4},  // Face gauche
        {1, 5, 6, 2},   // Face droite


        //Creuser le cube pour avoir un chariot

        {8, 9, 10, 11},  // Face arrière
        {12, 13, 14, 15},  // Face avant
        {8, 12, 13, 9},  // Face inférieure

        //relier le haut du chariot au creux
        {3, 11, 10, 2},
        {2, 10, 14, 6},
        {6, 14, 15, 7},
        {7, 15, 11, 3},

        {0, 4, 12, 8},  // Face gauche
        {1, 5, 13, 9}   // Face droite

    };

    // Dessiner les roues
    float compensation = -0.05;
    for (int i = 0; i < 4; i++)
    {
        drawWheel(vertices[faces[2][i]][0]+compensation, vertices[faces[2][i]][1], vertices[faces[2][i]][2], 0.15, 0.1, 30);
    }


    // Dessiner le cube face par face
    glBegin(GL_QUADS);
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 4; ++j) {
                glColor3f(0.2, 0.3, 0.7);
                glVertex3fv(vertices[faces[i][j]]);  
        }
    }
    glEnd();
}

