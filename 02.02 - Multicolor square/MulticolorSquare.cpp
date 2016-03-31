/* Copyright (c) Oscar Garc�a Panyella 1998, todos los derechos reservados. 
* Curso de OpenGL para Macedonia Magazine. 
* Primer ejemplo. 
*/

/* Incluimos las librer�as */
#include <GL/glut.h> 		
/* Ancho de la ventana de visualizaci�n */
#define WIDTH  400 
/* Alto de la ventana de visualizaci�n */ 
#define HEIGHT 400 
/* Coordenada X del origen de la ventana, esquina superior izquierda */ 
#define WINDOWS_X_POSITION  100 
/* Coordenada Y del origen de la ventana, esquina superior izquierda */ 
#define WINDOWS_Y_POSITION  100

/* 
* Inicialitza les matrius de vista i projecci�, aix� com la creaci� de la finestra
*/ 
void inicialitlizacio() { 
	// Inici de la configuraci� del context OpenGL
	// Activem el buffer simple i els colors del tipus RGB 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	// Definim una finestra de mides WIDTH per HEIGHT com finestra de visualitzaci� 
	glutInitWindowSize (WIDTH, HEIGHT); 
	// Posicionem el costat superior esquerra de la finestra a les coordenades
	glutInitWindowPosition (WINDOWS_X_POSITION, WINDOWS_Y_POSITION); 
	// Es crea la finestra i se li assigna un t�tol
	glutCreateWindow("Quadrat Multicolor");
	// Ja tenim el context creat, ara activem la matriu de projecci�, nom�s cal un cop
	glMatrixMode(GL_PROJECTION); 
	// Inicialitzem amb la matriu identitat
	glLoadIdentity(); 
	// El pla de projecci� ser� la finestra de visualitzaci� i amb profunditat de z=-10 fins z=10
	glOrtho(0, WIDTH, 0, HEIGHT, -10, 10); 
	// Activem la matriu de visualitzaci�
	glMatrixMode(GL_MODELVIEW); 
	// Inicialitzem amb la matriu identitat
	glLoadIdentity(); 
	//Ubiquem la c�mera mirant cap al pol�gon
	gluLookAt(0,0,1,0,0,0,0,1,0);
	// Ens traslladem al centre de la finestra 
	glTranslatef((GLfloat)WIDTH/2, (GLfloat)HEIGHT/2, 5.0); 
	// Establim el color de fons al negre
	glClearColor(0.0, 0.0, 0.0, 0.0); 
}

/* 
* OpenGL cridar� a aquesta funci� cada cop que hagi de tornar a dibuixar, per exemple si la finestra es mou, canvia la mida
*/ 
void dibuixar(void) { 
		//Restauraci� del frame buffer de color
		//Obligat per un correcte funcionament del proc�s de render
		// �s una reinicialitzaci� de la finestra amb el color definit abans
	glClear(GL_COLOR_BUFFER_BIT); 
		// Nom�s pintarem les cares frontals dels pol�gons i les omplirem de color
	glPolygonMode(GL_FRONT, GL_FILL); 
	glBegin(GL_TRIANGLES); 
		// Color blau pel primer vertex  
	glColor3f(0.0, 0.0, 1.0); 
	glVertex3i(-100, -100, 0); 
		// Color verd pel segon vertex
	glColor3f(0.0, 1.0, 0.0); 
	glVertex3i(100, -100, 0); 
		//Color vermell pel tercer vertex
	glColor3f(1.0, 0.0, 0.0); 
	glVertex3i(100, 100, 0); 


		//Color groc pel quart vertex
	glColor3f(0.0, 0.0, 1.0); 
	glVertex3i(100, 100, 0); 

	//Color groc pel cinqu� vertex
	glColor3f(1.0, 0.0, 0.0);
	glVertex3i(-100, -100, 0);

	//Color groc pel sis� vertex
	glColor3f(0.0, 1.0, 0.0);
	glVertex3i(-100, 100, 0);

	glEnd(); 
	
	//For�a l'execuci� de les comandes anterior
    glFlush();
}

/* 
* Main del programa. 
*/
int main(int argc, char **argv) { 
	//Per si passem par�metres a openGL	
	glutInit(&argc, argv); 
		//Inicialitzaci� de finestra i matrius
	inicialitlizacio();
		//Indiquem que ha de dibuixar-se sempre
	glutDisplayFunc(dibuixar);
		//El programa s�espera fins que sortim
	glutMainLoop();
	return 0;
}