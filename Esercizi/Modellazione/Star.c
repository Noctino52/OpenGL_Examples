/* ESERCIZIO:
 * Scrivere un programma che disegni una stella a cinque punte. Utilizzando le callback per la tastiera, la stella deve interattivamente ruotare su sé stessa,
 * cambiare dimensioni e spostarsi all’interno della finestra.
 * Suggerimento per il disegno: Creare un GL_TRIANGLE_FAN come per disegnare un cerchio,
 * ma utilizzando due lunghezze diverse per il raggio, da utilizzare alternativamente tra vertici successivi.
 *
 * CONTINUO:
 * Utilizzare le callback per il mouse per gestire le rotazioni, le scalature e le traslazioni.
 * Suggerimento: eseguire una iterazione ogni 10 pixel di spostamento del puntatore
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float starRotation = 0.0f;
float starScale = 1.0f;
float starPositionX = 0.0f;
float starPositionY = 0.0f;

float windowWidth=640;
float windowHeight=480;


void drawStar() {
    // Salva la matrice corrente nello stack della matrice e sposta, ruota e scala la matrice di trasformazione
    // per posizionare e orientare la stella.

    // Inizia la definizione del poligono come un TRIANGLE_FAN.
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(0.0f, 0.0f);
    float outerRadius = 0.5f;
    float innerRadius = 0.1f;

    // Definisce gli angoli per ogni vertice della stella.
    for (int i = 0; i <= 10; ++i) {
        float angle = (i * 36.0f + 18.0f) * 3.14159265f / 180.0f;

        // Alterna la posizione dei vertici tra raggio esterno e interno.
        if (i % 2 == 0) {
            glVertex2f(outerRadius * sin(angle), outerRadius * cos(angle));
        } else {
            glVertex2f(innerRadius * sin(angle), innerRadius * cos(angle));
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawStar();
    glutSwapBuffers();
}


// Funzione di callback per la gestione del movimento del mouse
int old_x=0;
int old_y=0;
int valid=0;
int mouse_button=0;

void mouse_func (int button, int state, int x, int y) {
    valid = state == GLUT_DOWN;
    //Sinistra=Scala, Centrale=Traslazione, Destra=Ruota
    if(button==GLUT_LEFT_BUTTON) mouse_button=0;
    else if (button==GLUT_MIDDLE_BUTTON) mouse_button=1;
    else if (button==GLUT_RIGHT_BUTTON)mouse_button=2;
}

void motion_func (int x, int y) {
    if (valid) {
        int dx = old_x - x;
        int dy = old_y - y;
        /* do something with dx and dy */
        printf("%d \n",dx);
        if(dx>10){
            if (mouse_button==1) glTranslatef(0.1f, 0.0f, 0.0f);
        }
        if(dy>10){
            if (mouse_button==1) glTranslatef(0.0f, -0.1f, 0.0f);
        }
        if(dx<-10){
            if (mouse_button==1) glTranslatef(-0.1f, 0.0f, 0.0f);
        }
        if(dy<-10){
            if (mouse_button==1) glTranslatef(0.0f, 0.1f, 0.0f);
        }

        if(dx>10 || dy<-10){
            if(mouse_button==0) glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
            else if(mouse_button==2) glScalef(0.9f, 0.9f, 1.0f);
        }
        else if(dy>10 || dx<-10){
            if(mouse_button==0)glRotatef(10.0f, 0.0f, 0.0f, -1.0f);
            else if(mouse_button==2) glScalef(1.1f, 1.1f, 1.0f);
        }

    }
    old_x = x;
    old_y = y;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
            break;
        case 'e':
            glRotatef(10.0f, 0.0f, 0.0f, -1.0f);
            break;
        case 'z':
            glScalef(0.9f, 0.9f, 1.0f);
            break;
        case 'x':
            glScalef(1.1f, 1.1f, 1.0f);
            break;
        case 'w':
            glTranslatef(0.0f, 0.1f, 0.0f);
            break;
        case 'a':
            glTranslatef(-0.1f, 0.0f, 0.0f);
            break;
        case 's':
            glTranslatef(0.0f, -0.1f, 0.0f);
            break;
        case 'd':
            glTranslatef(0.1f, 0.0f, 0.0f);
            break;

        case 27: // ESC key
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Star");
    glutDisplayFunc(display);
    //Comandi : w-a-s-d= Traslazioni , q,e=Ruotazioni, z-x=Scala
    glutKeyboardFunc(keyboard);
    //Comandi (tenere premuto e trascinare) : Sx=Ruotazione , Middle=Traslazione, Dx=Scala
    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}