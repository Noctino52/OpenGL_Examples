#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

typedef struct Vertex
{
    float x,y,z;

}Vertex;

float function(float x , float z)
{
    float result = (2 * sin (sqrt(pow(x,2)+pow(z,2))))/(sqrt(pow(x,2)+pow(z,2)));
    return result;
}

float x_eye=0, y_eye=3, z_eye = 0.2;
float incremento=0.2;

void CalculateVertex(Vertex vertex[], float x , float z)
{
    vertex[0].x=x;
    vertex[0].y=function(x,z);
    vertex[0].z=z;

    vertex[3].x=x+incremento;
    vertex[3].y =function(x+incremento,z);
    vertex[3].z=z;

    vertex[2].x=x+incremento;
    vertex[2].y=function(x+incremento,z+incremento);
    vertex[2].z=z+incremento;

    vertex[1].x=x;
    vertex[1].y=function(x,z+incremento);
    vertex[1].z=z+incremento;

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
    Vertex vertici[4];
    CalculateVertex(vertici,x,z);
    Vertex norm = Newell(vertici);
    glBegin(GL_POLYGON);
    glNormal3f(norm.x,norm.y,norm.z);
    for(int i=0;i<4;i++)
    {
        glVertex3f(vertici[i].x,vertici[i].y,vertici[i].z);
    }
    glEnd();

}

void redraw()
{
    glClearColor(0.0, 0.3, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10, 10, -10, 10, 1, 10);

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

    float x = -10, z = -10;
    while (z < 10)
    {
        while (x < 10)
        {
            drawSquare(x, z);
            x = x + incremento;
        }
        x = -10;
        z = z + incremento;
    }

    glutSwapBuffers();
    glFlush();
}


int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Function");
    glutDisplayFunc(redraw);
    glutKeyboardFunc(keyword);
    glutMainLoop();
    return 0;

}
