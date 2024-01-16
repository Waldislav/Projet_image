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

double calculateDistance(Point p1, Point p2) {
    double distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
    return distance;
}

Rail::Rail(double tubeRadius, double spaceBetweenRails, const std::vector<Point> curvePoints)
    : tubeRadius(tubeRadius), spaceBetweenRails(spaceBetweenRails), curvePoints(curvePoints) {}

Rail::Rail() {
    tubeRadius = 0.09;
    spaceBetweenRails = 0.40;
}


void Rail::drawRail(double radius, int numSides) {


    // Couleur gris métallique
    int red = 120;
    int green = 120;
    int blue = 120;

    // Conversion des couleurs dans l'intervalle [0, 1]
    float r = red / 255.0f;
    float g = green / 255.0f;
    float b = blue / 255.0f;
    
    double distance = 0;

    for (size_t i = 0; i < curvePoints.size() - 1; ++i) {
        const auto& p1 = curvePoints[i];
        const auto& p2 = curvePoints[i + 1];

        // Calcul de la direction entre les deux points

        std::vector<double> dir = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};

        // Calcul d'un vecteur perpendiculaire à la direction
        std::vector<double> perp = {-dir[2], dir[1], dir[0]};

        // Normalisation du vecteur perpendiculaire
        double length = std::sqrt(perp[0]*perp[0] + perp[1]*perp[1] + perp[2]*perp[2]);
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

        //dessiner un cylindre entre les deux points tous les 10 points
        if (distance >= 0.3) {
            // Couleur bois
            int red_2 = 139;    
            int green_2 = 69;  
            int blue_2 = 19;    

            int tanShade = 30;
            red_2 += tanShade;
            green_2 += tanShade;
            blue_2 += tanShade;

            // Conversion des valeurs dans l'intervalle [0, 1]
            float r_2 = red_2 / 255.0f;
            float g_2 = green_2 / 255.0f;
            float b_2 = blue_2 / 255.0f;

            Point pRailGauche1 = Point(p1.x + circleRadius * perp[0], p1.y + circleRadius * perp[1], p1.z + circleRadius * perp[2]);
            Point pRailGauche2 = Point(p1.x - circleRadius * perp[0], p1.y + circleRadius * perp[1], p1.z - circleRadius * perp[2]);
            
            drawCylinderBetweenPoints(pRailGauche1, pRailGauche2, radius - 0.015, numSides, r_2, g_2, b_2);
            distance = 0;
        }
        distance += calculateDistance(p1, p2);

    }
}

void Rail::drawCylinderBetweenPoints(Point p1, Point p2, double radius, int numSides, float r, float g, float b) {
    // Calculer la longueur du cylindre
    double length = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));

 

    // Calculer les composantes du vecteur direction
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;

    // Calculer l'angle d'inclinaison par rapport à l'axe y
    double theta = atan2(dy, dx);

    // Calculer l'angle d'élévation par rapport à l'axe z
    double phi = acos(dz / length);

    glColor3f(r, g, b);
    glPushMatrix();


    // Translation au point de départ
    glTranslatef(p1.x, p1.y, p1.z);

    // Rotation pour aligner le cylindre avec la direction entre les deux points
    glRotatef(theta * 180.0 / M_PI, 0.0, 0.0, 1.0);
    glRotatef(phi * 180.0 / M_PI, 0.0, 1.0, 0.0);

    // Dessiner le cylindre
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSides; ++i) {
        double angle = 2.0 * M_PI * i / numSides;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        
        glVertex3d(x, y, 0.0);  // Point sur le cercle inférieur
        glVertex3d(x, y, length);  // Point sur le cercle supérieur
        
    }
    glEnd();

    glPopMatrix();
}

void Rail::construire() {
    drawRail(tubeRadius, 8);
}

void Rail::setPoints(const std::vector<Point> curvePoints) {
    this->curvePoints = curvePoints;
}

void Rail::setTubeRadius(double tubeRadius) {
    this->tubeRadius = tubeRadius;
}

void Rail::setSpaceBetweenRails(double spaceBetweenRails) {
    this->spaceBetweenRails = spaceBetweenRails;
}
