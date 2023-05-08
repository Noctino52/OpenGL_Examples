/* ESERCIZIO:
#Modellare una casetta senza finestre utilizzando una struttura dati per Mesh Poligonali e attivando la luce di default
#Visualizzare i vettori normali applicati ad ogni vertice e per ogni faccia
#Con l’utilizzo di gluLookAt, permettere all’osservatore di girare intorno alla casetta
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265

float left =-1;
float right =1;
float top = 1;
float bottom = -1;
float nearclip =1 ;
float farclip =5;

typedef struct Vertex
{
    float x;
    float y;
    float z;
}Vertex;


typedef struct Face
{
    int numVert;
    int ** matrice;
}Face;

typedef struct Mesh
{
    int numVerts;
    Vertex  *vertici;
    int numNorms;
    Vertex  * norm;
    int numFaces;
    Face *face;
}Mesh;


Mesh casetta;
float *polx,*poly;

void InitMesh()
{
    casetta.numVerts=10;
    casetta.vertici = (Vertex*)malloc(casetta.numVerts*sizeof(Vertex));
    casetta.numNorms=7;
    casetta.norm = (Vertex*)malloc(casetta.numNorms*sizeof(Vertex));
    casetta.numFaces=7;
    casetta.face= (Face*)malloc(casetta.numFaces*sizeof(Face));
    int i,j;
    for (i=0;i<casetta.numFaces;i++)
    {
        if(i==0 || i==1)
        {
            casetta.face[i].numVert=5;
        }
        else
        {
            casetta.face[i].numVert=4;
        }
        casetta.face[i].matrice=(int **)malloc(casetta.face[i].numVert*sizeof(int*));
        for(j=0;j<casetta.face[i].numVert;j++)
        {
            casetta.face[i].matrice[j]=(int*)malloc(2*sizeof(int));
        }

    }
}

void LoadCordinate()
{
    polx=(float*)malloc(sizeof(float*)*casetta.face[0].numVert);
    poly=(float*)malloc(sizeof(float*)*casetta.face[0].numVert);
    int step =1;
    float incremento = 360/(float)5;
    float attuale = incremento;
    while (step <= 5)
    {
        polx[step-1] = cos((attuale*PI)/180)*0.5;
        poly[step-1] = sin((attuale*PI)/180)*0.5;
        attuale=attuale+incremento;
        step++;
    }
}



Vertex Newell(int i)
{
    Vertex result;
    int k,somma=0,indice_attuale,indice_successivo;
    for (k=0;k<casetta.face[i].numVert-1;k++)
    {
        indice_attuale = casetta.face[i].matrice[k][0];
        indice_successivo = casetta.face[i].matrice[(k+1)%casetta.face[i].numVert][0];
        somma = somma + (( casetta.vertici[indice_attuale].y - casetta.vertici[indice_successivo].y)*(casetta.vertici[indice_attuale].z + casetta.vertici[indice_successivo].z) );
    }
    result.x = somma ;
    somma =0 ;
    for (k=0;k<casetta.face[i].numVert-1;k++)
    {
        indice_attuale = casetta.face[i].matrice[k][0];
        indice_successivo = casetta.face[i].matrice[(k+1)%casetta.face[i].numVert][0];
        somma = somma + (( casetta.vertici[indice_attuale].z - casetta.vertici[indice_successivo].z)*(casetta.vertici[indice_attuale].x + casetta.vertici[indice_successivo].x) );
    }
    result.y=somma;
    somma=0;
    for (k=0;k<casetta.face[i].numVert-1;k++)
    {
        indice_attuale = casetta.face[i].matrice[k][0];
        indice_successivo = casetta.face[i].matrice[(k+1)%casetta.face[i].numVert][0];
        somma = somma + (( casetta.vertici[indice_attuale].x - casetta.vertici[indice_successivo].x)*(casetta.vertici[indice_attuale].y + casetta.vertici[indice_successivo].y) );
    }
    result.z=somma;
    return result;
}





void LoadMesh()
{
    LoadCordinate();
    int i,j;
    for(i=0;i<casetta.numVerts/2;i++)
    {

        casetta.vertici[i].x=polx[i];
        casetta.vertici[i].y= poly[i];
        casetta.vertici[i].z=-0.5;
        //printf("vertice[%d] %f %f %f \n",i,polx[i],poly[i],-0.5);
        casetta.vertici[i+casetta.numVerts/2].x=polx[i];
        casetta.vertici[i+casetta.numVerts/2].y=poly[i];
        casetta.vertici[i+casetta.numVerts/2].z=-1.5;
        //printf("vertice[%d] %f %f %f \n",i+casetta.numVerts/2,polx[i],poly[i],-1.5);
    }


    //riempio face
    //face [0]
    casetta.face[0].matrice[0][0]=0;
    casetta.face[0].matrice[1][0]=1;
    casetta.face[0].matrice[2][0]=2;
    casetta.face[0].matrice[3][0]=3;
    casetta.face[0].matrice[4][0]=4;
    //face [1]
    casetta.face[1].matrice[0][0]=5;
    casetta.face[1].matrice[1][0]=6;
    casetta.face[1].matrice[2][0]=7;
    casetta.face[1].matrice[3][0]=8;
    casetta.face[1].matrice[4][0]=9;
    //face [2]
    casetta.face[2].matrice[0][0]=0;
    casetta.face[2].matrice[1][0]=5;
    casetta.face[2].matrice[2][0]=9;
    casetta.face[2].matrice[3][0]=4;
    //face [3]
    casetta.face[3].matrice[0][0]=4;
    casetta.face[3].matrice[1][0]=9;
    casetta.face[3].matrice[2][0]=8;
    casetta.face[3].matrice[3][0]=3;
    //face [4]
    casetta.face[4].matrice[0][0]=3;
    casetta.face[4].matrice[1][0]=8;
    casetta.face[4].matrice[2][0]=7;
    casetta.face[4].matrice[3][0]=2;
    //face [5]
    casetta.face[5].matrice[0][0]=1;
    casetta.face[5].matrice[1][0]=6;
    casetta.face[5].matrice[2][0]=7;
    casetta.face[5].matrice[3][0]=2;
    //face [6]
    casetta.face[6].matrice[0][0]=0;
    casetta.face[6].matrice[1][0]=5;
    casetta.face[6].matrice[2][0]=6;
    casetta.face[6].matrice[3][0]=1;

    //calcolo coordinate normalizate per le facce
    for (i=0;i<casetta.numNorms;i++)
    {
        casetta.norm[i]= Newell(i);
    }

}

void drawFace(int i)
{
    int k;
    glPushMatrix();
    glBegin(GL_POLYGON);

    if(i==0)glColor3f(0.64,0,0);
    if(i==1)glColor3f(1,0.2,0.2);
    else if (i==2)glColor3f(0.85,0.58,0);
    else  if(i==3) glColor3f(0.59,0.36,0.1);
    else if(i==4)glColor3f(0.50,0.71,0.2);
    else if(i==5)glColor3f(0,0.71,0.6);
    else if(i==6)glColor3f(0.85,0,1);
    else if(i==7)glColor3f(0,0,1);
    else if(i==8) glColor3f(0.25,0.21,0.8);
    else if(i==9) glColor3f(1,1,0);

    glNormal3f(casetta.norm[i].x,casetta.norm[i].y,casetta.norm[i].z);

    for(k=0;k<casetta.face[i].numVert;k++)
    {
        Vertex vertice = casetta.vertici[casetta.face[i].matrice[k][0]];
        glVertex3f(vertice.x,vertice.y,vertice.z);
    }
    glEnd();
    glPopMatrix();

}


//Keyboard callback
float height=0.1;
float width=0.1;
float depth=0.6;

void check_cap(){
    //CAP sui valori massimali/minimali (l'immaggine diverebbe troppo distorta senza)
    if(width>=1.5)width=1.5;
    else if(width<=-0.5)width=-0.5;
    if(height>=1.5)height=1.5;
    else if(height<-0.5)height=-0.5;
    if(depth<=-3)depth=-3;
    if(depth>=3)depth=3;

    printf("=============== \n");
    printf("width = %f\n", width);
    printf("height = %f\n", height);
    printf("depth = %f\n", depth);
}
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
    check_cap();

    glutPostRedisplay();
}

void redraw()
{

    glClearColor(0.0,0.3,0.0,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(left,right,bottom,top,nearclip,farclip);
    glMatrixMode( GL_MODELVIEW );
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glShadeModel(GL_FLAT);
    glLoadIdentity();
    gluLookAt(width,height,depth, 0,0,-1, 0,1,0);
    glRotatef(90,0,0,1);
    int i;
    for(i=0;i<casetta.numFaces;i++)
    {
        // disegna faccia
        drawFace(i);
    }

    glFlush();
}


void stampaInfoMesh()
{

    printf("NUMERO VERTICI : %d \n",casetta.numVerts);
    printf("NUMERO NORMS: %d \n",casetta.numNorms);
    printf("NUMERO FACCE %d \n",casetta.numFaces);
    int i;
    printf("\n VERTICI \n");
    for (i=0;i<casetta.numVerts;i++)
    {
        printf("VERTICE[%d] X: %f Y :%f Z:%f \n",i,casetta.vertici[i].x,casetta.vertici[i].y,casetta.vertici[i].z);
    }

    printf("\nNORMS\n");
    for(i=0;i<casetta.numNorms;i++)
    {
        printf("FACCIA [%d] MX: %f MY:%f MZ:%f \n",i,casetta.norm[i].x,casetta.norm[i].y,casetta.norm[i].z);
    }

    printf("\nFACCE\n");
    int k,z;
    for (i=0;i<casetta.numFaces;i++)
    {
        printf("FACCIA [%d] HA %d VERTICI\n",i,casetta.face[i].numVert);
        for(k=0;k<casetta.face[i].numVert;k++)
        {
            for(z=0;z<2;z++)
            {
                printf("[%d,%d]: %d ",k,z,casetta.face[i].matrice[k][z]);
            }
            printf("\n");
        }

    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mesh Poligonale");
    InitMesh();
    LoadMesh();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(redraw);
    glutMainLoop();


    return 0;
}