#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet()
{
	

	TextureManager::Instance()->load("../Assets/Textures/bullet.png", "bullet");

	//set width
	setWidth(16);

	//set height
	setHeight(16);

	initVelocity = 0;
	isActive = false;
	frameCount = 0;

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

	setType(BULLET);
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
	//alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("bullet", x, y);
}

void Bullet::update()
{
	if (isActive)
	{
		frameCount++;
		if (frameCount == 4)
		{
			frameCount = 1;
			getTransform()->position.y = getTransform()->position.y + getRigidBody()->velocity.y;
			getRigidBody()->velocity = glm::vec2(0,getRigidBody()->velocity.y + getRigidBody()->acceleration.y);
			//std::cout << getRigidBody()->acceleration.y << std::endl;
		}
	}
}

void Bullet::clean()
{
}

void Bullet::setIsActive(bool active)
{
	isActive = active;
}

void Bullet::setInitVelocity(float val)
{
	initVelocity = val;
}

void Bullet::setPosition(glm::vec2 pos)
{
	getTransform()->position = pos;
}

void Bullet::setCollided(bool val)
{
	isCollided = val;
}

bool Bullet::getIsActive()
{
	return isActive;
}

glm::vec2 Bullet::getPosition()
{
	return getTransform()->position;
}

int Bullet::getInitVelocity()
{
	return initVelocity;
}

bool Bullet::getCollided()
{
	return isCollided;
}

void Bullet::init()
{
	int random = (rand() % 700) + 50;
	getTransform()->position = glm::vec2(random, -16.0f);
	getRigidBody()->velocity = glm::vec2(0, 2);
	getRigidBody()->acceleration = glm::vec2(0, 0.00981);
	isActive = true;
	isCollided = false;
}

void Bullet::reset()
{
	getTransform()->position = glm::vec2(0, 0);
	initVelocity = 0;
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->acceleration = glm::vec2(0, 0);
	isActive = false;
	isCollided = false;
	frameCount = 0;
}
