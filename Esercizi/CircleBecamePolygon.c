/* ESERCIZIO: Scrivere un programma che disegni un cerchio rosso, che man mano diventa blu,
 *
 * Continuo:
 * Modificare il programma  in modo da far variare interattivamente il numero dei lati
 * del poligono regolare inscritto nella circonferenza:
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

float windowWidth = 640; // larghezza della finestra
float windowHeight = 480; // altezza della finestra

//Numero massimo di segmenti che compongono il cerchio
int num_segments = 40;


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Solo il punto d'origine del cerchio deve essere rosso
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    //I restanti punti sono blu
    glColor3f(0.0, 0.0, 1.0);
    float radius = 0.5;
    //Definisco una circonferenza di punti per definire un cerchio come un poligono
    for (int i = 0; i <= num_segments; ++i) {
        float angle = i * 2.0 * 3.14159 / num_segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    // gestione degli eventi in base al tasto premuto
    switch (key) {
        case 8: // tasto backspace
            if(num_segments<40)
                num_segments+=2; //Aumento il numero di segmenti
            break;
        case 32: // tasto spazio
            if(num_segments>6)
                num_segments-=2; //diminiusco il numero di segmenti
            break;
        case 27: // tasto Esc
            exit(0); // termina il programma
            break;
        default:
            break;
    }
    glutPostRedisplay(); // richiede la ridisegnazione della finestra (richiama display)
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Blue circle became polygon");
    glutDisplayFunc(display);
    //Comandi:
    //Space= Diminiusce di 2 il numero di segmenti che compongono il poligono (max 6)
    //Backspace= Aggiunge di 2 il numero di segmenti che compongono il poligono (max 40)
    glutKeyboardFunc(keyboard);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutMainLoop();
    return 0;
}