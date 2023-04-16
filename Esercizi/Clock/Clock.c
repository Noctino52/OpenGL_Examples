/* ESERCIZIO:
 * Modellare un orologio 2D la lancetta dell’ora avanza ad ogni giro completo della lancetta dei minuti la lancetta dei minuti avanza con il
 * trascinamento del mouse quando il tasto sx è premuto
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
#include <stdio.h>

float windowWidth = 640; // larghezza della finestra
float windowHeight = 480; // altezza della finestra

//Numero massimo di segmenti che compongono il cerchio
int num_segments = 40;


float h_range=0;
float m_range=0;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Punto d'origine
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    //I restanti punti sono blu
    float radius = 0.5;
    //Definisco una circonferenza di punti per definire un cerchio come un poligono
    for (int i = 0; i <= num_segments; ++i) {
        float angle = i * 2.0 * 3.14159 / num_segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(4.0f);

    //Disegna lancetta ore
    glBegin(GL_LINES);
    glColor3f(1.0f,0,0);
    glVertex2f(0,0);

    float h_angle = h_range * 3.14159 ;
    float h_x = (radius-0.1) * cos(h_angle);
    float h_y = (radius-0.1) * sin(h_angle);
    glVertex2f(h_x, h_y);
    glColor3f(1,1,1);
    glEnd();

    //Disegna lancetta minuti
    glBegin(GL_LINES);
    glColor3f(0,1.0f,0);
    glVertex2f(0,0);

    float m_angle = m_range * 3.14159 ;
    float m_x = (radius-0.03) * cos(m_angle);
    float m_y = (radius-0.03) * sin(m_angle);
    glVertex2f(m_x, m_y);
    glColor3f(1,1,1);
    glEnd();


    glutSwapBuffers();
}

// Funzione di callback per la gestione del movimento del mouse
int old_x=0;
int old_y=0;
int mouse_button=0;

void mouse_func (int button, int state, int x, int y) {
    if(button==GLUT_LEFT_BUTTON) mouse_button=0;
    else if (button==GLUT_MIDDLE_BUTTON) mouse_button=1;
    else if (button==GLUT_RIGHT_BUTTON)mouse_button=2;
}

int num=0;
void motion_func (int x, int y) {
    int dx = old_x - x;
    int dy = old_y - y;
    if(dx>20 || dy<-20){
        if(mouse_button==0){
            m_range-=0.034f;
            if(m_range>=0.49f && m_range<0.52f) h_range-=0.18f;
        }
        //printf("m_range=%f , h_range=%f  num=%d\n ",m_range,h_range,num);
    }
    if(m_range<=-1)m_range=1;
    if(h_range<=-0.98)h_range=1;
    old_x = x;
    old_y = y;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Clock");
    glutDisplayFunc(display);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    //Comandi: tenere premuto SX per ruotare la lancetta dei minuti in senso orario
    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glutMainLoop();
    return 0;
}