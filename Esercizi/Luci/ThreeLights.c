/*
 * Esercizio:
 * Utilizzando una superficie di un esercizio precedente, creare:
 * Tre luci che si possano accendere alternativamente di tre colori diversi.
 * Una luce ambientale persistente anche con le luci spente
 * L’illuminazione anche delle facce posteriori
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

GLfloat ctrlpoints[4][4][3] ={{{0,0,0},{1,0,.5},{2,0,1},{3,0,0}},
{{0,1,0.5},{1,1,2},{2,1,2.5},{3,1,0.5}},
{{0,2,1},{1,2,2.5},{2,2,2.5},{3,2,1}},
{{0,3,0},{1,3,0.5},{2,3,1},{3,3,0}}};


char premuto;

void display (void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-2,2,-2,2,2,10);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0,0,6, 0,0,0,0,1,0);
    glRotatef(40,0,0,1);
    glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,0,1,12,4,&ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(30, 0.0, 1.0, 8,0.0,1.0);
    glEvalMesh2(GL_FILL, 0, 30,0,8);
    glEnable(GL_LIGHTING);
    //LUCE ROSSA
    float red[4]={1,0,0,1};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,&red[0]);

    //LUCE BLU
    float blue[4]={0,0,1,1};
    glLightfv(GL_LIGHT1,GL_DIFFUSE,&blue[0]);

    //LUCE VERDE
    float green[4]={0,1,0,1};
    glLightfv(GL_LIGHT2,GL_DIFFUSE,&green[0]);


    //LUCE AMBIENTALE PERSISTENTE
    float ambiente[4]={0.7,0,0.4,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&ambiente[0]);


    glFlush();

}


void keyword (unsigned char key, int xmouse, int ymouse)
{
    switch (key)
    {
        case 'r':
        {
            premuto='r';
            break;
        }
        case 'g':
        {
            premuto='g';
            break;
        }
        case 'b':
        {
            premuto='b';
            break;
        }
        case '+':
        {
            if(premuto=='r')
                glEnable(GL_LIGHT0);
            else if(premuto=='b')
                glEnable(GL_LIGHT1);
            else if(premuto=='g')
                glEnable(GL_LIGHT2);
            glutPostRedisplay();
            break;
        }
        case'-':
        {
            if(premuto=='r')
                glDisable(GL_LIGHT0);
            else if(premuto=='b')
                glDisable(GL_LIGHT1);
            else if(premuto=='g')
                glDisable(GL_LIGHT2);
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
    glutCreateWindow("Surface light");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyword);
    glutMainLoop();
    return 0;
}
