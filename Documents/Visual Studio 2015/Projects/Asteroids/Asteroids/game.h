/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <list>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"

#define CLOSE_ENOUGH 15
#define INITIAL_ASTEROIDS 5

class Game
{
public:
	Game(Point tl, Point br, Point ss, Velocity vs);

	void handleInput(const Interface & ui);
	void draw(const Interface & ui);
	void advance();

private:
	Point topLeft;
	Point bottomRight;

	Ship* sip;

	std::vector<Rocks*> asteroids;
	std::vector<Bullet> bullets;

	void rap();
	bool isOnScreen(const Point & point);
	void cleanUpZombies();
	void advanceBullets();
	void advanceAsteroids();
	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
	void handleCollisions();
};