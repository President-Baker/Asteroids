#include "ship.h"

void Ship::draw()
{
	drawShip(position, angle, thrust);
}

void Ship::turnLeft()
{
	angle += ROTATE_AMOUNT;
}

void Ship::turnRight()
{
	angle -= ROTATE_AMOUNT;
}

void Ship::thrustaroo()
{
	aDY += THRUST_AMOUNT * (cos(M_PI / 180.0 * angle));
	aDX += THRUST_AMOUNT * (-sin(M_PI / 180.0 * angle));
	velocity.setDx(aDX);
	velocity.setDy(aDY);
}

void Ship::advance()
{
	FlyingObject::advance();
}
