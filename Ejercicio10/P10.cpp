//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//***** Alumno (s):Trejo Luna Eva Marion Shanik **************//
//************Ejercicio de clase 10: Carro en movimiento******//
//*************			Visual Studio 2017				******//
//************************************************************//
//************************************************************//
//Bibliotecas incluidas
#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h" //cargar formato 3Ds

//Solo para Visual Studio 2015
#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

CCamera objCamera;
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;
//Diferentes tipos de luz,brillo y sombra
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };
//Texturas del entorno
CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
//Figuras del entorno
CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CFiguras fig7; //Para el monito

//Figuras de 3D Studio
CModel kit;
CModel llanta;

//Animaci�n del coche
//se declaran las variables para la animacion
float movKit = 0.0;
float rotder = 0.0;	
float rotizq = 0.0;
bool g_fanimacion = false;
bool limite = false;


void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);// Negro de fondo	
	//Texturas
	glEnable(GL_TEXTURE_2D);	
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//Materiales
	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);// Turn Blending On
	//Se mandan llamar a las texturas
	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	//Carga de Figuras
	kit._3dsLoad("kitt.3ds");
	//kit.VertexNormals();

	llanta._3dsLoad("k_rueda.3ds");


	objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1, 0);

}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;//Almacena los caracteres a escribir
    //Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	glRasterPos3f(x, y, z);	
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //Imprime
	}
}



void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	   glDisable(GL_LIGHTING);
	   glTranslatef(0, 60, 0);
	   fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
	   glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	//Para que el coche conserve sus colores
	    glDisable(GL_COLOR_MATERIAL);
	    glRotatef(90, 0, 1, 0);
	    glScalef(0.3, 0.3, 0.3);
        glTranslatef(0, 4, movKit);//Movimiento
    //Pongo aqu� la carroceria del carro	
	//Glrender mandar a dibujar lo que ya cargamos
	kit.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS
    //Llanta delantera (Piloto)
    glPushMatrix();	
	   glTranslatef(6, -1, 7.5);//Traslacion del pivote (para que el rin quede en el centro)
	   glRotatef(180, 0, 1, 0);//angulo de 180� en el eje y
	   glRotatef(rotizq, 1, 0, 0);//Rotacion de la llanta
	   llanta.GLrender(NULL, _SHADED, 1.0);//Se dibuja la llanta
	glPopMatrix();
	//Llanta delantera (Copiloto)
	glPushMatrix();	
	   glTranslatef(-6, -1, 7.5);//Traslacion del pivote (para que el rin quede en el centro)
	   glRotatef(0, 0, 1, 0);//angulo de 0� en el eje y
	   glRotatef(rotder, 1, 0, 0);//Rotacion de la llanta
	   llanta.GLrender(NULL, _SHADED, 1.0);//Se dibuja la llanta
	glPopMatrix();
	//Llanta trasera (Piloto)
	glPushMatrix();	
	   glTranslatef(6, -1, -9.5);//Traslacion del pivote (para que el rin quede en el centro)
	   glRotatef(180, 0, 1, 0);//angulo de 180� en el eje y
	   glRotatef(rotizq, 1, 0, 0);//Rotacion de la llanta
	   llanta.GLrender(NULL, _SHADED, 1.0);//Se dibuja la llanta 
	glPopMatrix();
	//Llanta trasera (Copiloto)
	glPushMatrix();	
	   glTranslatef(-6, -1, -9.5);//Traslacion del pivote (para que el rin quede en el centro)
	   glRotatef(0, 0, 1, 0);//angulo de 0� en el eje y
	   glRotatef(rotder, 1, 0, 0);//Rotacion de la llanta		
	   llanta.GLrender(NULL, _SHADED, 1.0);//Se dibuja la llanta 
	glPopMatrix();

	glPopMatrix();

	//Para que el comando glColor funcione con iluminacion
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix(); //Flecha
	glScalef(7, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma_anun(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino1
	glTranslatef(23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino2
	glTranslatef(-23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, -4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, 4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, 7.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, -7.0);
	glRotatef(90, 1, 0, 0);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.4, 0.4);
	pintaTexto(-12, 12.0, -14.0, (void *)font, "Practica 10");
	pintaTexto(-12, 10.5, -14, (void *)font, "Auto en Movimiento");
	pintaTexto(-12, 9.0, -14.0, (void *)font, "Shanik Trejo");

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void animacion()
{
	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;


	if (g_fanimacion)
	{
		//Para ir hacia delante
		if (movKit >  120) {
			g_fanimacion = false; //Para detener la animacion en 120  se pone el la variable en falso
			limite = true;

		}
		movKit += 0.5;//Va hacia delante
		rotder += 4.0;//Definimos la rotacion de las llantas
		rotizq -= 4.0;//Definimos la rotacion de las llantas

	}
	//Para ir en reversa
	if (g_fanimacion == false && limite == true)	//si, animacion y limite se cumplieron se hace lo siguiente
	{
		//Condicion: si la animacion y el limite se cumplieron se hace lo siguiente
		if (movKit < -120)
			g_fanimacion = true; //Cuando la animacion este en 120, activamos MovKit en sentido contrario
		movKit -= 0.5;
		//Se define la rotacion de las llantas en sentido contrario cambiandoles el signo
		rotder -= 4.0;	
		rotizq += 4.0;
	}
	glutPostRedisplay();
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

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case ' '://Pone el auto en movimiento
	 //Activamos la animacion si se toca 2 veces cambia el sentido
		g_fanimacion ^= true; 
		break;
	case 'r'://Regresa el auto a la posicion inicial pero continua su movimiento
	case 'R':
		g_fanimacion = movKit = 0.0;//Para regresar la animacion al punto de origen
		break;
		//Si va en reversa cambia el sentido hacia delante
	case 'i':
	case 'I':
		g_fanimacion ^= STOPBITS_20;
		break;
		//Regresa al auto a la posicion inicial pero maneja en reversa
	case 'j':
	case 'J':
		g_fanimacion = movKit=0.0;
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
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tama�o de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 10: Animacion <<Auto en movimiento>>"); // Nombre de la Ventana
									 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut funci�n de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut funci�n en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut funci�n de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}