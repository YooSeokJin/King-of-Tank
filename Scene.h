#pragma once
#include "glm/glm.hpp"
#include "Mesh.h"
#include "Camera.h"
#include "Object.h"
#include "PlayerController.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	void Init();

	virtual void timer(float delta) = 0;
	virtual void event(unsigned char key, int x, int y) = 0;
	virtual void draw();
	virtual void specialEvent(int key, int x, int y);
	virtual void keyUp(unsigned char key, int x, int y);
	virtual void keyDown(unsigned char key, int x, int y);
	virtual void mouseMotion(int x, int y);
	virtual void mouseWheel(int button, int dir, int x, int y);

	const glm::vec4& getBackgroundColor() const { return backgroundColor_; }
	const std::vector<std::shared_ptr<Object>>& getObjects() const;
	const std::vector<std::shared_ptr<Static_Object>>& getStaticObjects() const;

	//
	Camera getCamera() const { return camera_; };

	bool isShowMouse_;
protected:
	virtual void update(float frameTime);
	void addObject(const std::string& fileName, const std::string& shaderName);
	void addStaticObject(const std::string& fileName, const std::string& shaderName);
	
	void addLightCube(bool Static);
	void addCube(bool Static);
	void addSphere(bool Static);
	void addCylinder(bool Static);
	void addPyramid(bool Static);
	void addRectPyramid(bool Static);
	void addMonkey(bool Static);

	void setupObject(std::shared_ptr<Object> obj);
	void setupStaticObject(std::shared_ptr<Static_Object> obj);

private:
	
protected:
	bool isCull_, isFill_, isDepth_, isColl_;
	int mouseLastX_, mouseLastY_;
	std::vector<std::shared_ptr<Object>> objects_;
	std::vector<std::shared_ptr<Static_Object>> staticObjects_;
	std::shared_ptr<PlayerController> playeController_;
	glm::vec4 backgroundColor_;
	Camera camera_;
};

