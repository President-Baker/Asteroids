#ifndef flyingObject_h
#define flyingObject_h

#include "velocity.h"
#include "point.h"

class FlyingObject
{
protected:
	Velocity velocity;
	Point position;
	bool alive;

public:
	FlyingObject() : alive(true) {};
	~FlyingObject();

	Velocity getVelocity() const { return velocity; }
	void setVelocity(Velocity velocity) { this->velocity = velocity; }

	Point getPoint() const { return position; }
	void setPoint(Point position) { this->position = position; }

	bool isAlive() { return alive; }
	void kill() { alive = false; }

	virtual void advance();
	virtual void draw() = 0;
};


#endif /* flyingObject_h */
