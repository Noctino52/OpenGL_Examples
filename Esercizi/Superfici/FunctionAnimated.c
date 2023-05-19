#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265


float k =0;

typedef struct Vertex
{
    float x,y,z;

}Vertex;

float x_eye=0, y_eye=0, z_eye = 0.2;

float function(float x , float z)
{
    float  w = sqrt(pow(x,2)+pow(z,2));
    float  a = k * (PI/32);
    return  (2 * sin(w-a))/(w-a);
}

void CalculateVertex(Vertex vertex[], float x , float z)
{
    vertex[0].x=x;
    vertex[0].y=function(x,z);
    vertex[0].z=z;

    vertex[3].x=x+0.25;
    vertex[3].y =function(x+0.25,z);
    vertex[3].z=z;

    vertex[2].x=x+0.25;
    vertex[2].y=function(x+0.25,z+0.25);
    vertex[2].z=z+0.25;

    vertex[1].x=x;
    vertex[1].y=function(x,z+0.25);
    vertex[1].z=z+0.25;

}
void check_cap() {
    if(z_eye>2)z_eye=2;
    else if(z_eye<-2)z_eye=-2;
    if(x_eye>10)x_eye=10;
    else if(x_eye<-10)x_eye=-10;
    if(y_eye>10)y_eye=10;
    else if (y_eye<-10)y_eye=-10;
    printf("x:%f y:%f z:%f \n",x_eye,y_eye,z_eye);
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

Vertex Newell(Vertex vertex[])
{
    Vertex normal;
    normal.x = 0.0;
    normal.y = 0.0;
    normal.z = 0.0;
    int numVertices = 4;

    for (int i = 0; i < numVertices; i++) {
        int next = (i + 1) % numVertices;
        normal.x += (vertex[i].y - vertex[next].y) * (vertex[i].z + vertex[next].z);
        normal.y += (vertex[i].z - vertex[next].z) * (vertex[i].x + vertex[next].x);
        normal.z += (vertex[i].x - vertex[next].x) * (vertex[i].y + vertex[next].y);
    }
    // Normalizzazione della normale
    float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length != 0.0) {
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;
    }

    return normal;
}

void drawSquare(float x , float z)
{
    glPushMatrix();
    Vertex vertici[4];
    CalculateVertex(vertici,x,z);
    Vertex norm = Newell(vertici);
    int i,next;
    glBegin(GL_POLYGON);
    glNormal3f(norm.x,norm.y,norm.z);
    for(i=0;i<4;i++)
    {
        glVertex3f(vertici[i].x,vertici[i].y,vertici[i].z);
    }

    glEnd();
    glPopMatrix();

}
void redraw()
{
    glClearColor(0.0, 0.3, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10, 10, -10, 10, 4, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x_eye, y_eye, z_eye, 0, 0, 0, 0, 1, 0);
    check_cap();

    // Configurazione illuminazione
    //GLfloat light_position[] = {0, 5, 0, 1}; // Posizione della luce
    //GLfloat light_color[] = {2.0f, 2.0f, 2.0f, 1.0f}; // Colore della luce
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glTranslatef(0.0,0.2,-7);
    glRotatef(80,1,0,0);
    float x = -10, z = -10;
    while (z < 10)
    {
        while (x < 10)
        {
            drawSquare(x, z);
            x = x + 0.25;
        }
        x = -10;
        z = z + 0.25;
    }

    glutSwapBuffers();
    glFlush();
}
void increaseK()
{
    k=k+0.1;
    glutPostRedisplay();
    glutTimerFunc(32,increaseK,0);

}


int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("Function Animated");
    glutDisplayFunc(redraw);
    glutKeyboardFunc(keyword);
    glutTimerFunc(32,increaseK,0);
    glutMainLoop();
    return 0;

}
