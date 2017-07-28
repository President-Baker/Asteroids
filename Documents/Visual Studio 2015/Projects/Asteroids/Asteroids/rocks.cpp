#include "rocks.h"

/****************
* BIG ROCK
*****************/
void LargeAsteroid::draw()
{
	drawLargeAsteroid(position, spin);
}

void LargeAsteroid::advance()
{
	FlyingObject::advance();
	spin += BIG_ROCK_SPIN;
	
}

void LargeAsteroid::breakRocks(std::vector<Rocks*> & rocks, std::vector<Rocks*> & stones, int index)
{
	
	Point pt = stones[index]->getPoint();
	Velocity vel = stones[index]->getVelocity();
	Point pt1 = stones[index]->getPoint();
	Velocity vel1 = stones[index]->getVelocity();
	Point pt2 = stones[index]->getPoint();
	Velocity vel2 = stones[index]->getVelocity();

	vel.setDy(vel.getDy() + 1);
	vel1.setDy(vel1.getDy() - 1);
	vel2.setDx(vel2.getDx() + 2);
	

	Rocks* med1 = new MediumAsteroid(pt, vel);
	Rocks* med2 = new MediumAsteroid(pt1, vel1);
	Rocks* smol = new SmolAsteroid(pt2, vel2);

	rocks.push_back(med1);
	rocks.push_back(med2);
	rocks.push_back(smol);

}

/****************
* MEDIUM ROCK
*****************/
void MediumAsteroid::draw()
{
	drawMediumAsteroid(position, spin);
}

void MediumAsteroid::advance()
{
	FlyingObject::advance();
	spin += MEDIUM_ROCK_SPIN;

}

void MediumAsteroid::breakRocks(std::vector<Rocks*> & rocks, std::vector<Rocks*> & stones, int index)
{
	Point pt = stones[index]->getPoint();
	Velocity vel = stones[index]->getVelocity();
	Point pt1 = stones[index]->getPoint();
	Velocity vel1 = stones[index]->getVelocity();

	vel.setDx(vel.getDx() + 3);
	vel1.setDx(vel1.getDx() - 3);
	

	Rocks* smol1 = new SmolAsteroid(pt, vel);
	Rocks* smol2 = new SmolAsteroid(pt1, vel1);

	rocks.push_back(smol1);
	rocks.push_back(smol2);

}


/****************
* SMALL ROCK
*****************/
void SmolAsteroid::draw()
{
	drawSmallAsteroid(position, spin);
}

void SmolAsteroid::advance()
{
	FlyingObject::advance();
	spin += SMALL_ROCK_SPIN;

}