/*
*  GameBaseApp.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "framework/GameBaseApp.hpp"
#include "framework/AssetManager.hpp"
#include "framework/PhysicsSystem.hpp"
#include "framework/TimerHandler.hpp"

namespace SF
{
//--------------------------------------------------------------------------------------------------------
GameBaseApp::GameBaseApp(Vector2u WinSize, const std::string& Title, std::uint32_t Style)
{
    GameWindow = std::make_unique<RenderWindow>(VideoMode{ WinSize }, std::string{ Title }, Style);
}
//--------------------------------------------------------------------------------------------------------
void GameBaseApp::RunGame()
{
    TickClock.restart();
    float AccumulatedTime = 0.f;
    float TargetDeltaTime = 1.f/TargetFrameRate;

    while (GameWindow->isOpen())
    {
        while (const std::optional Event = GameWindow->pollEvent())
        {
            if(Event->is<sf::Event::Closed>())
            {
                GameWindow->close();
            }
        }
        AccumulatedTime +=TickClock.restart().asSeconds();
        while (AccumulatedTime > TargetDeltaTime)
        {
            AccumulatedTime -= TargetDeltaTime;
            TickInternal(TargetDeltaTime);
            RenderInternal();
        }
    }
}
//--------------------------------------------------------------------------------------------------------
Vector2u GameBaseApp::GetWindowSize() const
{
	return GameWindow.get()->getSize();
}
//--------------------------------------------------------------------------------------------------------
void GameBaseApp::Render()
{
	if (CurrentWorld)
	{
		CurrentWorld->Render(*GameWindow);
	}
}
//--------------------------------------------------------------------------------------------------------
void GameBaseApp::Tick(float DeltaTime)
{

}
//--------------------------------------------------------------------------------------------------------
void GameBaseApp::TickInternal(float DeltaTime)
{
    Tick(DeltaTime);

    if(CurrentWorld)
    {
        CurrentWorld->TickInternal(DeltaTime);
    }

    PhysicsSystem::Get().Step(DeltaTime);
    TimerHandler::Get().UpdateTimer(DeltaTime);

	// Cleanup unused assets
	if (CleanCycleClock.getElapsedTime().asSeconds() > CleanCycleInterval)
	{
		CleanCycleClock.restart();
		AssetManager::Get().CleanCycle();
		TimerHandler::Get().EraseExpiredTimers();
	}
}
//--------------------------------------------------------------------------------------------------------
void GameBaseApp::RenderInternal()
{
    GameWindow->clear();
    Render();
    GameWindow->display();
}

} // End namespace StarsFigher
