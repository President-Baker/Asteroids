#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "flyingObject.h"
#include <iostream>
#include "uiInteract.h"
#include "uiDraw.h"

#define BULLET_SPEED 10.0

class Bullet : public FlyingObject
{
	float aDX;
	float aDY;
	int time;

public:
	Bullet();

	void draw();
	void fire(Point position, float angle, Velocity vel);
	int getTime() { return time; }
	virtual void advance();
};