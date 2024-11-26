#pragma once
#include "Object.h"
class Crane : public Object {
public:
	Crane();
	void update(float frame_time) override;

	void move_F();
	void move_B();
	void rt_Y();
	void rt_Y_R();
private:

};

