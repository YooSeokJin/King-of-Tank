#include "Scene.h"

#include "global.h"
#include "Grid.h"

import Renderer;
import ObjectLoader;
import CollisionChecker;
Scene::Scene()
{
	bgColor = WhiteColor;
	cull = depth = fill = false;
	showMouse = false;
	Renderer::Init(*this);
	Renderer::Depth(depth);
	Renderer::Cull(cull);
	Renderer::Fill(fill);
	lastX, lastY = 0;
}

Scene::~Scene()
{
	Renderer::End(*this);
}

void Scene::draw()
{
	auto proj = camera.getPerspectiveMatrix();
	auto view = camera.getViewMatrix();
	Renderer::Rnderer_Scene(*this, proj, view);

	for (auto& obj : objs) {
		obj->DrawGrid(view, proj);
	}
}

void Scene::update(float frameTime)
{
	auto proj = camera.getPerspectiveMatrix();
	auto view = camera.getViewMatrix();
	for (auto& obj : objs) {
		for (auto& st : static_objs) {
			CollisionChecker::isCollid_Static(obj, st);
		}
		
		obj->update(frameTime);
	}
	camera.update(frameTime);
}

void Scene::Init()
{
	pc->set_target(objs[0]);
	pc->set_camera(&camera);

	for (auto& obj : objs) {
		for (auto& mesh : obj->getMeshes()) {
			mesh->apply_movement();
			mesh->add_collision();
			mesh->add_movement();
		}
		Renderer::Setup_Object(obj);
		obj->Init();
	}

	for (auto& obj : static_objs) {
		for (auto& mesh : obj->getMeshes()) {
			mesh->apply_movement();
			mesh->add_collision();
		}
		Renderer::Setup_Static_Object(obj);
		obj->Init();
	}
}
void Scene::specialEvent(int key, int x, int y)
{
	if (key == 1) Renderer::Depth(depth);
	else if (key == 2) Renderer::Fill(fill);
	else if (key == 3) Renderer::Cull(cull);
}

void Scene::KeyUp(unsigned char key, int x, int y)
{
	if (!pc) return;
	pc->keyUp(key, x, y);
}

void Scene::KeyDown(unsigned char key, int x, int y)
{
	if (!pc) return;
	pc->keyDown(key, x, y);
}

void Scene::mouseMotion(int x, int y)
{
}

void Scene::mouseWheel(int button, int dir, int x, int y)
{
	if (!pc) return;
	pc->mouseWheel(button, dir, x, y);
}

const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const
{
	return objs;
}

const std::vector<std::shared_ptr<Static_Object>>& Scene::getStaticObjects() const
{
	return static_objs;
}

void Scene::add_Object(const std::string& fileName, const std::string& shaderName)
{
	auto object = ObjectLoader::Load_Object(fileName, shaderName);
	Renderer::Setup_Object(object);
	objs.push_back(object);
}
void Scene::add_Static_Object(const std::string& fileName, const std::string& shaderName)
{
	auto object = ObjectLoader::Load_StaticObject(fileName, shaderName);
	Renderer::Setup_Static_Object(object);
	static_objs.push_back(object);
}

void Scene::add_LightCube(bool Static)
{
	if (Static) {
		add_Static_Object("./objs/cube.obj", "LightSource");
	}
	else {
		add_Object("./objs/cube.obj", "LightSource");
	}
}

void Scene::add_Cube(bool Static)
{
	if (Static) {
		add_Static_Object("./objs/cube.obj", "Model");
	}
	else {
		add_Object("./objs/cube.obj", "Model");
	}
}

void Scene::add_Sphere(bool Static)
{
	if (Static) {
		add_Static_Object("./objs/sphere.obj", "Model");
	}
	else {
		add_Object("./objs/sphere.obj", "Model");
	}
}

void Scene::add_Cylinder(bool Static)
{
	if (Static) {
		add_Static_Object("./objs/cylinder.obj", "Model");
	}
	else {
		add_Object("./objs/cylinder.obj", "Model");
	}
}

void Scene::add_Pyramid(bool Static)
{
	if (Static) {
		add_Static_Object("./objs/pyramid.obj", "Model");
	}
	else {
		add_Object("./objs/pyramid.obj", "Model");
	}
}

void Scene::add_Rpyramid(bool Static)
{
	if (Static) {
		add_Static_Object("./objs/rpyramid.obj", "Model");
	}
	else {
		add_Object("./objs/rpyramid.obj", "Model");
	}
}

void Scene::add_Monkey(bool Static)
{
	if (Static) {
		add_Static_Object("./objs/monkey.obj", "Model");
	}
	else {
		add_Object("./objs/monkey.obj", "Model");
	}
}

void Scene::setUp(std::shared_ptr<Object> obj)
{
	Renderer::Setup_Static_Object(obj);
}

