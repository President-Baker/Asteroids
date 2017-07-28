#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "uiDraw.h"
#include <vector>

//   Rock
class Rocks : public FlyingObject
{
protected:
	int spin;
	int radius;

public:
	Rocks() {}

	virtual void draw() = 0;
	virtual int getRadius() { return radius; }
	virtual void breakRocks(std::vector<Rocks*> & rocks, std::vector<Rocks*> & stones, int index) {}
};


//   BigRock
class LargeAsteroid : public Rocks
{
private:
	
public:
	LargeAsteroid(Point position, Velocity velocity)
	{
		radius = BIG_ROCK_SIZE;
		alive = true;
		spin = BIG_ROCK_SPIN;
		this->position = position;
		this->velocity = velocity;
	}

	virtual void draw();
	virtual void advance();
	virtual void breakRocks(std::vector<Rocks*> & rocks, std::vector<Rocks*> & stones, int index);
};


//   MediumRock
class MediumAsteroid : public Rocks
{
private:

public:
	MediumAsteroid(Point position, Velocity velocity)
	{
		radius = MEDIUM_ROCK_SIZE;
		alive = true;
		spin = MEDIUM_ROCK_SPIN;
		this->position = position;
		this->velocity = velocity;
	}

	virtual void draw();
	virtual void advance();
	virtual void breakRocks(std::vector<Rocks*> & rocks, std::vector<Rocks*> & stones, int index);
};


//   SmallRock
class SmolAsteroid : public Rocks
{
private:

public:
	SmolAsteroid(Point position, Velocity velocity)
	{
		radius = SMALL_ROCK_SIZE;
		alive = true;
		spin = SMALL_ROCK_SPIN;
		this->position = position;
		this->velocity = velocity;
	}

	virtual void draw();
	virtual void advance();
};


#endif /* rocks_h */
