#include "rail.h"
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <string>
#include <cmath>

 #define PI 3.1415927

//using namespace arma;
using namespace std;

/**
 * Calcule la distance entre deux points
*/
float calculateDistance(Point p1, Point p2) 
{
    float distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
    return distance;
}

/**
 * Constructeur de la classe Rail avec paramètres
*/
Rail::Rail(float tubeRadius, float spaceBetweenRails, const std::vector<Point> curvePoints)
{
    this->tubeRadius = tubeRadius;
    this->spaceBetweenRails = spaceBetweenRails;
    this->curvePoints = curvePoints;
}

/**
 * Constructeur de la classe Rail sans paramètres
*/  
Rail::Rail() 
{
    tubeRadius = 0.09;
    spaceBetweenRails = 0.40;
}


void Rail::drawRail(float radius, int numSides) 
{

    // Couleur gris métallique
    float r = 120 / 255.0;
    float g = 120 / 255.0;
    float b = 120 / 255.0;
    
    float distance = 0;

    for (int i = 0; i < curvePoints.size() - 1; ++i) {
        const Point p1 = curvePoints[i];
        const Point p2 = curvePoints[i + 1];

        // Calcul de la direction entre les deux points

        std::vector<float> dir = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};

        // Calcul d'un vecteur perpendiculaire à la direction
        std::vector<float> perp = {-dir[2], dir[1], dir[0]};

        // Normalisation du vecteur perpendiculaire
        float length = std::sqrt(perp[0]*perp[0] + perp[1]*perp[1] + perp[2]*perp[2]);
        perp[0] /= length;
        perp[1] /= length;
        perp[2] /= length;

        // Rayon du cercle décidant de la largeur de l'espace entre les rails
        float circleRadius = tubeRadius + spaceBetweenRails;

        // Calcul des points pour les rails
        Point pRailGauche1 = Point(p1.x + circleRadius * perp[0], p1.y + circleRadius * perp[1], p1.z + circleRadius * perp[2]);
        Point pRailGauche2 = Point(p2.x + circleRadius * perp[0], p2.y + circleRadius * perp[1], p2.z + circleRadius * perp[2]);

        Point pRailDroit1 = Point(p1.x - circleRadius * perp[0], p1.y + circleRadius * perp[1], p1.z - circleRadius * perp[2]);
        Point pRailDroit2 = Point(p2.x - circleRadius * perp[0], p2.y + circleRadius * perp[1], p2.z - circleRadius * perp[2]);

        // Dessin des cylindres pour les rails
        drawCylinderBetweenPoints(pRailGauche1, pRailGauche2, radius, numSides, r, g, b);
        drawCylinderBetweenPoints(pRailDroit1, pRailDroit2, radius, numSides, r, g, b);

        //dessiner un cylindre entre les deux points toutes les 0.3 unités de distance
        if (distance >= 0.3) {

            // Couleur bois
            float r_2 = 169 / 255.0f;
            float g_2 = 99 / 255.0f;
            float b_2 = 49 / 255.0f;

            Point pRailGauche1 = Point(p1.x + circleRadius * perp[0], p1.y + circleRadius * perp[1], p1.z + circleRadius * perp[2]);
            Point pRailGauche2 = Point(p1.x - circleRadius * perp[0], p1.y + circleRadius * perp[1], p1.z - circleRadius * perp[2]);
            
            drawCylinderBetweenPoints(pRailGauche1, pRailGauche2, radius - 0.015, numSides, r_2, g_2, b_2);
            distance = 0;
        }
        distance += calculateDistance(p1, p2);

    }
}

/**
 * Dessine un cylindre entre deux points
*/
void Rail::drawCylinderBetweenPoints(Point p1, Point p2, float radius, int numSides, float r, float g, float b) 
{
    // Calcul de la longueur du cylindre
    float length = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));

 

    // Calcul des composantes du vecteur direction
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float dz = p2.z - p1.z;

    // Calcul des angles
    float angleYX = atan2(dy, dx);
    float angleZ = acos(dz / length);

    glColor3f(r, g, b);
    glPushMatrix();


    // Translation au point de départ
    glTranslatef(p1.x, p1.y, p1.z);

    // Rotation pour aligner le cylindre avec la direction entre les deux points
    glRotatef(angleYX * 180.0 / PI, 0.0, 0.0, 1.0);
    glRotatef(angleZ * 180.0 / PI, 0.0, 1.0, 0.0);

    // Dessin du cylindre sous forme de quadrilatères
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSides; ++i) {
        float angle = 2.0 * PI * i / numSides;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        
        glVertex3d(x, y, 0.0);  // Point sur le cercle inférieur
        glVertex3d(x, y, length);  // Point sur le cercle supérieur
        
    }
    glEnd();

    glPopMatrix();
}

/**
 * Lance la construction du rail
*/
void Rail::construire() 
{
    drawRail(tubeRadius, 8);
}

///////// SETTERS /////////

/**
 * Définit les points de la courbe à suivre
*/
void Rail::setPoints(const std::vector<Point> curvePoints) 
{
    this->curvePoints = curvePoints;
}

/**
 * Définit le rayon du cylindre
*/
void Rail::setTubeRadius(float tubeRadius) 
{
    this->tubeRadius = tubeRadius;
}

/**
 * Définit l'espace entre les rails
*/
void Rail::setSpaceBetweenRails(float spaceBetweenRails) 
{
    this->spaceBetweenRails = spaceBetweenRails;
}

//////////////////


