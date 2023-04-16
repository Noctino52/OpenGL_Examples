/* ESERCIZIO: Scrivere un programma che disegni un anello(toro 2D) blu,
 * Continuo:
 * Man mano che ci si avvicina all'origine,  l'anello diventa magenta.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

float windowWidth = 640; // larghezza della finestra
float windowHeight = 480; // altezza della finestra

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    float inner_radius = 0.25; //raggio interno dell'anello
    float outer_radius = 0.6; //raggio esterno dell'anello
    int num_segments = 100; //numero di segmenti del poligono ad anello
    float angle_step = 2.0 * M_PI / num_segments;
    float angle = 0.0;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= num_segments; ++i) {
        //punto interno dell'anello
        //Solo il punto d'origine dell'anello deve essere un simil magenta (rosso e un pò di blu)
        glColor3f(0.6, 0.0, 0.3);
        float x_in = inner_radius * cos(angle);
        float y_in = inner_radius * sin(angle);
        glVertex2f(x_in, y_in);
        //punto esterno dell'anello
        float x_out = outer_radius * cos(angle);
        float y_out = outer_radius * sin(angle);
        glColor3f(0.0, 0.0, 1.0); //colore blu per il punto esterno
        glVertex2f(x_out, y_out);
        angle += angle_step;
    }
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Blue ring");
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutMainLoop();
    return 0;
}