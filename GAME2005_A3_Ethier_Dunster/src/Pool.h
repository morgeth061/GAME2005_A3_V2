#pragma once
#ifndef __POOL__
#define __POOL__

#include <string>
#include <iostream>
#include <list>
#include "Bullet.h"

class Pool
{
public:
	static Pool* Instance();
	
	Bullet* getBullet();

	void returnBullet(Bullet* bulletObj);

	int getNumBulletsActive();

private:
	std::list<Bullet*> bulletVec;

	static Pool* instance;

	int numBullets;

	int numBulletsActive = 0;

	Pool()
	{
		numBullets = 0;
	}
};

#endif /* defined (__POOL__)*/