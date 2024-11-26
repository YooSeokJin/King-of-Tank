#pragma once
#include "Object.h"
class Crane : public Object {
public:
	Crane();
	void update(float frameTime) override;

	void move_F();
	void move_B();
	void rt_Y();
	void rt_Y_R();
private:
	bool Forward;
	bool Backward;
};

