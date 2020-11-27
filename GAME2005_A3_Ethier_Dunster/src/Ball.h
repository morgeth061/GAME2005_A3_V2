#pragma once
#ifndef __BALL__
#define __BALL__

#define WIDTH = 800;
#define HEIGHT = 800;

#include "Sprite.h"
#include "TextureManager.h"

class Ball final : public Sprite
{
public:
	Ball();
	~Ball();

	//Life Cycle
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//Setters
	void setPosition(glm::vec2 pos);
	void setVelocity(glm::vec2 vel);
	void setAngle(float angle);

	//Getters
	glm::vec2 getPosition();
	glm::vec2 getVelocity();
	float getAngle();

	//Methods
	void changeShape(int shape);

private:
	float angleDeg;

	int shapeID = 1;

	glm::vec2 position;

	glm::vec2 velocity;
	
	glm::vec2 acceleration;
};

#endif /* Defined (__BALL__) */