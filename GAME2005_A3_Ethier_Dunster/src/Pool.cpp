#include "Pool.h"

Pool* Pool::Instance()
{
	if (instance == 0)
	{
		instance = new Pool;
	}
	return instance;
}

Bullet* Pool::getBullet()
{
	if(bulletVec.empty() || numBullets < 10)
	{
		if (numBullets < 10)
		{
			//std::cout << "Less than 10 bullets exist. creating new bullet." << std::endl;
			numBullets++;
			numBulletsActive++;
			return new Bullet;
		}
		//std::cout << "No bullet available" << std::endl;
		return NULL;
	}
	//std::cout << "Reusing existing" << std::endl;
	Bullet* newBullet = bulletVec.front();
	bulletVec.pop_front();
	numBulletsActive++;
	return newBullet;
}

void Pool::returnBullet(Bullet* bulletObj)
{
	bulletObj->reset();
	bulletVec.push_back(bulletObj);
	numBulletsActive--;
}

int Pool::getNumBulletsActive()
{
	return numBulletsActive;
}

Pool* Pool::instance = 0;
