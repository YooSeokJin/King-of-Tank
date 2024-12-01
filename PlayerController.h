#pragma once
#include <memory>
#include "Object.h"
#include "Camera.h"

class PlayerController {
public:
	PlayerController();
	PlayerController(std::shared_ptr<Object> target);
	~PlayerController();

	virtual void event(unsigned char key, int x, int y);
	virtual void keyDown(unsigned char key, int x, int y);
	virtual void keyUp(unsigned char key, int x, int y);
	virtual void mouseMotion(int x, int y);
	virtual void mouseWheel(int button, int dir, int x, int y);
	void setTarget(std::shared_ptr<Object> target);
	void setCamera(Camera* camera);
	glm::vec3 getCameraOffset() const { return cameraOffset_; }
protected:
	std::shared_ptr<Object> target_;
	glm::vec3 cameraOffset_;
	Camera* camera_;
};