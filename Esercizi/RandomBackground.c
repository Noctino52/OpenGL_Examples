/* ESERCIZIO:
 * Scrivere un programma che:
 * • apra una finestra e pulisca il background
 * con un colore predefinito;
 * • si metta in attesa di un input da tastiera;
 * • se premuto il tasto SPAZIO generi un colore casuale e lo usi come colore di sfondo;
 * • forzi un redisplay.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

float windowWidth = 640; // larghezza della finestra
float windowHeight = 480; // altezza della finestra

void keyboard(unsigned char key, int x, int y) {
    // generazione di numeri casuali compresi tra 0 e 1 per impostare il colore di sfondo della finestra
    double random_r = (double) rand() / (double) RAND_MAX; // componente rossa
    double random_g = (double) rand() / (double) RAND_MAX; // componente verde
    double random_b = (double) rand() / (double) RAND_MAX; // componente blu
    double random_a = (double) rand() / (double) RAND_MAX; // componente alpha
    // gestione degli eventi in base al tasto premuto
    switch (key) {
        case 32: // tasto spazio
            glClearColor(random_r, random_g, random_b, random_a); // imposta il colore di sfondo della finestra
            break;
        case 27: // tasto Esc
            exit(0); // termina il programma
            break;
        default: // gestione degli altri tasti
            break;
    }
    glutPostRedisplay(); // richiede la ridisegnazione della finestra
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT); // cancella il buffer di colore
    glutSwapBuffers(); // scambia il buffer di lavoro con quello visualizzato
}


int main(int argc, char** argv) {
    srand(time(NULL)); // inizializza il seme del generatore di numeri casuali
    glutInit(&argc, argv); //
    glutInitDisplayMode(GLUT_RGB); // imposta la modalità di visualizzazione
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("RandomBackgorund");
    glutDisplayFunc(display);
    //Comandi: Space=Cambia colore dello sfondo
    glutKeyboardFunc(keyboard);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // imposta il colore di sfondo della finestra iniziale a nero
    glutMainLoop(); // avvia il ciclo di eventi della finestra OpenGL
    return 0;
}