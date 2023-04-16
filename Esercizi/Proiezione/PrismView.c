/* ESERCIZIO:
 * Disegnare un Prisma a base ottagonale con centro base vicina in (0.2,0.2,-0.5) e centro base lontana in (0.2, 0.2,-1.5) e
 * La base circoscritta dalla circonferenza di raggio 0.5.
 * Dopo avere inizializzato il depth buffer e la sua visualizzazione ortogonale (glOrto).
 * Ricordati di usare glTranslatef(0.0,0.0, -3.0) e di usare mouse e tastiera combinati per modificare
 * i tre valori di altezza larghezza e profondità del Volume di Vista
 *
 * CONTINUO:
 * Sostituire glFrustum a glOrtho e vedere che succede,
 * dopodichè sostituire glFrustum con gluPerspective e vedere che succede.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>


// Definizione dei vertici dell'ottagono di base

float vertices[8][2] = {
        {0.7, 0.2},
        {0.553, 0.553},
        {0.2, 0.7},
        {-0.15, 0.553},
        {-0.3, 0.2},
        {-0.15, -0.15},
        {0.2, -0.3},
        {0.553, -0.15},
};

// Funzione per disegnare la faccia laterale del prisma
void draw_side(int i, int j) {
    glBegin(GL_QUADS);
    glColor3f(0,1,0);
    glVertex3f(vertices[i][0], vertices[i][1], -0.5);
    glVertex3f(vertices[j][0], vertices[j][1], -0.5);
    glVertex3f(vertices[j][0], vertices[j][1], -1.5);
    glVertex3f(vertices[i][0], vertices[i][1], -1.5);
    glColor3f(1,1,1);
    glEnd();
}

// Funzione per disegnare il prisma
void draw_prism() {

    // Disegna le facce laterali
    for (int i = 0; i < 8; i++) {
        draw_side(i, (i+1)%8);
    }

    //Superiore
    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; i++) {
        glColor3f(1, 1, 1);
        glVertex3f(vertices[i][0], vertices[i][1], -0.5);
    }
    glEnd();

// Definizione della base inferiore
    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; i++) {
        glColor3f(1, 1, 0);
        glVertex3f(vertices[i][0], vertices[i][1], -1.5);
    }
    glEnd();
}



static float height = 1;
static float width = 1;
static float depth = 1;

void check_cap(){
    //CAP sui valori massimali/minimali (l'immaggine diverebbe troppo distorta senza)
    if(width>=2.5)width=2.5;
    else if(width<=0.5)width=0.5;
    if(height>=2.5)height=2.5;
    else if(height<0.5)height=0.5;
    if(depth<=-5)depth=-5;
    if(depth>=5)depth=5;

    printf("left = %f\n", -width);
    printf("right = %f\n", width);
    printf("bottom = %f\n", -height);
    printf("top = %f\n", height);
    printf("near = %f\n", depth);
    printf("far = %f\n", 4 + depth);
    printf("===============\n");
}

// Funzione per disegnare la scena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //E' necessario richiamare glMatrixMode(GL_PROJECTION) ogni volta che si modifica la proiezione
    //per assicurarsi che le operazioni di trasformazione successive vengano applicate alla matrice corretta.
    glMatrixMode(GL_PROJECTION);
    //Imposta la matrice corrente su una matrice identità, che rappresenta la trasformazione nullo.
    glLoadIdentity();
    //Inizia con valori (-1,1,-1,1,1,5), come richiesto
    //Default
    glOrtho(-width, width, -height, height, depth, depth+4);
    //Frustum:
    //glFrustum(-width, width, -height, height, depth, depth+4);
    //Perspective:
    //gluPerspective(width*30, height, depth, depth+4);
    draw_prism();
    glutSwapBuffers();
}


int old_x=0;
int old_y=0;
int valid=0;
int mouse_button=0;

//Mouse callback pt1
void mouse(int button, int state, int x, int y) {
    valid = state == GLUT_DOWN;
    //Sinistra=Scala, Centrale=Traslazione, Destra=Ruota
    if(button==GLUT_LEFT_BUTTON) mouse_button=0;
    else if (button==GLUT_MIDDLE_BUTTON) mouse_button=1;
    else if (button==GLUT_RIGHT_BUTTON)mouse_button=2;
}

//Mouse callback pt2
void passive(int x, int y) {

    int dx = old_x - x;
    int dy = old_y - y;

    if (dx > 5 || dy < -5) {
        if (mouse_button == 1) depth += 0.01;
    } else if (dy > 5 || dx < -5) {
        if (mouse_button == 1) depth -= 0.01;
    }
    if (dx > 5) {
        if (mouse_button == 0) width += 0.01;
        if (mouse_button == 2) height += 0.01;
    }
    if (dy > 5) {
        if (mouse_button == 0) width += 0.01;
        if (mouse_button == 2) height += 0.01;
    }
    if (dx < -5) {
        if (mouse_button == 0) width -= 0.01;
        if (mouse_button == 2) height -= 0.01;
    }
    if (dy < -5) {
        if (mouse_button == 0) width -= 0.01;
        if (mouse_button == 2) height -= 0.01;
    }
    old_x = x;
    old_y = y;

    //CAP sui valori massimali/minimali (l'immaggine diverebbe troppo distorta senza)
    check_cap();

    glutPostRedisplay();
}

//Keyboard callback
void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 'w':
            height += 0.1;
            break;
        case 's':
            height -= 0.1;
            break;
        case 'a':
            width -= 0.1;
            break;
        case'd':
            width += 0.1;
            break;
        case 'x':
            depth += 0.1;
            break;
        case 'z':
            depth -= 0.1;
            break;
    }
    //CAP sui valori massimali/minimali (l'immaggine diverebbe troppo distorta senza)
    check_cap();

    glutPostRedisplay();
}

// Funzione principale
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Prisma a base ottagonale");
    glTranslatef(0,0,-3.0);

    //I tre tipi di proeizione sono modificabili da display() Default: glOrto
    glutDisplayFunc(display);
    //Comandi: W,S = +/- Altezza , A,D= +/- Larghezza , Z,X= +/- Profondità
    glutKeyboardFunc(keyboard);
    //Comandi (tenere premuto e trascinare) : Sx=Altezza , Middle=Profondità, Dx=Larghezza
    glutMouseFunc(mouse);
    glutMotionFunc(passive);
    glutMainLoop();
    return 0;
}
/*
 * Commenti:
 *
 * glOrto:Porta alla visualizzazione di un ottagono regolare (La faccia superiore, di colore bianco), quindi,
 * è stata effettuata una proiezione ortogonale di cui si visualizza il risulatto sul piano dell'asse z (Per questo non ci sono i  lati del prisma)
 * Cambiare i valori di x/y di questo tipo di proiezione porta la deformazione dell'ottagono, modificando la z invece,
 * Possiamo passare a vedere la faccia inferiore (gialla) , come se il nostro occhio si stia spostando da fuori a dentro il prisma.
 *
 * Perchè è stato utilizzata glTranslatef(0,0,-3.0)?:
 * Il prisma è stato disegnato in altezza (z) da -0.5 a -1.5, inizialmente, essendo che il nostro occhio (glOrto) è impostato da 1 a 5, senza questa trslazione
 * partiremo da dentro il prisma, vedendo direttamente la faccia gialla (Ricordiamo che il sistema di riferimento locale dell'oggetto è invertito di segno rispetto a quello della proiezione).
 *
 * glFrustum:
 * A differenza di glOrto, introduce una sorta di "percezione della distanza", il prisma infatti appare più grande, man mano che mi avvicino.
 * Entrando dentro il prisma adesso, posso anche osservare le sue facce (colorate di verde), come se, più l'oggetto è distante, più è distorto (ruotato, scalato)
 *
 * glPerspective:
 * Come glFrustum, ma mantiene costante il rapporto larghezza/altezza dell'area di visualizzazione,
 * mentre l'apertura verticale dell'angolo della telecamera (parametro fovy)definisce l'angolo di visualizzazione verticale.
 *
 */