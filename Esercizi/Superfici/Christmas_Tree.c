#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

const GLfloat R = 0.5f;
const GLfloat r = 0.2f;
const GLfloat Pi = 3.1415926536f;

float x_eye=0.0, y_eye=0.0, z_eye = 2.0;
const GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] =  {0.0f, 0.0f, 1.0f, 0.0f };



// Funzione che restituisce il coseno di un angolo dato in radianti
GLfloat cosP(GLfloat R, int angolo)
{
    return (R*cos(angolo * Pi / 180));
}

// Funzione che restituisce il seno di un angolo dato in radianti
GLfloat sinP(GLfloat R, int angolo)
{
    return (R*sin(angolo * Pi / 180));
}

void creaStella (void)
{
    glPushMatrix();

    glTranslated(0.0,3.2,-7);
    glRotated(180,1,0,0);
    glRotated(35,0.0, 0.0, 1.0);

    // Array bidimensionale che contiene le componenti speculari del materiale
    float specular[2][4]={{1,1,1,1},{0,0,0,1}};

    //luce bianca
    float stella [3]={1,0.8,0};
    float position [3]={0,1,0};
    glLightfv(GL_LIGHT2, GL_DIFFUSE,&stella[0]);
    glLightfv(GL_LIGHT2, GL_SPECULAR,&specular[0]);
    glLightfv(GL_LIGHT2, GL_POSITION, position);
    glEnable(GL_LIGHT2);

    // Colore della stella
    glColor3f(1,0.8,0);

    //Cordinate die punti
    GLfloat puntoA[3] = {0,R,-8};
    GLfloat puntoB[3] = {cosP(R,18),sinP(R,18),-8};
    GLfloat puntoC[3] = {cosP(R,54),-sinP(R,54),-8};
    GLfloat puntoD[3] = {-cosP(R,54),-sinP(R,54),-8};
    GLfloat puntoE[3] = {-cosP(R,18),sinP(R,18),-8};
    GLfloat puntoa[3] = {0,-r,-8};
    GLfloat puntob[3] = {-cosP(r,18),-sinP(r,18),-8};
    GLfloat puntoc[3] = {-cosP(r,54),sinP(r,54),-8};
    GLfloat puntod[3] = {cosP(r,54),sinP(r,54),-8};
    GLfloat puntoe[3] = {cosP(r,18),-sinP(r,18),-8};

    //disegno i punti
    glBegin(GL_POLYGON);
    glVertex2fv(puntoa);
    glVertex2fv(puntob);
    glVertex2fv(puntoc);
    glVertex2fv(puntod);
    glVertex2fv(puntoe);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2fv(puntoA);
    glVertex2fv(puntod);
    glVertex2fv(puntoc);

    glVertex2fv(puntod);
    glVertex2fv(puntoB);
    glVertex2fv(puntoe);

    glVertex2fv(puntoe);
    glVertex2fv(puntoC);
    glVertex2fv(puntoa);

    glVertex2fv(puntoa);
    glVertex2fv(puntoD);
    glVertex2fv(puntob);

    glVertex2fv(puntob);
    glVertex2fv(puntoE);
    glVertex2fv(puntoc);
    glEnd();
    glFlush();
    glPopMatrix();

}

void keyboard (unsigned char key, int xmouse, int ymouse)
{
    switch (key)
    {
        case 'c':
        {
            x_eye+=0.5;
            break;
        }
        case 'x':
        {
            x_eye-=0.5;
            break;
        }
        case 'y':
        {
            y_eye+=0.5;
            break;
        }
        case 't':
        {
            y_eye-=0.5;
            break;
        }
        case 'z':
        {
            z_eye+=0.5;
            break;
        }
        case 'a':
        {
            z_eye-=0.5;
            break;
        }

        default:
            break;
    }
    glutPostRedisplay();
}

static void creaAlbero(float base, float altezza)
{
    glPushMatrix();


    glTranslated(0.0,1.8,-8);
    glRotated(90,-1.0, 0.0, 0.0);
    glColor3f(0,0.5,0);
    glTranslated(0.0,0.0,-altezza);
    //Disegeno
    glutSolidCone(base,1.5, 50, 50);

    glPopMatrix();

}

static void creaTronco(void)
{
    glPushMatrix();
    glTranslated(0.0,-2,-8);
    glRotated(90, -1.0, 0.0, 0.0);
    glColor3d(0.62,0.41,0.20);

    //Disegno
    GLUquadric *gluQuadric = NULL;
    gluQuadric = gluNewQuadric();
    gluCylinder(gluQuadric,1,0.8,1,50,50);

    glPopMatrix();
}


static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    //Con la tastiera sposto la visuale
    gluLookAt(x_eye,y_eye,z_eye, 0,0,0,0,1,0);
    glEnable(GL_LIGHT0);


    //albero
    float base = 1, altezza=0;
    int i;
    for (i=0;i<5;i++)
    {
        creaAlbero(base,altezza);
        base+=0.3;
        altezza+=0.8;
    }

    creaTronco();
    creaStella();
    glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Christmas Tree");
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glutMainLoop();

    return EXIT_SUCCESS;
}