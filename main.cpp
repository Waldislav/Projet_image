
#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <vector>
#include <sstream>
#include <string>
#include "cube.h"
#include "chariot.h"
#include "courbe.h"
#include "rail.h"
#include "point.h"

using namespace std ;
void affichage(void);

void clavier(unsigned char touche,int x,int y);
void affiche_repere(void);

void mouse(int, int, int, int);
void mouseMotion(int, int);


// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance=0.;

bool quitteAnim=true;

/*   Déjà inclut dans cube.h

struct Point {
    float x,y,z;
    Point(float a=0, float b=0, float c=0) {set(a,b,c);}
    void set(float a, float b, float c) {x=a;y=b;z=c;}
};

*/

// Un objet pour effectuer des tests
Cube cube;

// Nécessaire à la construction du roller coaster
Chariot chariot;
/*
std::vector<std::vector<Point>> pointsDeControle1 = {
        {{-5, -5, -5}, {-5, 10, 0}, {-5, -5, 5}},
        {{0, -5, -5}, {0, 10, 0}, {0, -5, 5}},
        {{5, -5, -5}, {5, 10, 0}, {5, -5, 5}}
    };
std::vector<std::vector<Point>> pointsDeControle2 = {
        {{-5, -5, 5}, {-5, -35, 12}, {-5, -20, 17}},
        {{0, -5, 5}, {0, -35, 12}, {0, -20, 17}},
        {{5, -5, 5}, {5, -35, 12}, {5, -20, 17}}
    };
std::vector<std::vector<Point>> pointsDeControle3 = {
        {{5, -5, -5}, {5, -20, -10}, {5, -5, -15}},
        {{0, -5, -5}, {0, -20, -10}, {0, -5, -15}},
        {{-5, -5, -5}, {-5, -20, -10}, {-5, -5, -15}}
    };
std::vector<std::vector<Point>> pointsDeControle4 = {
        {{-5, -20, 17}, {-5, 15, 25}, {-5, 3, 32}},
        {{0, -20, 17}, {0, 15, 25}, {0, 3, 32}},
        {{5, -20, 17}, {5, 15, 25}, {5, 3, 32}}
    };
std::vector<std::vector<Point>> pointsDeControle5 = {
        {{5, -5, -15}, {5, 15, -20}, {5, 15, -30}},
        {{0, -5, -15}, {0, 15, -20}, {0, 15, -30}},
        {{-5, -5, -15}, {-5, 15, -20}, {-5, 15, -30}}
    };
Courbe courbe1(pointsDeControle1);
Courbe courbe2(pointsDeControle2);
Courbe courbe3(pointsDeControle3);
Courbe courbe4(pointsDeControle4);
Courbe courbe5(pointsDeControle5);
*/
CourbeBezier courbe1;
Rail* rail;
std::vector<Point> ptsCourbe;

Point ptCentreChariot(0.,0.,0.);
float angleRotationChariot = 0;
float chariotRotationX = 0;
float chariotRotationY = 0;
float chariotRotationZ = 0;
double G = 9.81;
vector<double> vitesse_init = {1.0, 1.0, 1.0};

//----------------------------------------------------------------------------------
void initMesh()
//----------------------------------------------------------------------------------
{
    // Initialisation de nos objets
    courbe1.construire();
    courbe2.construire();
    courbe3.construire();
    courbe4.construire();
    courbe5.construire();
    rail = new Rail();
    ptsCourbe = courbe1.generateCurvePoints();
    rail->setPoints(ptsCourbe);
}



