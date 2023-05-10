/*Esercizio:
 *  Scrivere un programma (con OpenGL) per il rendering di una superficie B-Spline/NURBS/NURBS con trimming di ordine (4,4) utilizzando le funzioni di OpenGL
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265

float ctrlpoints[4][4][3] ={{{-3,-3,-3},{-3,-1,-3},{-3,1,-3},{-3,3,-3}},
                            {{-1,-3,-3},{-1,-1,3},{-1,1,3},{-1,3,-3}},
                            {{1,-3,-3},{1,-1,3},{1,1,3},{1,3,-3}},
                            {{3,-3,-3},{3,-1,-3},{3,1,-3},{3,3,-3}}};

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

void display1() //BSPLINE
{
    glClearColor(0.0,0.2,0.6,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //Visuale ortogonale dall'alto, traslo sulle z per vederlo tutto
    glOrtho(-3.5,3.5,-3.5,3.5,1,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,-4);

    glColor3f(1.0, 1.0, 1.0);
    GLUnurbsObj * theNurb;
    GLfloat knots[8] = {0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0};
    theNurb= gluNewNurbsRenderer();
    gluBeginSurface(theNurb);
    gluNurbsProperty(theNurb,GLU_DISPLAY_MODE,GLU_OUTLINE_POLYGON);
    gluNurbsSurface(theNurb,8,knots,8,knots,4*3,3,&ctrlpoints[0][0][0],4,4,GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);
    glFlush();
}


void display2() //NURBS
{
    glClearColor(0.0,0.2,0.6,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //Visuale ortogonale dall'alto, traslo sulle z per vederlo tutto
    glOrtho(-3.5,3.5,-3.5,3.5,1,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,-4);

    glColor3f(1.0, 1.0, 1.0);
    GLUnurbsObj * theNurb;
    GLfloat knots[8] = {0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0};
    coordinateOmogenee(ctrlpoints,cw,w);
    theNurb= gluNewNurbsRenderer();
    gluBeginSurface(theNurb);
    gluNurbsProperty(theNurb,GLU_DISPLAY_MODE,GLU_OUTLINE_POLYGON);
    gluNurbsSurface(theNurb,8,knots,8,knots,4*4,4,&cw[0][0][0],4,4,GL_MAP2_VERTEX_4);
    gluEndSurface(theNurb);
    glFlush();

}

void display3() //TRIMMING
{
    /*
        Scrivere un programma (con OpenGL) per il rendering di una
        superfice NURBS di grado(4,4) con trimming utilizzando le funzioni
        di OpenGL
    */

    GLfloat E[5][2] = {{0,0},{1,0},{1,1},{0,1},{0,0}};
    GLfloat P[5][2] = {{0.3,0.3},{0.3,0.7},{0.7,0.7},{0.7,0.3},{0.3,0.3}};

    glClearColor(0.0,0.2,0.6,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //Visuale ortogonale dall'alto, traslo sulle z per vederlo tutto
    glOrtho(-3.5,3.5,-3.5,3.5,1,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,-4);

    glColor3f(1.0, 1.0, 1.0);
    GLUnurbsObj * theNurb;
    GLfloat knots[8] = {0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0};
    coordinateOmogenee(ctrlpoints,cw,w);
    theNurb= gluNewNurbsRenderer();
    gluBeginSurface(theNurb);
    gluNurbsProperty(theNurb,GLU_DISPLAY_MODE,GLU_OUTLINE_POLYGON);
    gluNurbsSurface(theNurb,8,knots,8,knots,4*4,4,&cw[0][0][0],4,4,GL_MAP2_VERTEX_4);
    gluBeginTrim(theNurb);//confine esterno
    gluPwlCurve(theNurb,5,&E[0][0],2,GLU_MAP1_TRIM_2);
    gluEndTrim(theNurb);
    gluBeginTrim(theNurb);
    gluPwlCurve(theNurb,5,&P[0][0],2,GLU_MAP1_TRIM_2);
    gluEndTrim(theNurb);
    gluEndSurface(theNurb);
    glFlush();

}

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Superfice Bspline & Nurbs");
    glutDisplayFunc(display3);
    glutMainLoop();
    return 0;
}

/*
 * Nota:
 * Es 1: Si nota subito un'uniformità dei poligoni che costruiscono la superficie
 * Es 2: Notiamo che in base al peso (quando w=0.5 occupa più spazio) dato i poligoni occupano parti differenti della superficie
 * Es 3: E' stato creato un parallelepipedo di contorno alla superficie mentre esternamenteo non è stato "tagliato" nulla.
 */
