#include "bullet.h"

Bullet::Bullet()
{
	alive = true;
	time = 0;
}

void Bullet::draw()
{
	drawDot(position);
}

void Bullet::fire(Point position, float angle, Velocity vel)
{
	this->position = position;
	aDY = vel.getDy();
	aDX = vel.getDx();

	aDY += BULLET_SPEED * (cos(M_PI / 180.0 * angle));
	aDX += BULLET_SPEED * (-sin(M_PI / 180.0 * angle));
	velocity.setDx(aDX);
	velocity.setDy(aDY);
	FlyingObject::advance();
}

void Bullet::advance()
{
	FlyingObject::advance();
	time++;
}