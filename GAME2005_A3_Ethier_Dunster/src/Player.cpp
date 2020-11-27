#include "Player.h"
#include "TextureManager.h"

Player::Player()
{

	TextureManager::Instance()->load("../Assets/Textures/Ship.png", "ship");

	// set frame width
	setWidth(64);

	// set frame height
	setHeight(64);

	//angleDegrees = 75; //Angle of initial ascent, in degrees		// Should be equal to ramp angle
	initVelocity = 2; //Initial speed of projectile, in m/s		// Should be 0, and increase as it descends the ramp, then decrease against the floor

	getTransform()->position = glm::vec2(400.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("ship", x, y);
}

void Player::update()
{

	if(isMoving == true)
	{
		frameCount++;
		if (frameCount == 4)
		{
			frameCount = 1;

			std::cout << getRigidBody()->velocity.y << std::endl;
			
			getTransform()->position = getTransform()->position + getRigidBody()->velocity;		

			//getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration;
		}
	}
	
	


}

void Player::clean()
{
}

void Player::setIsMoving(bool moving)
{
	isMoving = moving;
}

void Player::setAngleDegrees(float val)
{
	// Should be used to set angle to angle of ramp then when reaches floor
	if (0 <= val <= 90)
	{
		angleDegrees = val;
	}
}

void Player::setInitVelocity(float val)
{
	if (val >= 0)
	{
		initVelocity = val;
	}
}

void Player::setVelocity(glm::vec2 vel)
{
	getRigidBody()->velocity = vel * initVelocity;
}

void Player::setPosition(glm::vec2 pos)
{
	getTransform()->position = pos;
}

glm::vec2 Player::getPosition()
{
	return getTransform()->position;
}

void Player::setRampLength(float length)
{
	rampLength = length;
}

void Player::setRampHeight(float height)
{
	rampHeight = height;
}

int Player::getAngleDegrees()
{
	return angleDegrees;
}

glm::vec2 Player::getVelocity()
{
	return getRigidBody()->velocity;
}

int Player::getInitVelocity()
{
	return initVelocity;
}

void Player::reset()
{
	getTransform()->position = glm::vec2(400,400);
	getRigidBody()->velocity = glm::vec2(0,0);
	//getRigidBody()->acceleration = glm::vec2(0, 9.8);
}
