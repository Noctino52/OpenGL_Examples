/* ESERCIZIO:
Scrivere un programma (con OpenGL) per il rendering di curve di Bezier composite,
 consentendo l’input dei punti di controllo mediante mouse
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265

typedef struct vertici
{
    float x,y,z;

}vertici;


vertici punti[100];

typedef struct Curva
{
    int n;
    float punti[10][3]; // max 10 punti di controllo

}Curva;

Curva curve[10]; // max 10 curve

int num_curve_attuali=0;
int num_punti_attuali=0;

Curva tmp;

float w,h;

void stampaMatrice(float matrice [][3],int r)
{
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<3;j++)
        {
            printf("%f ",matrice[i][j]);
        }
        printf("\n");
    }
}

void display (void)
{
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor(0.3,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Disegna i punti
    glPointSize(10);
    for(int i=0; i<num_punti_attuali; i++)
    {
        glBegin(GL_POINTS);
        glColor3f(0,1,0);
        glVertex2f(punti[i].x,punti[i].y);
        glEnd();
    }

    // Disegna le curve
    for(int i=0; i<num_curve_attuali; i++)
    {
        glColor3f(1.0,1.0,1.0);
        GLfloat* ctrlPoints = &curve[i].punti[0][0];
        int n = curve[i].n;

        // Definisce la curva di Bezier tramite la funzione glMap1f
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, n, ctrlPoints);
        glEnable(GL_MAP1_VERTEX_3);

        // Imposta la griglia di valutazione per la curva
        glMapGrid1f(30, 0.0, 1.0);

        // Valuta la curva e disegna il risultato usando la funzione glEvalMesh1
        glEvalMesh1(GL_LINE, 0, 30);
    }

    glFlush();
}

void savePoint(int x, int y)
{
    // Calcola le coordinate normalizzate del punto
    float a = x / (w/2) - 1;
    float b = (y / (h/2)) * (-1) + 1;

    // Aggiunge il punto alla curva temporanea
    int n = tmp.n;
    tmp.n++;
    tmp.punti[n][0] = a;
    tmp.punti[n][1] = b;
    tmp.punti[n][2] = 0;

    // Aggiunge il punto all'elenco dei punti
    punti[num_punti_attuali].x = a;
    punti[num_punti_attuali].y = b;
    num_punti_attuali++;
}

void mouse(int bin, int state , int x , int y)
{
    // Se il pulsante sinistro del mouse è stato premuto
    if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Salva le coordinate del punto e ridisegna la scena
        savePoint(x,y);
        glutPostRedisplay();
    }
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':
        {
            // Salvataggio della curva temporanea nella lista delle curve
            curve[num_curve_attuali]=tmp;
            num_curve_attuali++;

            // Il primo punto della nuova curva è uguale all'ultimo punto della curva precedente
            tmp.punti[0][0]=tmp.punti[tmp.n-1][0];
            tmp.punti[0][1]=tmp.punti[tmp.n-1][1];
            tmp.punti[0][2]=tmp.punti[tmp.n-1][2];
            tmp.n=1;

            // Richiesta di disegnare nuovamente la finestra
            glutPostRedisplay();
            break;
        }
    }
}

/* Main */

int main (int argc, char** argv)
{
    int i;
    i=0;

    // Inizializzazione dei campi n di ogni curva a 0
    for (i=0; i<10; i++)
    {
        curve[i].n=0;
    }

    // Inizializzazione di GLUT e creazione della finestra
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Beizer_Comp");

    // Registrazione delle funzioni di callback
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    // Avvio del loop principale di GLUT
    glutMainLoop();
}