#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("PHYSICS SIMULATOR", "Consolas", 65, {255, 0, 0, 255}, glm::vec2(400.0f, 100.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	/*m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel); */

	/* Instructions Label */
	m_pMorganLabel = new Label("Morgan Ethier: #101230557", "Consolas");
	m_pMorganLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 300.0f);

	addChild(m_pMorganLabel);

	/* Instructions Label */
	m_pLucasLabel = new Label("Lucas Dunster: #101230948", "Consolas");
	m_pLucasLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 350.0f);

	addChild(m_pLucasLabel);

	/* Instructions Label */
	m_pSim1Label = new Label("Simulation 1: Ship", "Consolas");
	m_pSim1Label->getTransform()->position = glm::vec2(250, 450.0f);

	addChild(m_pSim1Label);

	/* Instructions Label */
	m_pSim2Label = new Label("Simulation 2: Shape", "Consolas");
	m_pSim2Label->getTransform()->position = glm::vec2(550, 450.0f);

	addChild(m_pSim2Label);

	// Sim 1 Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(250.0f, 500.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	// Sim 2 Start Button
	m_pStartButton2 = new Button();
	m_pStartButton2->getTransform()->position = glm::vec2(550.0f, 500.0f);

	m_pStartButton2->addEventListener(CLICK, [&]()-> void
		{
			m_pStartButton2->setActive(false);
			TheGame::Instance()->changeSceneState(SIM2_SCENE);
		});

	m_pStartButton2->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pStartButton2->setAlpha(128);
		});

	m_pStartButton2->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pStartButton2->setAlpha(255);
		});
	addChild(m_pStartButton2);

	
}

