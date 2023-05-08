/*Esercizio:
 Scrivere un programma con OpenGL che disegni una circonferenza mediante curve NURBS.
 Campioni la curva per un prefissato numero di valori del parametro e gestisca gli eventuali errori.
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265


// Definizione dei punti di controllo
float cp[7][3] = { {-2.0, 0.0, 0.0},
                   {-2.0, 2.0, 0.0},
                   { 2.0, 2.0, 0.0},
                   { 2.0, 0.0, 0.0},
                   { 2.0,-2.0, 0.0},
                   {-2.0,-2.0, 0.0},
                   {-2.0, 0.0, 0.0} };

// Array per le coordinate omogenee
float cpw[7][4];

// Array dei pesi dei punti di controllo
float w[7] = { 1, 0.5, 0.5, 1.0, 0.5, 0.5, 1.0 };

// Vettore dei nodi della curva
float knots[10] = { 0.0, 0.0, 0, 0.25, 0.5, 0.5, 0.75, 1.0, 1.0, 1.0 };

/*
 *  i nodi sono usati per controllare la forma della curva,
 *  stabilendo la posizione dei punti di controllo lungo la curva stessa,
 *  mentre i pesi determinano l'importanza relativa di ogni punto di controllo nell'influenzare la forma finale della curva.
 */

// Funzione per la gestione degli errori NURBS
void nurbsError(GLenum errorCode)
{
    const GLubyte *estring;
    estring = gluErrorString(errorCode);
    fprintf(stderr,"Errore NURBS: %s\n",estring);
    exit(0);
}

// Funzione per calcolare le coordinate omogenee dei punti di controllo
void  coordinateOmogenee(float a [][3], float b[][4],int righe, float * pesi )
{
    int i,j;

    for (i=0;i<righe;i++)
        b[i][3]=pesi[i];

    for (i=0;i<righe;i++)
    {
        for(j=0;j<3;j++)
        {
            b[i][j]=a[i][j]*pesi[i];

        }
    }
}



void display() //NURBS
{

    glClearColor(0.3,0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT );
    glLoadIdentity();
    glScalef(0.2,0.2,0);

    int i;
    // Disegna i punti di controllo
    for(i=0;i<7;i++)
    {
        glPointSize(5);
        glColor3f(0,1,0);
        glBegin(GL_POINTS);
        glVertex3f(cp[i][0],cp[i][1],cp[i][2]);
        glEnd();
    }
    // Calcola le coordinate omogenee dei punti di controllo
    coordinateOmogenee(cp,cpw,7,w);

    glColor3f(1.0f, 1.0f, 1.0f); // white

    GLUnurbsObj * theNurb;

    theNurb= gluNewNurbsRenderer();
    // Imposta la callback per gli errori NURBS
    gluNurbsCallback(theNurb,GLU_ERROR,(GLvoid(*))nurbsError);
    // Inizia a disegnare una curva NURBS
    gluBeginCurve(theNurb);
    // Disegna una curva NURBS
    gluNurbsCurve(theNurb,10,knots,4,&cpw[0][0],3,GL_MAP1_VERTEX_4);
    gluEndCurve(theNurb);

    glFlush();

}


int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Cerchio");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


