
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
#include <time.h>
#include <string>
#include <cmath>
#include "cube.h"
#include "chariot.h"
#include "courbe.h"
#include "rail.h"
#include "point.h"
#include "courbeBezier.h"

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
Point regardeCam;
bool etatPov=false;

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
Courbe courbe3(pointsDeControle3);sudo gdebi GitHubDesktop-linux-3.1.1-linux1.deb
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
float t = 0.0f;
float pas = 0.01f; // delta t
float gravity = -9.8f; // gravité
//vitesse initiale
float velocityX = 0.0f;
float velocityY = 0.0f;
float velocityZ = 0.0f;
//accélération initiale
float accelerationX = 0.0f;
float accelerationY = 0.0f;
float accelerationZ = 0.0f;

int indexPoint = 0;
//----------------------------------------------------------------------------------
void initMesh()
//----------------------------------------------------------------------------------
{
    // Initialisation de nos objets
    courbe1.construire();
    rail = new Rail();
    ptsCourbe = courbe1.generateCurvePoints();
    rail->setPoints(ptsCourbe);
    ptCentreChariot = {ptsCourbe[0].x,ptsCourbe[0].y,ptsCourbe[0].z};
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
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(45.0f,(GLfloat)200/(GLfloat)200,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();	
    //	glScalef(.7,.7,.7);
    //gluLookAt(0.,0.,4., 0.,0.,0., 0.,1.,0.);
    //  glTranslatef(0.0,0.0,-5.0);
}

void normalizeVector(Point vec) {
    float length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

    if (length != 0.0) {
        vec.x /= length;
        vec.y /= length;
        vec.z /= length;
    }
}

void rotation() {
    // Récupération de deux points sur la courbe
    Point pt1 = ptsCourbe[indexPoint];
    // Si on arrive à la fin du circuit, on revient au début
    if(indexPoint == ptsCourbe.size()-1) {
        indexPoint = -1;
    }
    Point pt2 = ptsCourbe[indexPoint+1];
    
    // Calcul du vecteur de direction du chariot avec deux points sur la courbe
    Point directionVector = {pt2.x - pt1.x, pt2.y - pt1.y, pt2.z - pt1.z};
    normalizeVector(directionVector);
    
    //Calcul d'un point lointain suivant la direction du trajet pour que la caméra la regarde
    regardeCam = {pt1.x+(directionVector.x*54), pt1.y+(directionVector.y*54) + 1.5f, pt1.z+(directionVector.z*54)};

    // Calcul de l'angle
    float angle = acos(directionVector.z / sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y + directionVector.z * directionVector.z)) * 180 / M_PI;
    // Parralèle au vecteur de direction
    Point axis = {-directionVector.y, directionVector.x, 0};
    angleRotationChariot = angle;
    chariotRotationX = axis.x;
    chariotRotationY = axis.y;
    chariotRotationZ = axis.z;
}

void camera() {
    
}