//----------------------------------------------------------------------------------
void initOpenGl()
//----------------------------------------------------------------------------------
{
    initMesh();

    //lumiere
	glClearColor( .5, .5, 0.5, 0.0 );
 
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat l_pos[] = { 3.,3.5,3.0,1.0 };
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos);

     glLightfv(GL_LIGHT0,GL_DIFFUSE,l_pos);
     glLightfv(GL_LIGHT0,GL_SPECULAR,l_pos);
 
     // glDepthFunc(GL_LESS);
     // glEnable(GL_DEPTH_TEST);
     glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(45.0f,(GLfloat)200/(GLfloat)200,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();	
    //	glScalef(.7,.7,.7);
    gluLookAt(0.,0.,4., 0.,0.,0., 0.,1.,0.);
    //  glTranslatef(0.0,0.0,-5.0);
}


// Fonction pour l'animation (le paramètre est obligatoire pour lancer glutTimerFunc)
//----------------------------------------------------------------------------------
void animation(int numTimer) {
//----------------------------------------------------------------------------------
    int temps = 1000;  // Le temps que va mettre l'animation à afficher la prochaine frame (possible à recalculer)

    
    //**********************************************************************
    // Traitement pour l'animation
    //**********************************************************************

    




    cout << "Fonction animation lancée" << endl;
    
    //**********************************************************************
    
    glutPostRedisplay();
    // QuitteAnim permet de vérifier si on relance la fonction animation ou pas
    if(!quitteAnim) glutTimerFunc(temps, animation, 1 );
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int main(int argc,char **argv)
{

      /* initialisation de glut et creation
         de la fenetre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(600,600);
    glutCreateWindow("Montagne russe");

    /* Initialisation d'OpenGL */
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(1.0);

    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    
    initOpenGl() ;

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------------------
void affiche_repere(void)
{
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex2f(0.,0.);
  glVertex2f(1.,0.);
  glEnd(); 

	 glBegin(GL_LINES);
  glColor3f(0.0,1.0,0.0);
  glVertex2f(0.,0.);
  glVertex2f(0.,1.);
  glEnd(); 
   glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.,0.,0.);
  glVertex3f(0.,0.,1.);
  glEnd(); 
}

//-----------------------------------------------------


//------------------------------------------------------
void affichage(void)
{
	glMatrixMode(GL_MODELVIEW);
    /* effacement de l'image avec la couleur de fond */
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0,0,cameraDistance);
    glRotatef(cameraAngleX,1.,0.,0.);
    glRotatef(cameraAngleY,0.,1.,0.);
    //--------------------------------
    affiche_repere();
    //--------------------------------
    // Construction de nos objets
    //--------------------------------

        // Place un cube de test
        glPushMatrix();
            glTranslatef(ptCentreChariot.x, ptCentreChariot.y, ptCentreChariot.z);
            cube.construire();
            courbe1.construire();
            //courbe2.construire();
            //courbe3.construire();
            //courbe4.construire();
            //courbe5.construire();
        glPopMatrix();
        
        // Construction chariot
        glPushMatrix();
            glTranslatef(ptCentreChariot.x, ptCentreChariot.y, ptCentreChariot.z);
            glRotatef(angleRotationChariot,chariotRotationX,chariotRotationY,chariotRotationZ);
            chariot.construire();
        glPopMatrix();
        
        // Construction des rails
        glPushMatrix();
            rail->construire();
        glPopMatrix();

    //--------------------------------

    glPopMatrix();
    /* on force l'affichage du resultat */
    glFlush();
}

//------------------------------------------------------


//------------------------------------------------------
void clavier(unsigned char touche,int x,int y)
{

  switch (touche)
    {
    case '+':
      glutPostRedisplay();
      break;
    case '-':
      glutPostRedisplay();
      break;
    case 'f': //* affichage en mode fil de fer 
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
      case 'p': //* affichage du carre plein 
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 's' : //* Affichage en mode sommets seuls
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'a' : //* Lance l'animation
        quitteAnim = !quitteAnim;
        if(!quitteAnim) glutTimerFunc(1, animation, 1);
        glutPostRedisplay();
        break;
    case 'q' : //*la touche 'q' permet de quitter le programme
      exit(0);
    }
    
}
void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}


void mouseMotion(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}

    
    
