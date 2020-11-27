#include "Brick.h"

Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/Textures/brick.png", "brick");

	setWidth(128);
	setHeight(16);
	
	currentPosition = glm::vec2(400.0f, 400.0f);
	lastPosition = currentPosition;
	angleDeg = 0;
	brickVelocity = glm::vec2(0.0f, 0.0f);
}

Brick::~Brick()
= default;

void Brick::draw()
{
	//alias for x and y
	const auto x = currentPosition.x;
	const auto y = currentPosition.y;

	TextureManager::Instance()->draw("brick", x, y);
}

void Brick::update()
{
	brickVelocity = glm::vec2((currentPosition.x - lastPosition.x) / 60, (currentPosition.y - lastPosition.y) / 60);

	//Determining Angle
	if (currentPosition.x > lastPosition.x && currentPosition.y < lastPosition.y)
	{
		//0 to 90
		angleDeg = (3141 / 180) * tan((currentPosition.y - lastPosition.y) / (currentPosition.x - lastPosition.x));
	}
	else if (currentPosition.x < lastPosition.x && currentPosition.y < lastPosition.y)
	{
		//90 to 180
		angleDeg = 180 - (3141 / 180) * tan((currentPosition.y - lastPosition.y) / (currentPosition.x - lastPosition.x));
	}
	else if (currentPosition.x < lastPosition.x && currentPosition.y > lastPosition.y)
	{
		//180 to 270
		angleDeg = 180 + (3141 / 180) * tan((currentPosition.y - lastPosition.y) / (currentPosition.x - lastPosition.x));
	}
	else if (currentPosition.x > lastPosition.x && currentPosition.y > lastPosition.y)
	{
		//270 to 360
		angleDeg = 360 - (3141 / 180) * tan((currentPosition.y - lastPosition.y) / (currentPosition.x - lastPosition.x));
	}
	else if (currentPosition.x > lastPosition.x && currentPosition.y == lastPosition.y)
	{
		//0
		angleDeg = 0;

	}
	else if (currentPosition.x == lastPosition.x && currentPosition.y < lastPosition.y)
	{
		//90
		angleDeg = 90;
	}
	else if (currentPosition.x < lastPosition.x && currentPosition.y == lastPosition.y)
	{
		//180
		angleDeg = 180;
	}
	else if (currentPosition.x == lastPosition.x && currentPosition.y > lastPosition.y)
	{
		//270
		angleDeg = 270;
	}

	std::cout << brickVelocity.x << " " << brickVelocity.y << std::endl;
	
	getTransform()->position = currentPosition;
}

void Brick::clean()
{
}

void Brick::setPosition(glm::vec2 pos)
{
	lastPosition = currentPosition;
	currentPosition = pos;
}

glm::vec2 Brick::getPosition()
{
	return currentPosition;
}

glm::vec2 Brick::getVelocity()
{
	return brickVelocity;
}

float Brick::getAngle()
{
	return angleDeg;
}
