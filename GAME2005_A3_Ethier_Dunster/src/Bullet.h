#pragma once
#ifndef __BULLET__
#define __BULLET__
#include "PlayerAnimationState.h"
#include "Sprite.h"

class Bullet final : public Sprite
{
public:
	Bullet();
	~Bullet();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setIsActive(bool active);

	void setInitVelocity(float val);

	void setPosition(glm::vec2 pos);

	void setCollided(bool val);

	// getters
	bool getIsActive();
	
	glm::vec2 getPosition();

	int getInitVelocity();

	bool getCollided();

	void init();
	
	void reset();
private:

	bool isCollided = false;;
	
	float initVelocity;

	bool isActive;

	int frameCount;
	
};

#endif /* defined (__BULLET__) */