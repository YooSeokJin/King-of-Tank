#include <iostream>
#include <memory>

#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glm/glm.hpp"

#include "global.h"
#include "newScene.h"

void InitProgram();
GLvoid RenderScene();
GLvoid Reshape(int w, int h);
GLvoid RenderSceneTimer(int value);
GLvoid Idle();
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid SpecialKeyInput(int key, int x, int y);

void ExitProgram();

const float frameTime = float(0.016);
bool isClicked = false;
int animNum = 0;
newScene* scene = nullptr;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(600, 200);
	glutInitWindowSize(WinSizeX, WinSizeY);
	glutCreateWindow("Computer Graphics");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_3"))
	{
		std::cout << " GLEW Version is 3.3\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	std::cout << "[ESC]: Exit" << std::endl;
	InitProgram();

	glutTimerFunc(16, RenderSceneTimer, 1);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMotion);
	glutSpecialFunc(SpecialKeyInput);
	
	glutMainLoop();
}

void InitProgram()
{
	scene = new newScene();
}

void RenderScene()
{
	if (!scene) return;
	scene->draw();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
void RenderSceneTimer(int value)
{
	if (!scene) return;
	scene->update(frameTime);
	glutPostRedisplay();
	glutTimerFunc(16, RenderSceneTimer, 1);
}
void Idle()
{
	if (!scene) return;
	glutPostRedisplay();
}
void MouseInput(int button, int state, int x, int y)
{
	if (!scene) return;
	if (button == GLUT_LEFT_BUTTON) {
		glm::vec3 center(0.0f, 0.0f, 0.0f);
		changeOpenGL(x, y, 0, center);
		if (state == GLUT_DOWN) {

		}
		else if (state == GLUT_UP) {

		}
	}	
	glutPostRedisplay();
}
void MouseMotion(int x, int y)
{
	if (!scene) return;
	if (isClicked) {
		glm::vec3 center(0.0f, 0.0f, 0.0f);
		changeOpenGL(x, y, 0, center);

	}
}
void KeyInput(unsigned char key, int x, int y)
{
	if (!scene) return;
	switch (key) {
	case 27:
		ExitProgram();
		break;
	default:
		scene->event(key, x, y);
		break;
	}
	
	glutPostRedisplay();
}
void SpecialKeyInput(int key, int x, int y) 
{
	if (!scene) return;
	scene->specialEvent(key, x, y);
	glutPostRedisplay();
}

void ExitProgram()
{
	delete scene;
	scene = nullptr;
	glutLeaveMainLoop();
}
