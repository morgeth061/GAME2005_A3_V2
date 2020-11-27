#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Bullet.h"
#include "Button.h"
#include "Label.h"
#include "Ramp.h"

#include "Pool.h"

#include "CollisionManager.h"
#include "SoundManager.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Player* m_pPlayer;
	Ramp* m_pRamp;
	bool m_playerFacingRight;

	// Bullet
	Bullet* bulletPoolVec[10];
	int bulletSpawnTimer = 0;
	bool bulletDespawned = false;
	bool respawnEnabled = false;
	float m_pRampAngle = 36.0f;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Button* m_pPlayButton;
	Label* m_pInstructionsLabel;

	//Pool
	Pool* bulletPool = Pool::Instance();

	
};

#endif /* defined (__PLAY_SCENE__) */