#include <iostream>
#include <memory>

#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glm/glm.hpp"

#include "global.h"
#include "KOF_Scene.h"

// Component - Movement, Collision
// Mesh - Mesh
// Object - Object
// Transform - ModelMatrix, Viewing, Projection
// Controller - PlayerController, AIController
// Rendering - Camera, Shader, ShaderManager, Grid
// Scene - Scene
// Module - Renderer.ixx, ObjectLoader.ixx, CollisionChecker.ixx
// shaders - FS, VS 세이더 파일
// objs - .obj 파일
// KOF_Scene - Tank, KofScene, KofPlayerController, KofAIController 등

void InitProgram();
GLvoid RenderScene();
GLvoid Reshape(int w, int h);
GLvoid RenderSceneTimer(int value);
GLvoid Idle();
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid SpecialKeyInput(int key, int x, int y);
GLvoid KeyDown(unsigned char key, int x, int y);
GLvoid KeyUp(unsigned char key, int x, int y);

void ExitProgram();

const float frameTime = float(0.016);
bool isClicked = false;
int animNum = 0;
KOF_Scene* scene = nullptr;

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
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMotion);
	glutSpecialFunc(SpecialKeyInput);
	//glutKeyboardFunc(KeyInput);
	glutMainLoop();
}

void InitProgram()
{
	scene = new KOF_Scene();
}

GLvoid RenderScene()
{
	if (!scene) return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->draw();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid RenderSceneTimer(int value)
{
	if (!scene) return;
	scene->timer(frameTime);
	glutPostRedisplay();
	glutTimerFunc(16, RenderSceneTimer, 1);
}
GLvoid Idle()
{
	if (!scene) return;
	glutPostRedisplay();
}
GLvoid MouseInput(int button, int state, int x, int y)
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
GLvoid MouseMotion(int x, int y)
{
	if (!scene) return;
	if (isClicked) {
		glm::vec3 center(0.0f, 0.0f, 0.0f);
		changeOpenGL(x, y, 0, center);

	}
}
GLvoid KeyInput(unsigned char key, int x, int y)
{
	if (!scene) return;
	switch (key) {
	case 27:
		ExitProgram();
		break;
	}
	
	glutPostRedisplay();
}
GLvoid SpecialKeyInput(int key, int x, int y)
{
	if (!scene) return;
	
	scene->specialEvent(key, x, y);
	glutPostRedisplay();
}

GLvoid KeyDown(unsigned char key, int x, int y)
{
	if (key == 27) ExitProgram();
	if (!scene) return;
	scene->KeyDown(key, x, y);
}

GLvoid KeyUp(unsigned char key, int x, int y)
{
	if (!scene) return;
	scene->KeyUp(key, x, y);
}

GLvoid ExitProgram()
{
	delete scene;
	scene = nullptr;
	glutLeaveMainLoop();
}
