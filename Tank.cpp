#include "Tank.h"
#include <math.h>
#include "global.h"
#include "Grid.h"

import ObjectLoader;

Tank::Tank()
{
	addGrid();
	meshes = ObjectLoader::Load_Meshes("objs/tank.obj", "Model");
	for (auto& mesh : meshes) {
		mesh->Local_Transform.rotateY(180.f);
	}
	to_yaw = to_pitch = 0.f;
	// 0 - Base
	// 1 - Right Track
	// 2 - Turret
	// 3 - Gun
	// 4 - Gun Holder
	// 5 - Right Track
	meshes[0]->Color = new glm::vec4(colorPalette[27]);
	meshes[1]->Color = new glm::vec4(BlackColor);
	meshes[2]->Color = new glm::vec4(colorPalette[19]);
	meshes[3]->Color = new glm::vec4(colorPalette[11]);
	meshes[4]->Color = new glm::vec4(colorPalette[38]);
	meshes[5]->Color = new glm::vec4(BlackColor);

	Backward = Forward = false;
}

void Tank::update(float frameTime)
{
	movement();
	turret_rotation();
	Object::update(frameTime);


}

void Tank::move_F()
{
	Forward = !Forward;
}

void Tank::move_B()
{
	Backward = !Backward;
}

void Tank::rt_Y()
{
	move.add_rt_direction(0.f, 1.f, 0.f);
	for (int i = 2; i < 5; ++i) {
		meshes[i]->move->add_rt_direction(0.f, -1.f, 0.f);
	}
}

void Tank::rt_Y_R()
{
	move.add_rt_direction(0.f, -1.f, 0.f);
	for (int i = 2; i < 5; ++i) {
		meshes[i]->move->add_rt_direction(0.f, 1.f, 0.f);
	}
}

void Tank::set_Angle(const glm::vec3& dir)
{

}

void Tank::set_Camera(const Camera* camera_)
{
	camera = camera_;
}

void Tank::movement()
{
	glm::vec3 FVector(0.f);
	if (Forward) FVector += World_Transform.get_Forward_vector();
	if (Backward) FVector -= World_Transform.get_Forward_vector();
	move.set_direction(FVector.x, FVector.y, FVector.z);
}

void Tank::turret_rotation()
{
	glm::vec3 dir = camera->getForwardVector();
	to_yaw = glm::degrees(atan2(dir.z, dir.x));
	//to_pitch = glm::degrees(asin(dir.y)); 주포 위 아래 회전
	float t_yaw = meshes[2]->Local_Transform.getYaw();
	yaw_diff = to_yaw - t_yaw;
	if (yaw_diff > 180.0f) yaw_diff -= 360.0f;
	if (yaw_diff < -180.0f) yaw_diff += 360.0f;
	if (-1.0f <= yaw_diff && yaw_diff <= 1.0f) {
		for (int i = 2; i < 5; ++i) {
			meshes[i]->Local_Transform.rotateY(-yaw_diff);
		}
	}
	else {
		for (int i = 2; i < 5; ++i) {
			meshes[i]->Local_Transform.rotateY(-yaw_diff * turret_speed);
		}
	}
}