//----------------------------------------------------------------------------------
void animation(int value) {
//----------------------------------------------------------------------------------
    int temps = 10;  // Le temps que va mettre l'animation à afficher la prochaine frame (possible à recalculer)

    
    //**********************************************************************
    // Traitement pour l'animation
    //**********************************************************************

    // Déplacement du chariot sur la courbe en prenant en compte la gravité
    if(value >= ptsCourbe.size() - 3) {
        return;
    }

    // Calcul du vecteur tangente à la courbe
    float tx = 3*pow(1-t, 2)*(ptsCourbe[value+1].x-ptsCourbe[value].x) + 6*t*(1-t)*(ptsCourbe[value+2].x-ptsCourbe[value+1].x) + 3*pow(t, 2)*(ptsCourbe[value+3].x-ptsCourbe[value+2].x);
    float ty = 3*pow(1-t, 2)*(ptsCourbe[value+1].y-ptsCourbe[value].y) + 6*t*(1-t)*(ptsCourbe[value+2].y-ptsCourbe[value+1].y) + 3*pow(t, 2)*(ptsCourbe[value+3].y-ptsCourbe[value+2].y);
    float tz = 3*pow(1-t, 2)*(ptsCourbe[value+1].z-ptsCourbe[value].z) + 6*t*(1-t)*(ptsCourbe[value+2].z-ptsCourbe[value+1].z) + 3*pow(t, 2)*(ptsCourbe[value+3].z-ptsCourbe[value+2].z);
    //printf("tx = %f, ty = %f, tz = %f\n", tx, ty, tz);

    // Normalisez le vecteur tangente
    float norme = sqrt(pow(tx, 2) + pow(ty, 2) + pow(tz, 2));
    tx /= norme;
    ty /= norme;
    tz /= norme;

    // Calculez la vitesse du chariot en fonction de la tangente
    float velocityXprime = tx * velocityX;
    float velocityYprime = ty * velocityY;
    float velocityZprime = tz * velocityZ;

    // Calculez l'accélération du chariot en fonction de la tangente
    float accelerationXtan = (velocityXprime - velocityX) / 0.01;
    float accelerationYtan = (velocityYprime - velocityY) / 0.01;
    float accelerationZtan = (velocityZprime - velocityZ) / 0.01;

    // Calculez l'accélération du chariot en fonction de la gravité
    float accelerationXgrav = 0.0f;
    float accelerationYgrav = gravity;
    float accelerationZgrav = 0.0f;

    // Produit scalaire entre la tangente et la gravité
    float produitScalaire = tx * accelerationXgrav + ty * accelerationYgrav + tz * accelerationZgrav;

    // Calculez l'accélération du chariot en fonction de la réaction
    float accelerationXreact = -produitScalaire * tx;
    float accelerationYreact = -produitScalaire * ty;
    float accelerationZreact = -produitScalaire * tz;

    // Calculez l'accélération totale du chariot
    accelerationX = accelerationXtan + accelerationXgrav + accelerationXreact;
    accelerationY = accelerationYtan + accelerationYgrav + accelerationYreact;
    accelerationZ = accelerationZtan + accelerationZgrav + accelerationZreact;
    printf("accelerationX = %f, accelerationY = %f, accelerationZ = %f\n", accelerationX, accelerationY, accelerationZ);

    // Modifier la vitesse du chariot en fonction de l'accélération
    velocityX += accelerationX * pas;
    velocityY += accelerationY * pas;
    velocityZ += accelerationZ * pas;
    printf("velocityX = %f, velocityY = %f, velocityZ = %f\n", velocityX, velocityY, velocityZ);

    // Modifier la position du chariot en fonction de la vitesse
    ptCentreChariot.x = ptsCourbe[value].x + velocityX * pas;
    ptCentreChariot.y = ptsCourbe[value].y + 0.75 + velocityY * pas;
    ptCentreChariot.z = ptsCourbe[value].z + velocityZ * pas;
    


    indexPoint++;
    //ptCentreChariot = {ptsCourbe[indexPoint].x,ptsCourbe[indexPoint].y,ptsCourbe[indexPoint].z};
    rotation();
    camera();


    cout << "Fonction animation lancée" << endl;
    
    //**********************************************************************
    glutTimerFunc(16, animation, value + 1 );
    glutPostRedisplay();
    // QuitteAnim permet de vérifier si on relance la fonction animation ou pas
    if(!quitteAnim) glutTimerFunc(16, animation, value + 1);
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int main(int argc,char **argv)
{

      /* initialisation de glut et creation
         de la fenetre */
    srand((unsigned)time(NULL));
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
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

    glutTimerFunc(16, animation, 0); // commence l'animation

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
    if(!etatPov){
        gluLookAt(0.,0.,4., 0.,0.,0., 0.,1.,0.);
        glTranslatef(0,0,cameraDistance);
        glRotatef(cameraAngleX,1.,0.,0.);
        glRotatef(cameraAngleY,0.,1.,0.);
    } else {
        gluLookAt(ptCentreChariot.x,ptCentreChariot.y+1, ptCentreChariot.z,  // Position de la caméra
                  regardeCam.x,regardeCam.y, regardeCam.z,  // Point de vue de la caméra
                  0.0f, 1.0f, 0.0f);
    }
    //--------------------------------
    affiche_repere();
    //--------------------------------
    // Construction de nos objets
    //--------------------------------
    courbe1.construire();
        // Place un cube de test
        glPushMatrix();
            glTranslatef(ptCentreChariot.x, ptCentreChariot.y, ptCentreChariot.z);
            glRotatef(angleRotationChariot,chariotRotationX,chariotRotationY,chariotRotationZ);
            //cube.construire();
            //courbe1.construire();
            //courbe2.construire();
            //courbe3.construire();
            //courbe4.construire();
            //courbe5.construire();
        glPopMatrix();
        
		
		// Construction des rails
        glPushMatrix();
            rail->construire();
        glPopMatrix();

        // Construction chariot
        glPushMatrix();
            glTranslatef(ptCentreChariot.x, ptCentreChariot.y, ptCentreChariot.z);
            glRotatef(angleRotationChariot,chariotRotationX,chariotRotationY,chariotRotationZ);
            chariot.construire();
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
    case 'v' :
            etatPov = false;
            glutPostRedisplay();
            break;
    case 'c' :
        etatPov = true;
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

    
    
