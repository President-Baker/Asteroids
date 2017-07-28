#include "flyingObject.h"

FlyingObject::~FlyingObject()
{

}

void FlyingObject::advance()
{
	position.addX(velocity.getDx());
	position.addY(velocity.getDy());
}