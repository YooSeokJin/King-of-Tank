#include "Scene.h"

#include "global.h"
#include "Grid.h"

import Renderer;
import ObjectLoader;
import CollisionChecker;
Scene::Scene()
{
	backgroundColor_ = whiteColorV4_;
	isCull_ = isDepth_ = isFill_, isColl_ = false;
	isShowMouse_ = false;
	Renderer::M_initRenderer(*this);
	Renderer::M_depthOnOff(isDepth_);
	Renderer::M_cullOnOff(isCull_);
	Renderer::M_fillOnOff(isFill_);
	mouseLastX_, mouseLastY_ = 0;
}

Scene::~Scene()
{
	Renderer::M_end(*this);
}

void Scene::draw()
{
	auto proj = camera_.getPerspectiveMatrix();
	auto view = camera_.getViewMatrix();
	Renderer::M_renderScene(*this, proj, view);

	for (auto& obj : objects_) {
		obj->drawGrid(view, proj);
	}
}

void Scene::update(float frameTime)
{
	auto proj = camera_.getPerspectiveMatrix();
	auto view = camera_.getViewMatrix();
	for (auto& obj : objects_) {
		for (auto& st : staticObjects_) {
			CollisionChecker::M_checkCollide(obj, st);
		}
		
		obj->update(frameTime);
	}
	camera_.update(frameTime);
}

void Scene::Init()
{
	playeController_->setTarget(objects_[0]);
	playeController_->setCamera(&camera_);

	for (auto& obj : objects_) {
		for (auto& mesh : obj->getMeshes()) {
			mesh->applyMovement();
			mesh->addCollision();
			mesh->addMovement();
		}
		Renderer::M_setupObject(obj);
		obj->Init();
	}

	for (auto& obj : staticObjects_) {
		for (auto& mesh : obj->getMeshes()) {
			mesh->applyMovement();
			mesh->addCollision();
		}
		Renderer::M_setupStaticObject(obj);
		obj->Init();
	}
}
void Scene::specialEvent(int key, int x, int y)
{
	if (key == 1) Renderer::M_depthOnOff(isDepth_);
	else if (key == 2) Renderer::M_fillOnOff(isFill_);
	else if (key == 3) Renderer::M_cullOnOff(isCull_);
	else if (key == 4) Renderer::m_collsionOnOff(isColl_);
}

void Scene::keyUp(unsigned char key, int x, int y)
{
	if (!playeController_) return;
	playeController_->keyUp(key, x, y);
}

void Scene::keyDown(unsigned char key, int x, int y)
{
	if (!playeController_) return;
	playeController_->keyDown(key, x, y);
}

void Scene::mouseMotion(int x, int y)
{
}

void Scene::mouseWheel(int button, int dir, int x, int y)
{
	if (!playeController_) return;
	playeController_->mouseWheel(button, dir, x, y);
}

const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const
{
	return objects_;
}

const std::vector<std::shared_ptr<Static_Object>>& Scene::getStaticObjects() const
{
	return staticObjects_;
}

void Scene::addObject(const std::string& fileName, const std::string& shaderName)
{
	auto object = ObjectLoader::M_loadObject(fileName, shaderName);
	Renderer::M_setupObject(object);
	objects_.push_back(object);
}
void Scene::addStaticObject(const std::string& fileName, const std::string& shaderName)
{
	auto object = ObjectLoader::M_loadStaticObject(fileName, shaderName);
	Renderer::M_setupStaticObject(object);
	staticObjects_.push_back(object);
}

void Scene::addLightCube(bool Static)
{
	if (Static) {
		addStaticObject("./objs/cube.obj", "LightSource");
	}
	else {
		addObject("./objs/cube.obj", "LightSource");
	}
}

void Scene::addCube(bool Static)
{
	if (Static) {
		addStaticObject("./objs/cube.obj", "Model");
	}
	else {
		addObject("./objs/cube.obj", "Model");
	}
}

void Scene::addSphere(bool Static)
{
	if (Static) {
		addStaticObject("./objs/sphere.obj", "Model");
	}
	else {
		addObject("./objs/sphere.obj", "Model");
	}
}

void Scene::addCylinder(bool Static)
{
	if (Static) {
		addStaticObject("./objs/cylinder.obj", "Model");
	}
	else {
		addObject("./objs/cylinder.obj", "Model");
	}
}

void Scene::addPyramid(bool Static)
{
	if (Static) {
		addStaticObject("./objs/pyramid.obj", "Model");
	}
	else {
		addObject("./objs/pyramid.obj", "Model");
	}
}

void Scene::addRectPyramid(bool Static)
{
	if (Static) {
		addStaticObject("./objs/rpyramid.obj", "Model");
	}
	else {
		addObject("./objs/rpyramid.obj", "Model");
	}
}

void Scene::addMonkey(bool Static)
{
	if (Static) {
		addStaticObject("./objs/monkey.obj", "Model");
	}
	else {
		addObject("./objs/monkey.obj", "Model");
	}
}

void Scene::setupObject(std::shared_ptr<Object> obj)
{
	Renderer::M_setupObject(obj);
}

void Scene::setupStaticObject(std::shared_ptr<Static_Object> obj)
{
	Renderer::M_setupStaticObject(obj);
}

