/* ESERCIZIO:
#Implementare l’algoritmo di de Casteljau per la valutazione di una curva di Bezier di grado n:
#Scrivere un programma (con OpenGL) per il rendering di una curva di Bezier di grado n mediante il metodo uniforme.

 CONTINUO:
 #Disegna la scena usando le funzioni di openGL (scelte glMap e glEvalCords)
 */


#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

float M=2;

typedef struct Vert
{
    float x ;
    float y;
}Vert;


void specialInput(unsigned char key, int xmouse, int ymouse)
{
    switch(key)
    {
        case 'a':
            M+=1;
            break;
        case 's':
            M-=1;
            if(M<1)
                M=1;
            break;
        default:
            break;
    }
    printf("M: %f \n ",M);
    glutPostRedisplay();
}

// Implementazione dell'algoritmo di de Casteljau per la valutazione di una curva di Bezier di grado n
// p_ctr: array dei vertici di controllo
// num_p_ctr: numero di vertici di controllo
// time: parametro della curva di Bezier, compreso tra 0 e 1
Vert casteljau(Vert * p_ctr, int num_p_ctr, float time)
{
    float t;
    int i, s;
    int n_points, n_step;

    n_step = num_p_ctr;
    n_points = num_p_ctr;
    t = time;

    Vert p_contr[n_points];
    Vert p[n_step][n_points];

    // Inizializzazione array dei vertici di controllo
    for(i = 0; i < n_points; i++)
    {
        p_contr[i].x = p_ctr[i].x;
        p_contr[i].y = p_ctr[i].y;
    }

    // Casteljau step 0
    for (i = 0; i < n_points; i++)
    {
        p[0][i].x = p_contr[i].x;
        p[0][i].y = p_contr[i].y;
    }

    // Calcolo dei punti di controllo intermedi
    // Step 1,....,n step
    for (s = 1; s < n_step; s++) //passi, grado curva
    {
        for (i = 0; i < n_points - s; i++)// step points
        {
            p[s][i].x = (1-t) * p[s-1][i].x + t * p[s-1][i+1].x;
            p[s][i].y = (1-t) * p[s-1][i].y + t * p[s-1][i+1].y;
        }
    }

    // Ritorna l'ultimo punto calcolato
    return p[n_step-1][0];
}

/*
 * Disegna la scena usando le funzioni di openGL (scelte glMap e glEvalCords)
void drawSceneMap()
{
    glClearColor(0.3, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    // Definizione dei vertici di controllo
    GLfloat ctrlPoints[4][3] = {
            {-0.4, -0.3, 0},
            {-0.3, 0.4, 0},
            {0.4, 0.4, 0},
            {0.4, -0.3, 0}
    };
    // Disegna la curva di Bezier a partire dai vertici di controllo
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 1);
    for (int i = 0; i < 4; i++){
        glVertex2f(ctrlPoints[i][0],ctrlPoints[i][1]);
    }
    glEnd();

    // Impostazione del tipo di curva
    GLenum curveType = GL_MAP1_VERTEX_3;
    glColor3f(1, 1, 1);
    glMap1f(curveType, 0.0, 1.0, 3, 4, &ctrlPoints[0][0]);
    glEnable(curveType);
    // Disegno della curva di Bezier
    glBegin(GL_LINE_STRIP);
    for (GLfloat t = 0; t <= 1.0; t += 0.001) {
        glEvalCoord1f(t);
    }
    glEnd();

    glFlush();
}
 */

void drawScene()
{
    // Imposta il colore di sfondo e pulisce i buffer
    glClearColor(0.3, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    // Imposta la matrice di proiezione
    glLoadIdentity();

    int num_p_ctr = 4, i;
    float t;
    Vert p_ctr[num_p_ctr];

    // Inizializzazione array dei vertici di controllo
    p_ctr[0].x = -0.4;
    p_ctr[0].y = -0.3;

    p_ctr[1].x = -0.3;
    p_ctr[1].y = 0.4;

    p_ctr[2].x = 0.4;
    p_ctr[2].y = 0.4;

    p_ctr[3].x = 0.4;
    p_ctr[3].y = -0.3;

    // Disegna la curva di Bezier a partire dai vertici di controllo
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 1);
    for (i = 0; i < num_p_ctr; i++){
        glVertex2f(p_ctr[i].x,p_ctr[i].y);
    }

    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    for(t=0;t<1;t=t+(1/M))
    {
        glVertex2f(casteljau(p_ctr,num_p_ctr,t).x,casteljau(p_ctr,num_p_ctr,t).y);
    }

    // Aggiungi il vertice finale della curva di Bezier alla sequenza di vertici
    t=1;
    glVertex2f(casteljau(p_ctr,num_p_ctr,t).x,casteljau(p_ctr,num_p_ctr,t).y);

    glEnd();
    glFlush();

}

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("Beizer");
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(specialInput);
    glutMainLoop();
    return 0;

}
/*
 * Note:
 * un "valutatore" (o "evaluator" in inglese) è una funzione che calcola il valore di una curva di Bezier in un punto specifico.
 * In generale, l'implementazione dell'algoritmo di de Casteljau è un modo comune per implementare un valutatore per una curva di Bezier.
 */