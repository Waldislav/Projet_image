#include "courbe.h"
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <string>


using namespace std;


//using namespace arma;

Courbe::Courbe()
{
    Mb = create2DArray(3, 3);
    Mb[0][0] = 1;
    Mb[1][0] = -2;
    Mb[2][0] = 1;
    Mb[0][1] = -2;
    Mb[1][1] = 2;
    Mb[2][1] = 0;
    Mb[0][2] = 1;
    Mb[1][2] = 0;
    Mb[2][2] = 0;

    Mt = create2DArray(3, 3);
    Mt[0][0] = 1;
    Mt[1][0] = -2;
    Mt[2][0] = 1;
    Mt[0][1] = -2;
    Mt[1][1] = 2;
    Mt[2][1] = 0;
    Mt[0][2] = 1;
    Mt[1][2] = 0;
    Mt[2][2] = 0;
}

// Constructeur prenant les points de contrôle comme paramètres
    Courbe::Courbe(const std::vector<std::vector<Point>> &points) {
        Mb = create2DArray(3, 3);
    Mb[0][0] = 1;
    Mb[1][0] = -2;
    Mb[2][0] = 1;
    Mb[0][1] = -2;
    Mb[1][1] = 2;
    Mb[2][1] = 0;
    Mb[0][2] = 1;
    Mb[1][2] = 0;
    Mb[2][2] = 0;

    Mt = create2DArray(3, 3);
    Mt[0][0] = 1;
    Mt[1][0] = -2;
    Mt[2][0] = 1;
    Mt[0][1] = -2;
    Mt[1][1] = 2;
    Mt[2][1] = 0;
    Mt[0][2] = 1;
    Mt[1][2] = 0;
    Mt[2][2] = 0;
    
        
        if (points.size() == 3 && points[0].size() == 3 && points[1].size() == 3 && points[2].size() == 3) {
            // Initialisation des points de contrôle
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    pointControle[i][j] = points[i][j];
                }
            }
        } else {
            // Gestion d'erreur si la taille des points de contrôle est incorrecte
            printf("Le nombre de lignes ou de colonnes des points de contrôle est incorrect.");
        }}

// Fonction pour initializer une matrice
double** Courbe::create2DArray(unsigned height, unsigned width)
{
    double **array2D = 0;
    array2D = new double *[height];

    for (int h = 0; h < height; h++)
    {
        array2D[h] = new double[width];

        for (int w = 0; w < width; w++)
        {
            array2D[h][w] = 0;
        }
    }
    return array2D;
}
// Fonction qui retourne les points dans l'axe X
double** Courbe::getXValues(Point controlPoints[3][3])
{
    double **matrix = create2DArray(3, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = controlPoints[i][j].x;
        }
    }

    return matrix;
}

// Fonction qui retourne les points dans l'axe Y
double** Courbe::getYValues(Point controlPoints[3][3])
{
    double **matrix = create2DArray(3, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = controlPoints[i][j].y;
        }
    }

    return matrix;
}

// Fonction qui retourne les points dans l'axe Z
double** Courbe::getZValues(Point controlPoints[3][3])
{
    double **matrix = create2DArray(3, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = controlPoints[i][j].z;
        }
    }

    return matrix;
}

// Fonction qui effectue une multiplication entre matrices
double** Courbe::multiply(int rows_matrix1, int col_matrix1, double **matrix1, int col_matrix2, double **matrix2)
{
    double **product = create2DArray(rows_matrix1, col_matrix2);

    for (int row = 0; row < rows_matrix1; row++)
    {
        for (int col = 0; col < col_matrix2; col++)
        {
            for (int inner = 0; inner < col_matrix1; inner++)
            {
                product[row][col] += matrix1[row][inner] * matrix2[inner][col];
            }
        }
    }

    return product;
}

// Fonction pour dessiner une surface de Bézier à partir de points de contrôle
// Utilise le produit tensoriel
void Courbe::bezier(Point controlPoints[3][3])
{
    double u = 0, v = 0;
    double **resultX;
    double **resultY;
    double **resultZ;

    double **matrixX = getXValues(controlPoints);
    double **matrixY = getYValues(controlPoints);
    double **matrixZ = getZValues(controlPoints);

    double **Mu = create2DArray(1, 3);
    double **Mv = create2DArray(3, 1);

    double step = 0.1;

    for (u = 0; u <= 1; u += step)
    {
        for (v = 0; v <= 1; v += step)
        {

            Mu[0][0] = pow(u, 2);
            Mu[0][1] = u;
            Mu[0][2] = 1;

            Mv[0][0] = pow(v, 2);
            Mv[1][0] = v;
            Mv[2][0] = 1;

            resultX = multiply(1, 3, multiply(1, 3, multiply(1, 3, Mu, 3, Mb), 3, matrixX), 1, multiply(3, 3, Mt, 1, Mv));
            resultY = multiply(1, 3, multiply(1, 3, multiply(1, 3, Mu, 3, Mb), 3, matrixY), 1, multiply(3, 3, Mt, 1, Mv));
            resultZ = multiply(1, 3, multiply(1, 3, multiply(1, 3, Mu, 3, Mb), 3, matrixZ), 1, multiply(3, 3, Mt, 1, Mv));

            Point p(resultX[0][0], resultY[0][0], resultZ[0][0]);
            surfacePoints.push_back(p);
        }
    }
}



void Courbe::construire()
{
    surfacePoints.clear();
    bezier(pointControle);


    // Construction des courbes et renvoie les points de la courbe dans ptsCourbe
    glPointSize(3);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                glVertex3f(pointControle[i][j].x, pointControle[i][j].y, pointControle[i][j].z);
            }
        }
    }
    glEnd();

    for (int i = 0; i < 3; i++)
    {
        glBegin(GL_LINE_STRIP);
        {
            for (int j = 0; j < 3; j++)
            {
                glVertex3f(pointControle[i][j].x, pointControle[i][j].y, pointControle[i][j].z);
            }
        }
        glEnd();
    }

    for (int i = 0; i < 3; i++)
    {
        glBegin(GL_LINE_STRIP);
        {
            for (int j = 0; j < 3; j++)
            {
                glVertex3f(pointControle[j][i].x, pointControle[j][i].y, pointControle[j][i].z);
            }
        }
        glEnd();
    }

    int cont = 1;
    int numPoints = sqrt(surfacePoints.size());

    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < surfacePoints.size(); i++)
    {
        if (cont == numPoints)
        {
            cont = 1;
        }
        else
        {
            if (i + numPoints < surfacePoints.size())
            {
                glBegin(GL_TRIANGLES);
                glVertex3f(surfacePoints[i].x, surfacePoints[i].y, surfacePoints[i].z);
                glVertex3f(surfacePoints[i + 1].x, surfacePoints[i + 1].y, surfacePoints[i + 1].z);
                glVertex3f(surfacePoints[i + numPoints].x, surfacePoints[i + numPoints].y, surfacePoints[i + numPoints].z);

                glVertex3f(surfacePoints[i + numPoints].x, surfacePoints[i + numPoints].y, surfacePoints[i + numPoints].z);
                glVertex3f(surfacePoints[i + 1].x, surfacePoints[i + 1].y, surfacePoints[i + 1].z);
                glVertex3f(surfacePoints[i + (numPoints + 1)].x, surfacePoints[i + (numPoints + 1)].y, surfacePoints[i + (numPoints + 1)].z);
                glEnd();
                cont++;
            }
        }
    }
}

