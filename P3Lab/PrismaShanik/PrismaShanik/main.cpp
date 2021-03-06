//Semestre 2019 - 1
//*************************************************************//
//************************************************************//
//****** Alumno (s): Trejo Luna Eva Marion Shanik************//
//************* Visual Studio 2017			****************//
//*************	Ejercicio de clase:Pr�ctica #3		*******//
//********************************************************//

//#include <gl/gl.h>     // The GL Header File
//#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
//#include <stdlib.h>
#include "Main.h"

float angleX = 0.0f;//angulos 
float angleY = 0.0f;
float angleZ = 0.0f;
float transX = 0.0f;//traslaciones
float transY = 0.0f;
float transZ = -5.0f;


void InitGL(GLvoid)     // Inicializamos parametros
{

	//glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
														//glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
														//glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void prisma(void)
{
	GLfloat vertice[8][3] = {//arreglo de vertices 0-7
		{ 1,0,0},    //Coordenadas V�rtice 0 V0
		{ 1,1,0},    //Coordenadas V�rtice 1 V1
		{ 0,1,0 },    //Coordenadas V�rtice 2 V2
		{ 0,0,0 },    //Coordenadas V�rtice 3 V3
		{ 0,1,5 },    //Coordenadas V�rtice 4 V4
		{ 1,1,5 },    //Coordenadas V�rtice 5 V5
		{ 0,0,5 },    //Coordenadas V�rtice 6 V6
		{ 1,0, 5 },    //Coordenadas V�rtice 7 V7
		};

	


	glBegin(GL_POLYGON);	//Front poligono 
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(vertice[0]);//cara frontal
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[7]);
	glEnd();

	glBegin(GL_POLYGON);	//Right Derecha
	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glEnd();

	glBegin(GL_POLYGON);	//Back Atr�s
	glColor3f(0.0, 1.0, 0.0);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[6]);
	glEnd();

	glBegin(GL_POLYGON);  //Left Izq
	glColor3f(1.0, 1.0, 1.0);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom tapa

	glColor3f(0.4, 0.2, 0.6);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top tapa
	glColor3f(0.8, 0.2, 0.4);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[6]);
	glEnd();
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Poner C�digo Aqu�.
	glTranslatef(transX, transY, transZ);//se recorre hacia atras de nuestra vista
	glRotatef(angleX,1,0,0);//Rotaci�n con las flechas para X &Y
	glRotatef(angleY, 0, 1, 0);
	//Letra E---------------------------------
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(-3, 1, 0);
	prisma();
	glTranslatef(0, 1, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(-3, 1, 0);
	prisma();
	glTranslatef(0, 1, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(2, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	glTranslatef(1, 0, 0);
	prisma();
	//Letra T----------------------
	glTranslatef(-2, -1, 0);
	prisma();
	glTranslatef(0, -1, 0);
	prisma();
	glTranslatef(0, -1, 0);
	prisma();
	glTranslatef(0, -1, 0);
	prisma();
	glutSwapBuffers();
	//glFlush();
	// Swap The Buffers
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista A(izquierda) y D (derecha) para mover 
	//glOrtho(-5,5,-5,5,0.1,20);//0.1 resolucion ,20 volumen de vista	
	//glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 50.0);
	//glFrustum (-2,2,-2,2,0.1,50);
	//glFrustum(-0.5, 0.5, -0.5, 0.5, 0.1, 50);
	glFrustum(-0.5, 0.5, -0.5, 0.5, 0.1, 50);//vista en perspectiva
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	//casos para trasladar las letras en los ejes X,Y y Z en sentido positivo y negativo
	switch (key) {
	case 'w':
	case 'W':
		transZ += 0.2f;
		printf("Posicion en Z: %f\n", transZ);
		break;
	case 's':
	case 'S':
		transZ -= 0.2f;
		printf("Posicion en Z: %f\n", transZ);
		break;
	case 'a':
	case 'A':
		transX += 0.2f;
		printf("Posicion en X: %f\n", transX);
		break;
	case 'd':
	case 'D':
		transX -= 0.2f;
		printf("Posicion en X: %f\n", transX);
		break;
	case 'q':
	case 'Q':
		transY += 0.2f;
		printf("Posicion en Y: %f\n", transY);
		break;
	case 'e':
	case 'E':
		transY -= 0.2f;
		printf("Posicion en Y: %f\n", transY);
		break;
	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		angleX += 1.0f;
		break;
		//glutFullScreen ( ); // Full Screen Mode
		//break;
	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		angleX -= 1.0f;
		break;
		//glutReshapeWindow ( 500, 500 ); // Cambiamos tamano de Ventana
		//break;
	case GLUT_KEY_LEFT:
		angleY += 1.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleY -= 1.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
						   //glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Sencillo )
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tama�o de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 3"); // Nombre de la Ventana
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut funci�n de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut funci�n en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut funci�n de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutMainLoop();          // 

	return 0;
}
