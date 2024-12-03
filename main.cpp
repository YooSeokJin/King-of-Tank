#include <iostream>
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glm/glm.hpp"

#include "global.h"
#include "KOT_Scene.h"

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
// KOF_Scene - Tank, KoTScene, KoTPlayerController, KoTAIController 등

// 모듈: M_functionName, M_memberName_
// 클래스: functionName, memberName_

void initProgram();
GLvoid renderScene();
GLvoid reshape(int w, int h);
GLvoid renderSceneTimer(int value);
GLvoid idle();
GLvoid mouseInput(int button, int state, int x, int y);
GLvoid mouseMotion(int x, int y);
GLvoid mouseWheel(int button, int dir, int x, int y);

GLvoid keyInput(unsigned char key, int x, int y);
GLvoid specialKeyInput(int key, int x, int y);
GLvoid keyDown(unsigned char key, int x, int y);
GLvoid keyUp(unsigned char key, int x, int y);


void exitProgram();

const float frameTime_ = float(0.016);
KOT_Scene* scene_ = nullptr;
bool warpPointerEvent_ = false;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(600, 200);
	glutInitWindowSize(width_, height_);
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
	initProgram();

	glutTimerFunc(16, renderSceneTimer, 1);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouseInput);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseWheelFunc(mouseWheel);
	glutSpecialFunc(specialKeyInput);
	glutMainLoop();
}

void initProgram()
{
	scene_ = new KOT_Scene();
}

GLvoid renderScene()
{
	if (!scene_) return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene_->draw();
	glutSwapBuffers();
}
GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid renderSceneTimer(int value)
{
	if (!scene_) return;
	scene_->timer(frameTime_);
	glutPostRedisplay();
	glutTimerFunc(16, renderSceneTimer, 1);
}
GLvoid idle()
{
	if (!scene_) return;
	glutPostRedisplay();
}
GLvoid mouseInput(int button, int state, int x, int y)
{
	if (!scene_) return;
	scene_->mouseInput(button, state, x, y);

	glutPostRedisplay();
}
GLvoid mouseMotion(int x, int y)
{
	if (!scene_) return;

	scene_->mouseMotion(x, y);

	glutWarpPointer(windowCenterX_, windowCenterY_);
	glutPostRedisplay();
}
GLvoid mouseWheel(int button, int dir, int x, int y)
{
	if (!scene_) return;
	scene_->mouseWheel(button, dir, x, y);
}
GLvoid keyInput(unsigned char key, int x, int y)
{
	if (!scene_) return;
	switch (key) {
	case 27:
		exitProgram();
		break;
	}
	
	glutPostRedisplay();
}
GLvoid specialKeyInput(int key, int x, int y)
{
	if (!scene_) return;
	
	scene_->specialEvent(key, x, y);
	glutPostRedisplay();
}

GLvoid keyDown(unsigned char key, int x, int y)
{
	if (key == 27) exitProgram();
	if (!scene_) return;
	scene_->keyDown(key, x, y);
}

GLvoid keyUp(unsigned char key, int x, int y)
{
	if (!scene_) return;
	scene_->keyUp(key, x, y);
}

GLvoid exitProgram()
{
	delete scene_;
	scene_ = nullptr;
	glutLeaveMainLoop();
}
