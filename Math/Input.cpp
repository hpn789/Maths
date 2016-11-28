#include "Input.h"
#include "Scene.h"

Input* Input::currentInstance = nullptr;

void Input::keyboardCallBack(unsigned char touche, int x, int y)
{
	Input::currentInstance->checkKeyboardInputs(touche, x, y);
}

void Input::mouseCallBack(int button, int state, int x, int y)
{
	Input::currentInstance->checkMouseClicks(button, state, x, y);
}

Input::Input(Scene *s)
{
	Input::currentInstance = this;
	scene = s;
}


Input::~Input()
{
}

void Input::init()
{
	glutKeyboardFunc(Input::keyboardCallBack);
	glutMouseFunc(Input::mouseCallBack);
}

bool Input::isLetterPressed(char letter)
{
	int nb = letter - (int)'A';
	if(nb<0 || nb>25)
	return false;
	return (letters[nb] == PRESSED);
}

bool Input::isLetterClicked(char letter)
{
	int nb = letter - (int)'A';
	if (nb<0 || nb>25)
		return false;
	return (letters[nb] == CLICKED);
}

bool Input::isMouseButtonPressed(int button)
{
	if (button<0 || button>2)
		return false;
	return (mouseButtons[button] == PRESSED);
}

bool Input::isMouseButtonClicked(int button)
{
	if (button<0 || button>2)
		return false;
	return (mouseButtons[button] == CLICKED);
}

void Input::checkKeyboardInputs(unsigned char  touche, int x, int y)
{
	std::cout << "Keypressed : " << (char)touche<<std::endl;
	switch (touche)
	{
	case 'a':
		std::cout << "change state : ENTER_POINTS" << std::endl;
		scene->changeState(ENTER_POINTS);
		glutPostRedisplay();
		break;
	case 'z':
		std::cout << "change state : DRAW" << std::endl;
		scene->changeState(DRAW);
		glutPostRedisplay();
		break;
	}

	
}

void Input::checkMouseClicks(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && scene->getState()== ENTER_POINTS) {
		std::cout << "mouse click x=" << x << " y=" << y << std::endl;
		maths::Point p;
		p.x = x;
		p.y = y;
		scene->addPoint(p);
		//onMouse = 1;
		glutPostRedisplay();
	}

	
}