#ifndef SCENE_H
#define SCENE_H

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
	virtual void KeyUp(unsigned char key, int x, int y);
	virtual void KeyDown(unsigned char key, int x, int y);
	virtual void mouseMotion(int x, int y);
	virtual void mouseWheel(int button, int dir, int x, int y);

	const glm::vec4& getBG() const { return bgColor; }
	const std::vector<std::shared_ptr<Object>>& getObjects() const;
	const std::vector<std::shared_ptr<Static_Object>>& getStaticObjects() const;

	bool showMouse;
protected:
	virtual void update(float frameTime);
	void add_Object(const std::string& fileName, const std::string& shaderName);
	void add_Static_Object(const std::string& fileName, const std::string& shaderName);
	
	void add_Cube(bool Static);
	void add_Sphere(bool Static);
	void add_Cylinder(bool Static);
	void add_Pyramid(bool Static);
	void add_Rpyramid(bool Static);
	void add_Monkey(bool Static);

	void setUp(std::shared_ptr<Object> obj);
	void setUp(std::shared_ptr<Static_Object> obj);
private:
	
protected:
	bool cull, fill, depth;
	int lastX, lastY;
	std::vector<std::shared_ptr<Object>> objs;
	std::vector<std::shared_ptr<Static_Object>> static_objs;
	std::shared_ptr<PlayerController> pc;
	glm::vec4 bgColor;
	Camera camera;
};
#endif

