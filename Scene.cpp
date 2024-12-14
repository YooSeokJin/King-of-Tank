#include "Scene.h"
#include "Bullet.h"
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
	clearTime_ = 0.f;
	showMiniMap_ = false;

	miniMap_.setPosition(1, 50, 0);
}

Scene::~Scene()
{
	Renderer::M_end(*this);
}

void Scene::draw()
{
	Renderer::M_clear(backgroundColor_);

	auto proj = camera_.getPerspectiveMatrix();
	auto view = camera_.getViewMatrix();
	Renderer::M_glViewport(0, 0, width_, height_);
	Renderer::M_renderScene(*this, proj, view);

	if (!showMiniMap_) return;
	Renderer::M_glViewport(width_ - miniMapWidth_ - 10, 10, miniMapWidth_, miniMapHeight_);
	auto proj2 = miniMap_.getOrthographicMatrix();
	auto view2 = miniMap_.getViewMatrix();
	Renderer::M_renderScene(*this, proj2, view2);
}

void Scene::update(float frameTime)
{
	clearTime_ += frameTime;
	checkGarbage();
	playeController_->update(frameTime);
	for (auto& obj : objects_) {
		CollisionChecker::M_checkFalling(obj, staticObjects_);
		CollisionChecker::M_checkCollide(obj, staticObjects_, objects_);
		obj->update(frameTime);
	}
	for (auto& bullet : bullets_) {
		CollisionChecker::M_checkBullet(bullet, staticObjects_, objects_);
		bullet->update(frameTime);
	}
	for (auto& line : lines_) {
		line->update();
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
	else if (key == 4) Renderer::M_collisionOnOff(isColl_);
}

void Scene::keyUp(unsigned char key, int x, int y)
{
	if (!playeController_) return;
	playeController_->keyUp(key, x, y);

	if (key == 'm' || key == 'M') showMiniMap_ = !showMiniMap_;
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

void Scene::mouseInput(int button, int state, int x, int y)
{
	if (!playeController_) return;
	playeController_->mouseInput(button, state, x, y);

}

const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const
{
	return objects_;
}

const std::vector<std::shared_ptr<Static_Object>>& Scene::getStaticObjects() const
{
	return staticObjects_;
}

const std::vector<std::shared_ptr<Object>>& Scene::getBullets() const
{
	return bullets_;
}

const std::vector<std::shared_ptr<Line>>& Scene::getLines() const
{
	return lines_;
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
		addStaticObject("./objs/cube.obj", "Texture");
	}
	else {
		addObject("./objs/cube.obj", "Texture");
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

void Scene::checkGarbage()
{
	if (clearTime_ < 1.f) return;
	bullets_.erase(
		std::remove_if(bullets_.begin(), bullets_.end(),
			[](const std::shared_ptr<Object>& bullet) {
				if (bullet->isDeleteTarget()) {
					Renderer::M_deleteObj(bullet);
					return true;
				}
				return false;
			}),
		bullets_.end()
	);

	objects_.erase(
		std::remove_if(objects_.begin(), objects_.end(),
			[](const std::shared_ptr<Object>& bullet) {
				if (bullet->isDeleteTarget()) {
					Renderer::M_deleteObj(bullet);
					return true;
				}
				return false;
			}),
		objects_.end()
	);

	clearTime_ = 0.f;
}

