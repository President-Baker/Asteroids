#ifndef ship_h
#define ship_h
#define _USE_MATH_DEFINES
#include <cmath>
#include "flyingObject.h"
#include "uiDraw.h"

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

class Ship : public FlyingObject
{
private:
	bool thrust;
	int angle;
	float aDX;
	float aDY;

public:
	Ship() {};
	Ship(Point position, Velocity velocity)
	{
		alive = true;
		thrust = false;
		aDY = 0;
		aDX = 0;
		angle = 0;
		this->position = position;
		this->velocity = velocity;
	}

	int getAngle() { return angle; }
	void turnLeft();
	void turnRight();
	void thrustaroo();
	void setThrust(bool thr) { thrust = thr; }
	virtual void draw();
	virtual void advance();
};


#endif /* ship_h */
