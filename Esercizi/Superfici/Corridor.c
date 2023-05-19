#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Dimensioni del corridoio
#define CORRIDOR_WIDTH 10.0
#define CORRIDOR_HEIGHT 10.0
#define CORRIDOR_LENGTH 300.0

typedef struct Vertex
{
    float x,y,z;

}Vertex;

// Posizione dell'osservatore
float observerX = 5.0;
float observerY = 0.0;
float observerZ = 15.0;
float rotationAngle = 90.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Colore di sfondo (nero)
    glEnable(GL_DEPTH_TEST);           // Abilita il depth testing

    GLfloat lightPosition[] = {-9, 2.0, -9.0, 1};
    GLfloat lightDiffuse[] = {0.6, 0.6, 0.6, 1};   // Diffuse color of the light (yellow)
    GLfloat lightSpecular[] = {1, 1, 1, 1.0};  // Specular color of the light (no specular highlight)


    glLightfv(GL_LIGHT3, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, lightSpecular);




    GLfloat lightPosition2[] = {9, 2.0, -9.0, 1};
    GLfloat lightDiffuse2[] = {0.6, 0.6, 0.6, 1};   // Diffuse color of the light (yellow)
    GLfloat lightSpecular2[] = {1, 1, 1, 1.0};  // Specular color of the light (no specular highlight)


    glLightfv(GL_LIGHT4, GL_POSITION, lightPosition2);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, lightDiffuse2);
    glLightfv(GL_LIGHT4, GL_SPECULAR, lightSpecular2);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_FLAT);
    glEnable(GL_NORMALIZE);
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

