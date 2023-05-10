#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>



float x_eye=0.0, y_eye=0.0, z_eye = 5.0;

void displayDisk()
{
    glClearColor(0.0,0,0.8,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-10,10,-10,10,1,6);
    glMatrixMode( GL_MODELVIEW );
    glTranslatef(0,0,-5);
    glLoadIdentity();
    printf("x:%f y:%f z:%f \n",x_eye,y_eye,z_eye);
    gluLookAt(x_eye,y_eye,z_eye,0,0,0,0,1,0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLUquadricObj *qobj;
    qobj = gluNewQuadric(); //creazione
    //gluQuadricCallback(qobj,GLU_ERROR,(GLvoid(*))errorCallback);//gestione errori
    gluQuadricDrawStyle(qobj,GLU_FILL);
    gluQuadricOrientation(qobj,GLU_OUTSIDE);
    gluQuadricNormals(qobj,GLU_FLAT);
    gluDisk(qobj,3,10,20,1);
    glFlush();
}


void displaySphere()
{
    glClearColor(0.0, 0, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // Seleziona la matrice di proiezione.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Definisce la prospettiva della telecamera.
    glFrustum(-1, 1, -1, 1, 1, 10);
    // Seleziona la matrice di modelview.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Imposta la posizione della telecamera e il punto verso cui guardare.
    gluLookAt(x_eye, y_eye, z_eye, 0, 0, 0, 0, 1, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    // Imposta lo stile di disegno della sfera
    gluQuadricDrawStyle(qobj, GLU_FILL);
    // Imposta l'orientamento della normale delle facce
    gluQuadricOrientation(qobj, GLU_OUTSIDE);
    // Imposta il tipo di normali
    gluQuadricNormals(qobj, GLU_FLAT);
    // Disegna una sfera con raggio 0.80, suddivisa in 10 latitudini e 10 longitudini.
    gluSphere(qobj, 0.80, 10, 10);
    glFlush();
}

void displayCylinder()
{
    glClearColor(0.0,0,0.8,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Modalità di visualizzazione prospettica
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // Definizione della prospettiva
    glFrustum(-2.5,2.5,-2.5,2.5,1,5);

    // Modalità di visualizzazione oggetto
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Impostazione della posizione e dell'orientamento della telecamera (occhio)
    gluLookAt(x_eye,y_eye,z_eye,0,0,0,0,1,0);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColor3f(1.0, 1.0, 1.0);

    // Creazione di un nuovo oggetto quadrico
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();

    // Impostazione della callback di gestione degli errori del quadrico
    //gluQuadricCallback(qobj,GLU_ERROR,(GLvoid(*))errorCallback);

    // Impostazione dello stile di visualizzazione del quadrico (solo superficie)
    gluQuadricDrawStyle(qobj,GLU_FILL);
    // Impostazione dell'orientamento delle normali del quadrico (esterno)
    gluQuadricOrientation(qobj,GLU_OUTSIDE);
    // Impostazione delle normali del quadrico (piane)
    gluQuadricNormals(qobj,GLU_FLAT);

    // Disegno
    gluCylinder(qobj,0, 0.75, 8, 10,10 );

    glFlush();
}

void keyword (unsigned char key, int xmouse, int ymouse)
{
    switch (key){
        case 'q':
        {
            x_eye+=0.2;
            glutPostRedisplay();
            break;
        }
        case 'w':
        {
            x_eye-=0.2;
            glutPostRedisplay();
            break;
        }
        case 'a':
        {
            y_eye+=0.2;
            glutPostRedisplay();
            break;
        }
        case 's':
        {
            y_eye-=0.2;
            glutPostRedisplay();
            break;
        }
        case 'z':
        {
            z_eye+=0.2;
            glutPostRedisplay();
            break;
        }
        case 'x':
        {
            z_eye-=0.2;
            glutPostRedisplay();
            break;
        }
        default:
            break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Solids");
    glutDisplayFunc(displayDisk);
    glutKeyboardFunc(keyword);
    glutMainLoop();
    return 0;
}
