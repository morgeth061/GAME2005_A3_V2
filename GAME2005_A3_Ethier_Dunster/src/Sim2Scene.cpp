#include "Sim2Scene.h"
#include "Game.h"
#include "EventManager.h"

//imgui
#include "imgui.h"
#include "imgui_sdl.h"


Sim2Scene::Sim2Scene()
{
	Sim2Scene::start();
}

Sim2Scene::~Sim2Scene()
= default;

void Sim2Scene::draw()
{
	GUI_Function();
	
	drawDisplayList();
	
	//******************************
	//Background Colour
	//******************************
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 0, 0, 0, 255);
}

void Sim2Scene::update()
{
	updateDisplayList();

	m_pBrick->setPosition(glm::vec2(mousePosX - 64, mousePosY - 8));

	if(CollisionManager::AABBCheck(m_pBall, m_pBrick))
	{
		std::cout << "COLLIDE" << std::endl;

		if(m_pBrick->getVelocity().x == 0 && m_pBrick->getVelocity().y == 0 || m_pBall->getVelocity().y > m_pBrick->getVelocity().y)
		{
			m_pBall->setVelocity(glm::vec2(m_pBall->getVelocity().x, m_pBall->getVelocity().y * -1));
		}
		else
		{
			m_pBall->setVelocity(glm::vec2(m_pBrick->getVelocity().x * 10, m_pBrick->getVelocity().y * 10));
		}
	}
}

void Sim2Scene::clean()
{
	removeAllChildren();
}

void Sim2Scene::handleEvents()
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
	//Brick Movement
	//******************************
	

	SDL_GetMouseState(&mousePosX, &mousePosY);

	
	//std::cout << m_pBrick->getAngle() << std::endl;

	
}

void Sim2Scene::start()
{
	//Brick
	m_pBrick = new Brick();
	addChild(m_pBrick);

	m_pBall = new Ball();
	addChild(m_pBall);
	
}

void Sim2Scene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Shape", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Circle"))
	{
		std::cout << "Circle" << std::endl;
		m_pBall->changeShape(1);
	}

	if (ImGui::Button("Square"))
	{
		std::cout << "Square" << std::endl;
		m_pBall->changeShape(2);
	}

	if (ImGui::Button("Triangle"))
	{
		std::cout << "Triangle" << std::endl;
		m_pBall->changeShape(3);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
