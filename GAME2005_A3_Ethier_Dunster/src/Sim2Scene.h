#pragma once

#ifndef __SIM2_SCENE__
#define __SIM2_SCENE__

#include "Scene.h"
#include "Renderer.h"
#include "CollisionManager.h"

#include "Brick.h"
#include "Ball.h"

class Sim2Scene: public Scene
{
public:
	Sim2Scene();
	~Sim2Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	void GUI_Function();
	
	Brick* m_pBrick;
	Ball* m_pBall;

	int mousePosX = 0;
	int mousePosY = 0;
	
};

#endif /* Defined (__SIM2_SCENE__) */
