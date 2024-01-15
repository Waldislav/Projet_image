#ifndef __COURBE
#define __COURBE
#include <string>
#include <vector>
#include <math.h>
#include "point.h"

//#include <GL/glut.h>
using namespace std;

class Courbe
{

    private :
    double **Mb, **Mt;
    vector<Point> surfacePoints;
    Point pointControle[3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}



;
    public:
    
    Courbe();

    // Constructeur prenant les points de contrôle comme paramètres
    Courbe(const std::vector<std::vector<Point>> &points);

    void construire();

    // Fonction pour initializer une matrice
    double **create2DArray(unsigned height, unsigned width);

    // Fonctions qui retourne les points dans les axes X,Y et Z
    double **getXValues(Point controlPoints[3][3]);
    double **getYValues(Point controlPoints[3][3]);
    double **getZValues(Point controlPoints[3][3]);

    // Fonction qui effectue une multiplication entre matrices
    double **multiply(int rows_matrix1, int col_matrix1, double **matrix1, int col_matrix2, double **matrix2);

    // Fonction pour dessiner une surface de Bézier à partir de points de contrôle
    void bezier(Point controlPoints[3][3]);


};





#endif
