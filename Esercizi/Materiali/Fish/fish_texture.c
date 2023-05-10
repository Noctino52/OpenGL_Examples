#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265
#include "texture.c"

float incrementox=0.0;
float incrementoangolo=0.0;

float x_eye=0.0, y_eye=0.0, z_eye = 5.0;
static GLuint texnames[2];

GLvoid initTexture(unsigned *image,unsigned *image_spec, GLsizei imageWidth, GLsizei imageHeight)
{
	
	GLsizei sWidth = 256, sHeight=256;
    glGenTextures(2, texnames);
    glBindTexture(GL_TEXTURE_2D, texnames[0]);
	glTexParameterf( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned *simage;
	simage = (unsigned*)malloc(sWidth*sHeight*4*sizeof(unsigned));
	gluScaleImage(GL_RGBA,imageWidth,imageHeight,GL_UNSIGNED_BYTE,image,sWidth,sHeight,GL_UNSIGNED_BYTE,simage);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,sWidth,sHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,simage);


    glBindTexture(GL_TEXTURE_2D, texnames[1]);
    glTexParameterf( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned *simage_spec;
    simage_spec = (unsigned*)malloc(sWidth*sHeight*4*sizeof(unsigned));
    gluScaleImage(GL_RGBA,imageWidth,imageHeight,GL_UNSIGNED_BYTE,image_spec,sWidth,sHeight,GL_UNSIGNED_BYTE,simage_spec);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,sWidth,sHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,simage_spec);
    glEnable(GL_TEXTURE_2D);
}


void drawScene(void)
{

	float v0[3]= {-1.5,-1.0,0.0};
	float v1[3]= {1.5,-1.0,0.0};
	float v2[3]= {1.5,1.0,0.0};
	float v3[3]= {-1.5,1.0,0.0};
	
	
	float t0[2]= {0.0,0.0};
	float t1[2]= {1.0,0.0};
	float t2[2]= {1.0,1.0};
	float t3[2]= {0.0,1.0};

	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  	glEnable(GL_DEPTH_TEST);
  	glMatrixMode( GL_PROJECTION );
  	glLoadIdentity();
  	glFrustum(-2,7,-2,2,3,20);
  	glMatrixMode( GL_MODELVIEW );
  	glLoadIdentity();
  	gluLookAt(x_eye,y_eye,z_eye, 0,0,0,0,1,0);
	
	glColor3f(1.0,1.0,1.0);

	glTranslatef(sin(incrementox),sin(incrementox),0);
	glRotatef(sin((incrementoangolo*PI)/180)*30,0,1,0);

	//Primo pesce
    glBindTexture(GL_TEXTURE_2D, texnames[0]);
	glBegin(GL_QUADS);
		glTexCoord2fv(t0);glVertex3fv(v0);
		glTexCoord2fv(t1);glVertex3fv(v1);
		glTexCoord2fv(t2);glVertex3fv(v2);
		glTexCoord2fv(t3);glVertex3fv(v3);
	glEnd();

    glTranslatef(4,0,0);
    glBindTexture(GL_TEXTURE_2D, texnames[1]);
    glBegin(GL_QUADS);
    glTexCoord2fv(t0);glVertex3fv(v0);
    glTexCoord2fv(t1);glVertex3fv(v1);
    glTexCoord2fv(t2);glVertex3fv(v2);
    glTexCoord2fv(t3);glVertex3fv(v3);
    glEnd();

	glutSwapBuffers();
	
}

void increase()
{
	
	incrementox+=0.05;
	incrementoangolo+=10;
	glutPostRedisplay();
	glutTimerFunc(100,increase,0);
}

int main(int argc, char *argv[])
{
	char * imageFileName="C:\\Users\\ivan_\\CLionProjects\\ComputerGraphics\\Esercizi\\Materiali\\Fish\\fish.rgba";
    char * imageFileNameSpec="C:\\Users\\ivan_\\CLionProjects\\ComputerGraphics\\Esercizi\\Materiali\\Fish\\fisha.rgba";
	unsigned *image,*image_spec;
	long width=640, height=480;
	int imageWidth,imageHeight, components;
	glutInit(&argc,argv);
	image = read_texture(imageFileName,&imageWidth,&imageHeight,&components);
	image_spec=read_texture(imageFileNameSpec,&imageWidth,&imageHeight,&components);

	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	
	initTexture(image,image_spec,imageWidth,imageHeight);

	glutTimerFunc(100,increase,0);
	glutDisplayFunc(drawScene);
	glutMainLoop();
	
}

