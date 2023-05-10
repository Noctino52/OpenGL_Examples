/*
 * Esercizio:
 * Disegnare una sfera rossa lucida, un cono blu matto ed un toro giallo fosforescente.(glutSolidSphere, glutSolidCone, glutSolidTorus)
 * Creare due luci: una vicino alla sfera rossa e l’altra vicino al cono blu.
 * Permettere all’ osservatore di ruotare gli oggetti intorno al centro della scena.
 */

#include <GL/gl.h>
#include <GL/glut.h>

float angolo=0.0;
float x_eye=0.0, y_eye=0.0, z_eye = 8.0;

int spec=0;

void drawSphere()
{
    glPushMatrix();
    glRotatef(angolo,0,1,0);


    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
    glColor3f(1,0,0);
    glutSolidSphere(0.90,50,50); //raggio long lat

    glPopMatrix();
}

void drawCone()
{
    glPushMatrix();
    glRotatef(angolo,0.0,0.0,1.0);
    glTranslatef(2.5,0,0);
    float black[4]={0,0,0,1};

    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&black[0]);
    glColor3f(0,0,1);
    glutSolidCone(1,3,50,50); //raggio long lat

    glPopMatrix();
}


void drawTorus()
{
    glPushMatrix();
    glRotatef(angolo,0.0,0.0,1.0);
    glTranslatef(-2.5,0,0);
    float black[4]={0,0,0,1};
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,0);  // Imposta la brillantezza del materiale a 0
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&black[0]);  // Imposta il colore speculare del materiale a nero
    glColor3f(1,1,0);
    glutSolidTorus(0.4,0.8,50,50); //raggio long lat

    glPopMatrix();

}

void display()
{
    glClearColor(0,0.0,0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-2,2,-2,2,2,10);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(x_eye,y_eye,z_eye, 0,0,0,0,1,0);
    glEnable(GL_LIGHTING);

    //2 LUCI BIANCHE, SI SELEZIONA UNA INVECE CHE UN'ALTRA PREMENDO SPAZIO
    //Cambia solo la posizione
    float light_position[2][4]= {{0,0,8,0},{2.5,0,8,0}};
    float white[4]={1,1,1,1};
    glLightfv(GL_LIGHT1,GL_DIFFUSE,&white[0]);
    glLightfv(GL_LIGHT1,GL_POSITION,&light_position[spec][0]);

    glLightfv(GL_LIGHT2,GL_DIFFUSE,&white[0]);
    glLightfv(GL_LIGHT2,GL_POSITION,&light_position[spec][0]);

    if(spec)glEnable(GL_LIGHT1);
    else glEnable(GL_LIGHT2);


    drawSphere();
    drawCone();
    drawTorus();

    if(spec)glDisable(GL_LIGHT1);
    else glDisable(GL_LIGHT2);
    glFlush();
}


void keyword (unsigned char key, int xmouse, int ymouse)
{
    switch (key)
    {
        case '+':
        {
            angolo+=5;
            break;
        }
        case '-':
        {
            angolo-=5;
            break;
        }
        case' ':
        {
            spec=(spec+1)%2;
            break;
        }

        default:
            break;

    }
    glutPostRedisplay();

}

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Material_Solid");
    glutDisplayFunc(display);
    //COMANDI: Spazio=cambio luce
    glutKeyboardFunc(keyword);
    glutMainLoop();
    return 0;
}
