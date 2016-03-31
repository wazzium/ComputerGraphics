#include <GL/glut.h>

GLfloat angleCubeX = 0.0f;
GLfloat angleCubeY = 0.0f;
GLfloat angleSphere = 0.0f;
 
GLint currentWidth=400;
GLint currentHeight=400;
 
int perspective = 0;
 
void reshape(int newWidth, int newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(perspective)
     gluPerspective(60.0f, (GLfloat)newWidth/(GLfloat)newHeight, 1.0f, 20.0f);
    else

      glOrtho(-4,4, -4, 4, 1, 10);

    glMatrixMode(GL_MODELVIEW);
 
    currentWidth = newWidth;
    currentHeight = newHeight;
}
 
void drawCube(void)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);       //cara frontal
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);       //cara trasera
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);       //cara lateral izq
    glVertex3f(-1.0f,-1.0f, -1.0f);
    glVertex3f(-1.0f,-1.0f,  1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);       //cara lateral dcha
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glEnd(); 
    glColor3f(0.0f,      1.0f, 1.0f);
    glBegin(GL_QUADS);       //cara arriba
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
 
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);       //cara abajo
    glVertex3f( 1.0f,-1.0f, -1.0f);
    glVertex3f( 1.0f,-1.0f,  1.0f);
    glVertex3f(-1.0f,-1.0f,  1.0f);
    glVertex3f(-1.0f,-1.0f, -1.0f);
    glEnd();
}

void dibuixa()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glLoadIdentity();
 
    glTranslatef(0.0f, 0.0f, -5.0f);
 
    glRotatef(angleCubeX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleCubeY, 0.0f, 1.0f, 0.0f);
 
    drawCube();
 
    glLoadIdentity();
 
    glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(angleSphere, 0.0f, 1.0f, 0.0f);
    glTranslatef(3.0f, 0.0f, 0.0f);
 
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireSphere(0.5f, 8, 8);
 
    glutSwapBuffers();
 
	angleCubeX+=0.1f;
    angleCubeY+=0.1f;
    angleSphere+=0.2f;
}

void idle()
{
    dibuixa();
}
 
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'p':
    case 'P':
      perspective=1;
      reshape(currentWidth,currentHeight);
      break;
 
    case 'o':
    case 'O':
      perspective=0;
	  reshape(currentWidth,currentHeight);
      break;
 
    case 27:   // escape
      exit(0);
      break;
    }
}

void init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
	glutInitWindowSize(currentWidth, currentHeight);
    glutCreateWindow("Cub i esfera");
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}
  
int main(int argc, char **argv) {
		//Inicialització de context OpenGL
	glutInit(&argc, argv); 
    init();
		//Programació de CallBacks
    glutDisplayFunc(dibuixa);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}