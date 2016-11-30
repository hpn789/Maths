
#ifdef _MSC_VER
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#endif

#include <iostream>

using namespace std;

#ifdef NO_GLEW
#include <gl/GL.h>
#include "glext.h"
#else
#include "glew.h"
#ifdef _MSC_VER
#pragma comment(lib, "glew32.lib")
#endif
#endif // !NO_GLEW

#include "freeglut.h"

#include "../common/EsgiShader.h"

// Variables globales
EsgiShader g_BasicShader;
bool g_bDetectLeftClic = false;
int g_fPosXClic = 0;
int g_fPosYClic = 0;

static const float g_Triangle[] = {
	-0.8f, .8f,
	0.f, -.8f,
	.8f, .8f
};

static const float g_Color[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

static const float g_TriangleAttribs[] = {
	-0.8f, .8f,
	1.0f, 0.0f, 0.0f,
	0.f, -.8f,
	0.0f, 1.0f, 0.0f,
	.8f, .8f,
	0.0f, 0.0f, 1.0f
};

int width = 800;
int height = 600;
int g_nWindowID;

void animate()
{
	glViewport(0, 0, width, height);
	glClearColor(1.f, 1.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	auto program = g_BasicShader.GetProgram();

	glUseProgram(program);
	
	auto color_location = glGetAttribLocation(program, "a_Color");
	auto position_location = glGetAttribLocation(program, "a_Position");

	if (g_bDetectLeftClic == true)
	{
		cout << "Click gauche detecte \n" << endl;
		// Attention ici on r�cup�re des valeurs de x tel que 0 < x < 800 et des valeurs de y tel que 0 < y < 600
		cout << "X : " << g_fPosXClic << " - Y : " << g_fPosYClic << endl;
		g_bDetectLeftClic = false;
		g_fPosXClic = 0;
		g_fPosYClic = 0;
	}

	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), &g_TriangleAttribs[2]);
	glVertexAttribPointer(position_location, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), &g_TriangleAttribs[0]);

	//glVertexAttribPointer(position_location, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), g_Triangle);
	//glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), g_Color);

	glEnableVertexAttribArray(position_location);
	glEnableVertexAttribArray(color_location);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(position_location);
	glDisableVertexAttribArray(color_location);

	glUseProgram(0);

	glutSwapBuffers();
}

// fonction de gestion du clavier
void KeyBoardDetect(unsigned char touche, int x, int y)
{
	// traitement des touches q et echap
	if (touche == 'q' || touche == 27)
	{
		// destruction de la fenetre GLUT
		glutDestroyWindow(g_nWindowID);
		// on quitte le programme
		exit(EXIT_SUCCESS);
	}
}

// fonction de gestion de la souris
void MouseDetect(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:   //gestion du bouton gauche*/
			if (state == GLUT_DOWN)   //Si le bouton gauche est clicker
				//cout << "Click gauche detecte \n" << endl;  //On affiche un message comme quoi le bouton a ete enfonce
				g_bDetectLeftClic = true;
				g_fPosXClic = x;
				g_fPosYClic = y;
			break;
		case GLUT_RIGHT_BUTTON:  //gestion du bouton droit de la souris
			if (stat == GLUT_DOWN)  //si le bouton est enfonce
				cout << "Bouton droit de la souris clicker\n" << endl;  //Affichage du message
			break;
	}
}


int main(int argc, const char* argv)
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(width, height);
	g_nWindowID = glutCreateWindow("Maths");

	#ifndef NO_GLEW
	glewInit();
	#endif

	g_BasicShader.LoadVertexShader("basic.vs");
	g_BasicShader.LoadFragmentShader("basic.fs");
	g_BasicShader.CreateProgram();

	glutDisplayFunc(animate);
	glutMouseFunc(MouseDetect);
	glutKeyboardFunc(KeyBoardDetect);
	glutMainLoop();

	g_BasicShader.DestroyProgram();

	return 1;
}