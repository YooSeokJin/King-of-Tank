#pragma once
#include <memory>
#include "Object.h"
#include "Camera.h"

class PlayerController {
public:
	PlayerController();
	PlayerController(std::shared_ptr<Object> target_);
	~PlayerController();

	virtual void event(unsigned char key, int x, int y);
	virtual void keyDown(unsigned char key, int x, int y);
	virtual void keyUp(unsigned char key, int x, int y);
	virtual void mouseMotion(int x, int y);
	virtual void mouseWheel(int button, int dir, int x, int y);
	void set_target(std::shared_ptr<Object> target_);
	void set_camera(Camera* camera);
	glm::vec3 get_camera_offset() const { return camera_offset; }
protected:
	std::shared_ptr<Object> target;
	glm::vec3 camera_offset;
	Camera* camera;
};