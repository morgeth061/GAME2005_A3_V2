#include "Ball.h"

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/Textures/circle.png", "circle");
	TextureManager::Instance()->load("../Assets/Textures/square.png", "square");
	TextureManager::Instance()->load("../Assets/Textures/triangle.png", "triangle");

	setWidth(16);
	setHeight(16);
	
	position = glm::vec2(392, 150);
	velocity = glm::vec2(0, 0);
	acceleration = glm::vec2(0, 0.00931);
}

Ball::~Ball()
= default;

void Ball::draw()
{
	//alias for x and y
	const auto x = position.x;
	const auto y = position.y;

	if (shapeID == 1)
	{
		TextureManager::Instance()->draw("circle", x, y);
	}
	else if (shapeID == 2)
	{
		TextureManager::Instance()->draw("square", x, y);
	}
	else if (shapeID == 3)
	{
		TextureManager::Instance()->draw("triangle", x, y);
	}
	else
	{
		TextureManager::Instance()->draw("circle", x, y);
	}
	
}

void Ball::update()
{
	position = position + velocity;

	velocity = velocity + acceleration;

	//Walls

	if (position.x <= 0)
	{
		std::cout << "LEFT" << std::endl;
		position.x = 1;
		if (velocity.x < 0)
		{
			velocity.x = velocity.x * -0.9;
		}
	}
	if (position.x >= 784)
	{
		std::cout << "RIGHT" << std::endl;
		position.x = 783;
		if (velocity.x > 0)
		{
			velocity.x = velocity.x * -0.9;
		}
	}
	if (position.y <= 0)
	{
		std::cout << "TOP" << std::endl;
		position.y = 1;

		if (velocity.y < 0)
		{
			velocity.y = velocity.y * -0.9;
		}
	}
	if (position.y >= 784)
	{
		std::cout << "BOTTOM" << std::endl;
		position.y = 783;
		
		if(velocity.y > 0)
		{
			velocity.y = velocity.y * -0.9;
		}
	}

	//std::cout << velocity.y << std::endl;
	getTransform()->position = position;
}

void Ball::clean()
{
}

void Ball::setPosition(glm::vec2 pos)
{
	position = pos;
}

void Ball::setVelocity(glm::vec2 vel)
{
	velocity = vel;
}

void Ball::setAngle(float angle)
{
	angleDeg = angle;
}

glm::vec2 Ball::getPosition()
{
	return position;
}

glm::vec2 Ball::getVelocity()
{
	return velocity;
}

float Ball::getAngle()
{
	return angleDeg;
}

void Ball::changeShape(int shape)
{
	shapeID = shape;
}
