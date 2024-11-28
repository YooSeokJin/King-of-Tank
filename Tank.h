#pragma once
#include "Object.h"
#include "Camera.h"
class Tank : public Object {
public:
	Tank();
	void update(float frameTime) override;

	void move_F();
	void move_B();
	void rt_Y();
	void rt_Y_R();

	void set_Angle(const glm::vec3& dir);
	void set_Camera(const Camera* camera);
	const Camera* camera = nullptr;
private:
	void movement();
	void turret_rotation();
private:
	bool Forward;
	bool Backward;

	// 터렛 회전에 사용
	float to_yaw;
	float yaw_diff =0.f;
	// 포탑 회전에 사용
	float to_pitch;

	float turret_speed = 0.01f;
};

