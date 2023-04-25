/* ESERCIZIO:
 * Modellare un cronometro 3D:
 * – Dotato dei tasti: START, STOP, RESET
 * – Il tasto START fa partire il cronometro, il tasto STOP ferma il cronometro, il tasto RESET azzera il cronometro
 * – La lancetta dei secondi avanza ad ogni secondo
 * – La lancetta dei minuti avanza ogni qualvolta la lancetta dei secondi completa un giro
 */
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

float angle_s = 0.0f; // angolo della lancetta dei secondi
float angle_m = 0.0f; // angolo della lancetta dei minuti
int is_running = 0; // indica se il cronometro è in funzione
time_t start_time;

char timer_s[3];
char timer_m[3];

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Disegna il quadrante del cronometro
    //Lo ruoto per dargli un'effetto 3d
    glRotatef(30, 1.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); // colore bianco
    glVertex3f(-0.8f, 0.8f, 0.0f);
    glVertex3f(-0.8f, -0.8f, 0.0f);
    glVertex3f(0.8f, -0.8f, 0.0f);
    glVertex3f(0.8f, 0.8f, 0.0f);
    glEnd();

    //Punto d'origine
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f); // colore blu
    glVertex2f(0.0, 0.0);
    float radius = 0.5;
    //Definisco una circonferenza di punti per definire un cerchio come un poligono
    for (int i = 0; i <= 40; ++i) {
        float angle = i * 2.0 * 3.14159 / 40;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(4.0f);

    // Disegna la lancetta dei secondi
    glPushMatrix();
    glRotatef(angle_s, 0.0f, 0.0f, 1.0f); // ruota la lancetta dei secondi
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // colore rosso
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.4f, 0.0f);
    glEnd();
    glPopMatrix();

    // Disegna la lancetta dei minuti
    glPushMatrix();
    glRotatef(angle_m, 0.0f, 0.0f, 1.0f); // ruota la lancetta dei minuti
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f); // colore verde
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.34f, 0.0f);
    glEnd();
    glPopMatrix();

    // Disegna il tempo trascorso sotto forma di caratteri
    glColor3f(1.0f,0.0f,1.0f);
    glRasterPos2f(0.0,-0.7);
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, timer_m[0]);
    glRasterPos2f(0.05,-0.7);
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, timer_m[1]);
    glRasterPos2f(0.1,-0.7);
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, ':');
    glRasterPos2f(0.15,-0.7);
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, timer_s[0]);
    glRasterPos2f(0.2,-0.7);
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, timer_s[1]);

    glutSwapBuffers();
}

void update(int value) {
    if (is_running) {
        time_t current_time = time(NULL);
        double elapsed_time = difftime(current_time, start_time);
        int minutes = elapsed_time / 60;
        int seconds = (int)elapsed_time % 60;
        //Da int a char
        sprintf(timer_s, "%d", seconds);
        sprintf(timer_m, "%d", minutes);

        angle_s = fmod(elapsed_time, 60.0) * 6.0; // calcola l'angolo della lancetta dei secondi
        if(angle_s==0)angle_m = fmod(elapsed_time / 60.0, 60.0) * 6.0; // calcola l'angolo della lancetta dei minuti
    }
    glutPostRedisplay();
    glutTimerFunc(10000/60, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 's': // START
            if (!is_running) {
                is_running = 1;
                start_time = time(NULL);
            }
            break;
        case 't': // STOP
            is_running = 0;
            break;
        case 'r': // RESET
            angle_s = 0.0f;
            angle_m = 0.0f;
            is_running = 0;
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Cronometro 3D");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // colore di sfondo nero
    glutMainLoop();
    return 0;
}