void drawCorridor(){
    // Disegna il corridoio
    Vertex norm;
    for (float x = 0.0; x < CORRIDOR_LENGTH; x += CORRIDOR_WIDTH) {
        for (float z = 0.0; z < CORRIDOR_WIDTH; z += CORRIDOR_WIDTH) {
            glBegin(GL_QUADS);
            // Soffitto bianco

            glColor3f(1.0, 1.0, 1.0);
            Vertex soffitto[4]={{x, CORRIDOR_HEIGHT, z},
                              {x + CORRIDOR_WIDTH, CORRIDOR_HEIGHT, z},
                              {x + CORRIDOR_WIDTH, CORRIDOR_HEIGHT, z + CORRIDOR_WIDTH},
                              {x, CORRIDOR_HEIGHT, z + CORRIDOR_WIDTH}
            };
            norm= Newell(soffitto);
            glNormal3f(norm.x,norm.y,norm.z);
            glVertex3f(soffitto[0].x,soffitto[0].y,soffitto[0].z);
            glVertex3f(soffitto[1].x,soffitto[1].y,soffitto[1].z);
            glVertex3f(soffitto[2].x,soffitto[2].y,soffitto[2].z);
            glVertex3f(soffitto[3].x,soffitto[3].y,soffitto[3].z);

            // Pareti beige
            glColor3f(0.8, 0.8, 0.6);
            Vertex parete[4]={{x,-CORRIDOR_HEIGHT,z},
                              {x + CORRIDOR_WIDTH, -CORRIDOR_HEIGHT, z},
                              {x + CORRIDOR_WIDTH, CORRIDOR_HEIGHT, z},
                              {x, CORRIDOR_HEIGHT, z}};
            norm= Newell(parete);
            glNormal3f(norm.x,norm.y,norm.z);
            glVertex3f(parete[0].x,parete[0].y,parete[0].z);
            glVertex3f(parete[1].x,parete[1].y,parete[1].z);
            glVertex3f(parete[2].x,parete[2].y,parete[2].z);
            glVertex3f(parete[3].x,parete[3].y,parete[3].z);



            glColor3f(0.8, 0.8, 0.6);
            Vertex parete2[4]={
                    {x,-CORRIDOR_HEIGHT,z+CORRIDOR_WIDTH},
                    {x, CORRIDOR_HEIGHT, z+CORRIDOR_WIDTH},
                    {x + CORRIDOR_WIDTH, CORRIDOR_HEIGHT, z+CORRIDOR_WIDTH},
                    {x + CORRIDOR_WIDTH, -CORRIDOR_HEIGHT, z+CORRIDOR_WIDTH},
                    };

            norm= Newell(parete2);
            glNormal3f(norm.x,norm.y,norm.z);
            glVertex3f(parete2[0].x,parete2[0].y,parete2[0].z);
            glVertex3f(parete2[1].x,parete2[1].y,parete2[1].z);
            glVertex3f(parete2[2].x,parete2[2].y,parete2[2].z);
            glVertex3f(parete2[3].x,parete2[3].y,parete2[3].z);

            //Muro1
            if(x==CORRIDOR_LENGTH-10){
                glColor3f(1, 0, 0);
                Vertex muro1[4]={{x+CORRIDOR_WIDTH,-CORRIDOR_HEIGHT,z},
                                 {x + CORRIDOR_WIDTH, +CORRIDOR_HEIGHT, z},
                                 {x + CORRIDOR_WIDTH, CORRIDOR_HEIGHT, z+CORRIDOR_WIDTH},
                                 {x+ CORRIDOR_WIDTH, -CORRIDOR_HEIGHT, z+CORRIDOR_WIDTH}};
                norm= Newell(muro1);
                glNormal3f(norm.x,norm.y,norm.z);
                glVertex3f(muro1[0].x,muro1[0].y,muro1[0].z);
                glVertex3f(muro1[1].x,muro1[1].y,muro1[1].z);
                glVertex3f(muro1[2].x,muro1[2].y,muro1[2].z);
                glVertex3f(muro1[3].x,muro1[3].y,muro1[3].z);
            }

            if(x==0){
                glColor3f(1, 0, 0);
                Vertex muro2[4]={{x,-CORRIDOR_HEIGHT,z},
                                 {x , +CORRIDOR_HEIGHT, z},
                                 {x, CORRIDOR_HEIGHT, z+CORRIDOR_WIDTH},
                                 {x, -CORRIDOR_HEIGHT, z+CORRIDOR_WIDTH}};
                norm= Newell(muro2);
                glNormal3f(norm.x,norm.y,norm.z);
                glVertex3f(muro2[0].x,muro2[0].y,muro2[0].z);
                glVertex3f(muro2[1].x,muro2[1].y,muro2[1].z);
                glVertex3f(muro2[2].x,muro2[2].y,muro2[2].z);
                glVertex3f(muro2[3].x,muro2[3].y,muro2[3].z);
            }


            // Pavimento blu lucido
            glColor3f(0.0, 0.0, 1.0);
            Vertex pavimento[4]={{x, -CORRIDOR_HEIGHT, z},
                                {x + CORRIDOR_WIDTH, -CORRIDOR_HEIGHT, z},
                                {x + CORRIDOR_WIDTH, -CORRIDOR_HEIGHT, z + CORRIDOR_WIDTH},
                                {x, -CORRIDOR_HEIGHT, z + CORRIDOR_WIDTH}};
            norm= Newell(pavimento);
            glNormal3f(norm.x,norm.y,norm.z);
            glVertex3f(pavimento[0].x,pavimento[0].y,pavimento[0].z);
            glVertex3f(pavimento[1].x,pavimento[1].y,pavimento[1].z);
            glVertex3f(pavimento[2].x,pavimento[2].y,pavimento[2].z);
            glVertex3f(pavimento[3].x,pavimento[3].y,pavimento[3].z);
            glEnd();

            // Applique sulle pareti
            if(x!=0) {
                glPushMatrix();
                glTranslatef(x, 2.0, z);
                glColor3f(1.0, 1.0, 0.0);  // Colore applique
                glutSolidSphere(1, 10, 10);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(x, 2.0, z + 10);
                glColor3f(1.0, 1.0, 0.0);  // Colore applique
                glutSolidSphere(1, 10, 10);
                glPopMatrix();
            }

        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 100.0);  // Prospettiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Posiziona l'osservatore
    gluLookAt(observerX, observerY, observerZ, observerX, observerY, observerZ - 1.0, 0.0, 1.0, 0.0);
    // Applica la rotazione della visuale
    glRotatef(rotationAngle, 0.0, 1.0, 0.0);

    drawCorridor();

    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    // Gestisci l'input da tastiera
    switch (key) {
        case 'w':
            observerZ += 0.6;
            break;
        case 's':
            observerZ -= 0.6;
            break;
        case 'a':
            observerX -= 0.6;
            break;
        case 'd':
            observerX += 0.6;
            break;
        case 'q':
            rotationAngle -= 5.0;
            break;
        case 'e':
            rotationAngle += 5.0;
            break;
    }
    if(rotationAngle>360) rotationAngle=0;
    if(rotationAngle<0) rotationAngle=360;
    printf("x:%f z:%f angolo:%f \n",observerX,observerZ,rotationAngle);

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Corridoio 3D");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}