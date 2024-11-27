#pragma once
#include "Object.h"
class Tank : public Object {
public:
	Tank();
	void update(float frameTime) override;

	void move_F();
	void move_B();
	void rt_Y();
	void rt_Y_R();
private:
	bool Forward;
	bool Backward;
};

