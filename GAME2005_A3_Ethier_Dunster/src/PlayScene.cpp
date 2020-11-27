#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include <ctime>

#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	//******************************
	//Display List
	//******************************
	drawDisplayList();

	//******************************
	//Player
	//******************************
	m_pPlayer->draw();

	//******************************
	//Bullets
	//******************************
	for (int i = 0; i < 10; i++)
	{
		if (bulletPoolVec[i] != NULL)
		{
			bulletPoolVec[i]->draw();
		}
	}

	//******************************
	//Background Colour
	//******************************
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 0, 0, 0, 255);
}

void PlayScene::update()
{
	//******************************
	//Display List
	//******************************
	updateDisplayList();

	//******************************
	//Player
	//******************************
	m_pPlayer->update();


	//******************************
	//Bullets
	//******************************
	bulletSpawnTimer++;

	//***************
	//Spawn Bullets
	//***************
	if (bulletSpawnTimer >= 80 || bulletDespawned == true || (bulletPool->getNumBulletsActive() < 10 && respawnEnabled))
	{
		if(bulletDespawned == true)
		{
			bulletDespawned = false;
		}
		
		Bullet* tempBullet = bulletPool->getBullet();

		if (tempBullet != NULL)
		{
			bulletSpawnTimer = 0;
			bool isAdded = false;
			for(int i = 0; i < 10; i++)
			{
				if (bulletPoolVec[i] == nullptr && isAdded == false)
				{
					bulletPoolVec[i] = tempBullet;
					//addChild(bulletPoolVec[i]);
					bulletPoolVec[i]->init();
					isAdded = true;
				}
			}
		}
	}
	
	//**********************
	//Update/Despawn Bullets
	//**********************
	for(int i = 0; i < 10; i++)
	{
		if (bulletPoolVec[i] != NULL)
		{

			bulletPoolVec[i]->update();
			
			if(bulletPoolVec[i]->getPosition().y > 850)
			{
				bulletPoolVec[i]->reset();
				//removeChild(bulletPoolVec[i]);
				bulletPool->returnBullet(bulletPoolVec[i]);
				bulletPoolVec[i] = NULL;
				bulletDespawned = true;
				respawnEnabled = true;
			}
		}
	}

	//******************************
	//Collision
	//******************************
	for (int i = 0; i < 10; i++)
	{
		if (bulletPoolVec[i] != NULL)
		{
			if (CollisionManager::AABBCheck(m_pPlayer, bulletPoolVec[i]) == 1)
			{
				if(bulletPoolVec[i]->getCollided() == false)
				{
					SoundManager::Instance().playSound("Explosion");
					bulletPoolVec[i]->setCollided(true);
				}
				
			}
		}
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	//******************************
	//Ship Movement
	//******************************


	//***************
	//Mouse
	//***************
	int mousePosX = 0;
	int mousePosY = 0;

	SDL_GetMouseState(&mousePosX, &mousePosY);

	m_pPlayer->setPosition(glm::vec2(mousePosX - 32, mousePosY - 32));

	//***************
	//KeyDown
	//***************
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		std::cout << "UP" << std::endl;
		m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, -1));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, 0));
		}
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		std::cout << "LEFT" << std::endl;
		m_pPlayer->setVelocity(glm::vec2(-1, m_pPlayer->getVelocity().y));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));
		}
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		std::cout << "DOWN" << std::endl;
		m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, 1));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, 0));
		}
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		std::cout << "RIGHT" << std::endl;
		m_pPlayer->setVelocity(glm::vec2(1, m_pPlayer->getVelocity().y));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));
		}
	}

	//***************
	//KeyUp
	//***************
	if(EventManager::Instance().isKeyUp(SDL_SCANCODE_W))
	{
		m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, 0));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, 1));
		}
	}

	if(EventManager::Instance().isKeyUp(SDL_SCANCODE_A))
	{
		m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setVelocity(glm::vec2(1, m_pPlayer->getVelocity().y));
		}
	}

	if(EventManager::Instance().isKeyUp(SDL_SCANCODE_S))
	{
		m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, 0));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x, -1));
		}
	}

	if(EventManager::Instance().isKeyUp(SDL_SCANCODE_D))
	{
		m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setVelocity(glm::vec2(-1, m_pPlayer->getVelocity().y));
		}
	}
	
}

void PlayScene::start()
{
	//******************************
	//IMGUI
	//******************************
	m_guiTitle = "Play Scene";

	//******************************
	//Random Seed
	//******************************
	srand(time(NULL));

	//******************************
	//Import
	//******************************
	//Sound
	SoundManager::Instance().load("../Assets/audio/Explosion.wav", "Explosion", SOUND_SFX);

	//******************************
	//Objects
	//******************************
	// Player Sprite
	m_pPlayer = new Player();
	m_pPlayer->reset();
	m_pPlayer->setIsMoving(true);

	//bullet reserve
	for (int i = 0; i < 10; i++)
	{
		Bullet* tempBullet = bulletPool->getBullet();
		bulletPool->returnBullet(tempBullet);
	}
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();	

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Name", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	/*if (ImGui::SliderFloat("Ramp Height", &rampHeight, 1.0f, 10.0f))
	{
	}

	ImGui::Separator();

	if (ImGui::SliderFloat("Ramp Length", &rampLength, 1.0f, 10.0f))
	{
	} */

	//ImGui::Separator();

	if (ImGui::Button("Reset"))
	{
	}

	//ImGui::Separator();

	//ImGui::Text("X position = %f", (m_pPlayer->getPosition().x - 100.0f));
	//ImGui::Text("y position = %f", (675 - m_pPlayer->getPosition().y));

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}