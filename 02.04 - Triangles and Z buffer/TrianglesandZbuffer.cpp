#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h> 		//Llibreria OpenGL
#define WIDTH 500		//Constants sobre la finestra
#define HEIGHT 500 
#define WINDOWS_X_POSITION 100 
#define WINDOWS_Y_POSITION 100



void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 0, 5);
    glMatrixMode(GL_MODELVIEW);
}
 
void display()
{
		// Restauraci� del frame buffer de color i de profunditat
		// Obligat per un correcte funcionament del proc�s de render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Dibuixem el primer triangle
	glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
      glVertex3f(4,0,3);
      glVertex3f(0,2,3);
      glVertex3f(0,-2,3);
    glEnd();	
		// Dibuixem el segon triangle
	glColor3f(0,0,1);
    glBegin(GL_TRIANGLES);
      glVertex3f(3,0,2);
      glVertex3f(0,3,2);
      glVertex3f(0,-3,2);
    glEnd();

    	//For�a l'intercanvi dels dos buffers i, per tant, no cal fer glFlush() com abans
	glutSwapBuffers();
}
 
/* 
* Inicialitza el sistema: Configuraci� de Glut, Finestra, Projecci� i C�mera
*/ 
void inicialitzacio()
{
	// Inici de la configuraci� del context OpenGL
		// Activem el doble buffer, colors RGB i el z-buffer per permetre diferenciar entre profunditat
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		// Definim una finestra de mides WIDTH per HEIGHT com finestra de visualitzaci� 
	glutInitWindowPosition(WINDOWS_X_POSITION, WINDOWS_Y_POSITION);
	    // Posicionem el costat superior esquerra de la finestra a les coordenades
	glutInitWindowSize(WIDTH, HEIGHT);
	    // Es crea la finestra i se li assigna un t�tol
	glutCreateWindow("Triangles en profunditat");
		//Activa el z-buffer, nom�s pinta els de davant m�s propers a la c�mera
	glEnable(GL_DEPTH_TEST);

	// Ja tenim el context creat, ara activem la matriu de projecci�, nom�s cal un cop
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 0, 10);
	//gluPerspective(60,WIDTH/HEIGHT,7,12);

		// Activem la matriu de visualitzaci�
	glMatrixMode(GL_MODELVIEW);
		// Inicialitzem amb la matriu identitat. 
	glLoadIdentity();
		// Ubiquem la c�mera
	gluLookAt(0,0,10,0,0,0,0,1,0);
		// Establim el color de totes aquelles �rees on no dibuixem, �s a dir, el color de fons
	glClearColor(0,0,0,0);
		// Establim valor de 'z' per defecte
	glClearDepth(1.0);
}
 
int main(int argc, char **argv)
{
		//Per si passem par�metres a openGL	
	glutInit(&argc, argv);
		//Inicialitzaci� de finestra i matrius
	inicialitzacio();
		//Funci� encarregada de dir que cal renderitzar (dibuxar)
    glutDisplayFunc(display);
		//Programaci� del canvi d'escala
//  glutReshapeFunc(reshape);
	  //El programa s�espera fins que sortim
	glutMainLoop();
    return 0;
}