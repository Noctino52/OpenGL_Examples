/*Esercizio:
Scrivere un programma (con OpenGL) per il rendering
 di una superficie di Bezier razionale e non
 di ordine (4,4) utilizzando le funzioni di OpenGL
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLfloat ctrlpoints[4][4][3] ={{{0,0,0},{1,0,.5},{2,0,1},{3,0,0}},
                              {{0,1,0},{1,1,3},{2,1,3},{3,1,0}},
                              {{0,2,0},{1,2,3},{2,2,3},{3,2,0}},
                              {{0,3,0},{1,3,1},{2,3,0.5},{3,3,0}}};
float w[4][4] = {{1,.5,.5,1},{1,.5,.5,1},{1,.5,.5,1},{1,.5,.5,1}};

float cw[4][4][4];

void coordinateOmogenee(float a[][4][3], float b[][4][4], float pesi[][4])
{
    int i,j,k;

    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            b[i][j][3]=pesi[i][j];
        }
    }

    for (i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            for(k=0;k<3;k++)
            {
                b[i][j][k]=a[i][j][k]*pesi[i][j];
            }
        }
    }
}

void display2(void) {
    glClearColor(1.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Abilita il test della profondità
    glEnable(GL_DEPTH_TEST);
    // Imposta la matrice di proiezione
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Imposta la prospettiva
    glFrustum(-2, 2, -2, 2, 1, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Imposta la posizione della telecamera e il punto di vista
    gluLookAt(2, 2, 4, 1.5, 1.5, 1.5, 0, 1, 0);
    // Calcola le coordinate omogenee per i punti di controllo
    coordinateOmogenee(ctrlpoints, cw, w);
    // Imposta la mappa dei vertici a 4 dimensioni
    glMap2f(GL_MAP2_VERTEX_4, 0, 1, 4, 4, 0, 1, 16, 4, &cw[0][0][0]);
    glEnable(GL_MAP2_VERTEX_4);
    // Imposta la griglia della mappa
    glMapGrid2f(30, 0.0, 1.0, 30, 0.0, 1.0);
    // Valuta e disegna la mesh con linee
    glEvalMesh2(GL_LINE, 0, 30, 0, 30);
    glFlush();
}
void display (void)
{
    glClearColor(1.0,0.0,0.2,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-2,2,-2,2,1,5);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(2,1,4,1.5,1.5,1.5,0,1,0);
    glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,0,1,12,4,&ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(30, 0.0, 1.0, 8,0.0,1.0);
    glEvalMesh2(GL_LINE, 0, 30,0,8);
    glFlush();

}


int main (int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode( GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Superfici Beizer");
    glutDisplayFunc(display2);
    glutMainLoop();

}
//Nota:
// Svantaggio Beizer Razionali:Se modifico un peso modifico tutta la curva
//Beizer ottime se uniforme




