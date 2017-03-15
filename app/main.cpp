
#include <windows.h>
#include <GL/glew.h>  
#include <GL/freeglut.h>
#include <SOIL.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Input.hpp"
#include "FpsCounter.hpp"
#include "GameManager.hpp"
#include "glm/glm.hpp"

#include <iostream>

std::shared_ptr<GameManager> gm;
siut::FpsCounter counter;

int window;

bool keyPressed[30];
int mousePosX, mousePosY;
float moveX, moveY;

void init()//preinitialization before rendering
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	GLenum err = glewInit();

	counter.start();//start of fps counter

	gm.reset(new GameManager());
	gm->init();//game manager initialization

	for (int i = 0; i < 30; i++)
		keyPressed[i] = false;//setting key events to false
}

void display()//rendering
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clearing the scene

	gm->update(counter.fps());
	gm->render();

	if (keyPressed[KEY_ID_W] == true)      gm->getCam()->moveForward();
	if (keyPressed[KEY_ID_A] == true)      gm->getCam()->moveLeft();
	if (keyPressed[KEY_ID_D] == true)      gm->getCam()->moveRight();
	if (keyPressed[KEY_ID_S] == true)      gm->getCam()->moveBackward();
	if (keyPressed[KEY_ID_SPACE] == true)  gm->getCam()->moveUp();
	if (keyPressed[KEY_ID_C] == true)      gm->getCam()->moveDown();

	glutSwapBuffers();//swap buffer objects ?
	glutPostRedisplay();

}

void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 27:
		glutDestroyWindow(window);
#ifndef _WIN32
		// Must use this with regular glut, since it never returns control to main().
		exit(0);
#endif
		break;

	case 'w':
		keyPressed[KEY_ID_W] = true;
		break;
	case 'a':
		keyPressed[KEY_ID_A] = true;
		break;
	case 's':
		keyPressed[KEY_ID_S] = true;
		break;
	case 'd':
		keyPressed[KEY_ID_D] = true;
		break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = true;
		break;
	case 'c':
		keyPressed[KEY_ID_C] = true;
		break;

	default:
		glutPostRedisplay();
	}
}

void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		keyPressed[KEY_ID_W] = false;
		break;
	case 'a':
		keyPressed[KEY_ID_A] = false;
		break;
	case 's':
		keyPressed[KEY_ID_S] = false;
		break;
	case 'd':
		keyPressed[KEY_ID_D] = false;
		break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = false;
		break;
	case 'c':
		keyPressed[KEY_ID_C] = false;
		break;

	}
}

void mousePressed(int button, int state, int posX, int posY)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mousePosX = posX;
		mousePosY = posY;
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
	if (keyPressed[MOUSE_LEFT_BUTTON_DOWN])
	{
		int diffX = posX - mousePosX;
		mousePosX = posX;
		int diffY = posY - mousePosY;
		mousePosY = posY;

		// Implement quaternion based mouse move

	}
}

void reshape(int w, int h)//resize
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//  glOrtho(-50, 700, -50, 700, -50, 50);
	gluPerspective(60.0f, float(w) / float(h), 1.0f, 3000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//  gluLookAt(0.0, 0.0, 10.0,     0.0, 0.0, 0.0,    0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(10, 10);
	window = glutCreateWindow("Space Shooter 3D");
	init();
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseMoved);

	// Add other callback functions here..

	glutMainLoop();
	return 0;
}
