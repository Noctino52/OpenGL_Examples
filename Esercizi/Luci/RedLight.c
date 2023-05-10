/*
 * Esercizio:
 *  Disegnare due sfere che si intersecano.
 *  Permettere all’ osservatore di ruotare le sfere intorno al centro della scena.
 *  Creare due luci:
 *  – Una luce bianca in prossimità delle sfere e che si muova con le sfere.
 *  – Una luce rossa che rimane coerente alla posizione dell’ osservatore.
 */

#include <GL/gl.h>
#include <GL/glut.h>


float x_eye=0.0, y_eye=0.0, z_eye = 8.0;

float angolo=0.0;

void drawSphere()
{
    glPushMatrix();
    glRotatef(angolo,0.0,1.0,0.0);


    //LUCE BIANCA

    float white[4]={1.0,1.0,1.0,1.0};
    float whitePosition[4]={3,8,8,0};
    glLightfv(GL_LIGHT1,GL_DIFFUSE,&white[0]);
    glLightfv(GL_LIGHT1,GL_POSITION,&whitePosition[0]);

    //Sfera 1
    GLUquadricObj *qobj,*qobj2;
    qobj = gluNewQuadric(); //creazione
    gluQuadricDrawStyle(qobj,GLU_FILL);
    gluQuadricOrientation(qobj,GLU_OUTSIDE);
    gluSphere(qobj,0.90,50,50); //raggio long lat

    //Sfera2
    glTranslatef(1.5,0.0,0.0);
    qobj2 = gluNewQuadric();
    gluQuadricDrawStyle(qobj2,GLU_FILL);
    gluQuadricOrientation(qobj2,GLU_OUTSIDE);
    gluSphere(qobj,0.90,55,50);

    glPopMatrix();
}


void displaySphere()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-1,1,-1,1,3,10);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(x_eye,y_eye,z_eye, 0,0,0,0,1,0);

    glEnable(GL_LIGHTING);

    //LUCE ROSSA
    float red[4]={1,0,0,1};
    float redPosition[4]={0.0,0.0,8.0,0.0};

    glLightfv(GL_LIGHT0,GL_DIFFUSE,&red[0]);
    glLightfv(GL_LIGHT0,GL_POSITION,&redPosition[0]);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    drawSphere();

    glFlush();
}



void keyword (unsigned char key, int xmouse, int ymouse)
{
    switch (key)
    {
        case '+':
        {
            angolo+=5;
            glutPostRedisplay();
            break;
        }
        case '-':
        {
            angolo-=5;
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
    glutCreateWindow("RedLight");
    glutDisplayFunc(displaySphere);
    glutKeyboardFunc(keyword);
    glutMainLoop();
    return 0;
}
