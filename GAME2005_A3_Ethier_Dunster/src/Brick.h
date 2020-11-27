#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "Sprite.h"
#include "TextureManager.h"
#include <cmath>

class Brick final : public Sprite
{
public:
	Brick();
	~Brick();

	//Life Cycle
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//Setters
	void setPosition(glm::vec2 pos);
	
	//Getters
	glm::vec2 getPosition();
	glm::vec2 getVelocity();
	float getAngle();

	//Methods

private:
	float angleDeg;

	glm::vec2 lastPosition;
	glm::vec2 currentPosition;

	glm::vec2 brickVelocity;
	
};

#endif /* Defined (__BRICK__) */