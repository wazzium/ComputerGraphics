/* Copyright (c) Oscar García Panyella 1998, todos los derechos reservados. 
* Curso de OpenGL para Macedonia Magazine. 
* Primer ejemplo. 
*/

/* Incluimos las librerías */
#include <GL/glut.h> 		
/* Ancho de la ventana de visualización */
#define WIDTH  400 
/* Alto de la ventana de visualización */ 
#define HEIGHT 400 
/* Coordenada X del origen de la ventana, esquina superior izquierda */ 
#define WINDOWS_X_POSITION  100 
/* Coordenada Y del origen de la ventana, esquina superior izquierda */ 
#define WINDOWS_Y_POSITION  100

/* 
* Inicialitza les matrius de vista i projecció, així com la creació de la finestra
*/ 
void inicialitlizacio() { 
	// Inici de la configuració del context OpenGL
	// Activem el buffer simple i els colors del tipus RGB 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	// Definim una finestra de mides WIDTH per HEIGHT com finestra de visualització 
	glutInitWindowSize (WIDTH, HEIGHT); 
	// Posicionem el costat superior esquerra de la finestra a les coordenades
	glutInitWindowPosition (WINDOWS_X_POSITION, WINDOWS_Y_POSITION); 
	// Es crea la finestra i se li assigna un títol
	glutCreateWindow("Quadrat Multicolor");
	// Ja tenim el context creat, ara activem la matriu de projecció, només cal un cop
	glMatrixMode(GL_PROJECTION); 
	// Inicialitzem amb la matriu identitat
	glLoadIdentity(); 
	// El pla de projecció serà la finestra de visualització i amb profunditat de z=-10 fins z=10
	glOrtho(0, WIDTH, 0, HEIGHT, -10, 10); 
	// Activem la matriu de visualització
	glMatrixMode(GL_MODELVIEW); 
	// Inicialitzem amb la matriu identitat
	glLoadIdentity(); 
	//Ubiquem la càmera mirant cap al polígon
	gluLookAt(0,0,1,0,0,0,0,1,0);
	// Ens traslladem al centre de la finestra 
	glTranslatef((GLfloat)WIDTH/2, (GLfloat)HEIGHT/2, 5.0); 
	// Establim el color de fons al negre
	glClearColor(0.0, 0.0, 0.0, 0.0); 
}

/* 
* OpenGL cridarà a aquesta funció cada cop que hagi de tornar a dibuixar, per exemple si la finestra es mou, canvia la mida
*/ 
void dibuixar(void) { 
		//Restauració del frame buffer de color
		//Obligat per un correcte funcionament del procés de render
		// És una reinicialització de la finestra amb el color definit abans
	glClear(GL_COLOR_BUFFER_BIT); 
		// Només pintarem les cares frontals dels polígons i les omplirem de color
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

	//Color groc pel cinquè vertex
	glColor3f(1.0, 0.0, 0.0);
	glVertex3i(-100, -100, 0);

	//Color groc pel sisè vertex
	glColor3f(0.0, 1.0, 0.0);
	glVertex3i(-100, 100, 0);

	glEnd(); 
	
	//Força l'execució de les comandes anterior
    glFlush();
}

/* 
* Main del programa. 
*/
int main(int argc, char **argv) { 
	//Per si passem paràmetres a openGL	
	glutInit(&argc, argv); 
		//Inicialització de finestra i matrius
	inicialitlizacio();
		//Indiquem que ha de dibuixar-se sempre
	glutDisplayFunc(dibuixar);
		//El programa s’espera fins que sortim
	glutMainLoop();
	return 0;
}