/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 7.5

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

void Game::handleCollisions()
{
	vector<Rocks*> tempRocks;

	vector<Rocks*>::iterator it = asteroids.begin();
	int count = 0;

	while (it != asteroids.end())
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())
			{
				switch ((*it)->getRadius())
				{
				case 16:
					if (getClosestDistance(*(*it), bullets[i]) < (*it)->getRadius())
					{
						bullets[i].kill();
						(*it)->breakRocks(tempRocks, asteroids, count);
						(*it)->kill();
					}
					break;
				case 8:
					if (getClosestDistance(*(*it), bullets[i]) < (*it)->getRadius())
					{
						bullets[i].kill();
						(*it)->breakRocks(tempRocks, asteroids, count);
						(*it)->kill();
					}
					break;
				case 4:
					if (getClosestDistance(*(*it), bullets[i]) < (*it)->getRadius())
					{
						bullets[i].kill();
						(*it)->kill();
					}
					break;
				}
			}
		}
		it++;
		count++;
	}

	for (int i = 0; i < tempRocks.size(); i++)
	{
		asteroids.push_back(tempRocks[i]);
	}

	for (int i = 0; i < asteroids.size(); i ++)
	{
		if (asteroids[i]->isAlive())
		{
			if (getClosestDistance(*sip, *asteroids[i]) <= asteroids[i]->getRadius())
			{
				sip->kill();
			}
		}
	}
}


Game::Game(Point tl, Point br, Point ss, Velocity vs)
{
	for (int i = 0; i < INITIAL_ASTEROIDS; i++)
	{
		Rocks* newAst = NULL;

		Point randomStart;
		randomStart.setX(random(tl.getX(), br.getX()));
		randomStart.setY(random(br.getY(), tl.getY()));

		float randX = (random(1, 11) > 5) ? 1 : -1;
		float randY = (random(1, 11) > 5) ? 1 : -1;

		Velocity randomVel;
		randomVel.setDx(randX);
		randomVel.setDy(randY);

		newAst = new LargeAsteroid(randomStart, randomVel);

		asteroids.push_back(newAst);
	}

	Ship* ship = new Ship(ss, vs);
	sip = ship;
}

void Game::rap()
{
	for (vector<Rocks*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->advance();

			if (!isOnScreen((*it)->getPoint()))
			{
				Point negPt = (*it)->getPoint();
				if (negPt.getX() > 207.0 || negPt.getX() < -207.0)
				{
					negPt.setX(negPt.getX() * -1);
				}

				if (negPt.getY() > 207.0 || negPt.getY() < -207.0)
				{
					negPt.setY(negPt.getY() * -1);
				}

				(*it)->setPoint(negPt);
			}
		}
	}

	for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{
		if (it->isAlive())
		{
			if (!isOnScreen(it->getPoint()))
			{
				Point negPt = it->getPoint();
				if (negPt.getX() > 205.0 || negPt.getX() < -205.0)
				{
					negPt.setX(negPt.getX() * -1);
				}

				if (negPt.getY() > 205.0 || negPt.getY() < -205.0)
				{
					negPt.setY(negPt.getY() * -1);
				}

				it->setPoint(negPt);
			}
		}
	}

	if (!isOnScreen(sip->getPoint()))
	{
		Point negPt = sip->getPoint();
		if (negPt.getX() > 205.0 || negPt.getX() < -205.0)
		{
			negPt.setX(negPt.getX() * -1);
		}

		if (negPt.getY() > 205.0 || negPt.getY() < -205.0)
		{
			negPt.setY(negPt.getY() * -1);
		}

		sip->setPoint(negPt);
	}

}

bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

void Game::cleanUpZombies()
{
	for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
	{
		if (it->isAlive())
		{
			if (it->getTime() > 40)
				it = bullets.erase(it);
			else
				it++;
		}
		else if (!it->isAlive())
		{
			it = bullets.erase(it);
		}
	}

	for (vector<Rocks*>::iterator it = asteroids.begin(); it != asteroids.end();)
	{
		if (!(*it)->isAlive())
		{
			delete (*it);
			(*it) = NULL;

			it = asteroids.erase(it);
		}
		else
			it++;
	}
}


void Game::advanceBullets()
{
	for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{
		it->advance();
	}

}

void Game::advanceAsteroids()
{
	for (vector<Rocks*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->advance();
		}
	}
}

void Game::advance()
{
	advanceBullets();
	advanceAsteroids();
	rap();
	handleCollisions();
	cleanUpZombies();

	if (!sip->isAlive())
	{
		drawText(topLeft, "Game Over");
	}
	else if (asteroids.size() == 0)
	{
		drawText(topLeft, "You Win!");
	}

}

void Game::handleInput(const Interface & ui)
{
	if (ui.isUp() && sip->isAlive())
	{
		sip->thrustaroo();
		sip->advance();
		sip->setThrust(true);
	}
	else if (ui.isLeft() && sip->isAlive())
	{
		sip->turnLeft();
		sip->advance();
		sip->setThrust(false);
	}
	else if (ui.isRight() && sip->isAlive())
	{
		sip->turnRight();
		sip->advance();
		sip->setThrust(false);
	}
	else
	{
		sip->advance();
		sip->setThrust(false);
	}
		
	if (ui.isSpace() && sip->isAlive())
	{
		Bullet newBullet = Bullet();

		newBullet.fire(sip->getPoint(), sip->getAngle(), sip->getVelocity());

		bullets.push_back(newBullet);
	}
}

void Game::draw(const Interface & ui)
{
	for (vector<Rocks*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->draw();
		}
	}

	for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{
		if (it->isAlive())
		{
			it->draw();
		}
	}

	if (sip->isAlive())
	{
		sip->draw();
	}
}
