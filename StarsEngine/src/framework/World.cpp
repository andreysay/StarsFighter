/*
*  World.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "framework/World.hpp"
#include "framework/Core.hpp"
#include "framework/GameBaseApp.hpp"


namespace SF
{
	//--------------------------------------------------------------------------------------------------------
    World::World(const GameBaseApp& OwningApp)
    : WorldOwningApp{OwningApp}
		, Actors{}
		, PendingActors{}
    {

    }
	//--------------------------------------------------------------------------------------------------------
    void World::BeginPlayInternal()
    {
        if(!bBeginPlay)
        {
            bBeginPlay = true;
            BeginPlay();
        }
    }
	//--------------------------------------------------------------------------------------------------------
    void World::TickInternal(float DeltaTime)
    {
		for (auto& NewActor : PendingActors)
		{
            NewActor->BeginPlayInternal();
			Actors.push_back(NewActor);
		}

		PendingActors.clear();

        for (auto ActorIterator = Actors.begin(); ActorIterator != Actors.end();)
        {
			if (ActorIterator->get()->IsPendingDestroy())
			{
				ActorIterator = Actors.erase(ActorIterator);
			}
			else
			{
				ActorIterator->get()->TickIntelrnal(DeltaTime);
				++ActorIterator;
			}
        }
        Tick(DeltaTime);
    }
	//--------------------------------------------------------------------------------------------------------
    void World::Render(sf::RenderWindow& Window)
    {
        for (auto& AActor : Actors)
        {
			AActor->Render(Window);
        }
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return WorldOwningApp.GetWindowSize();
    }
	//--------------------------------------------------------------------------------------------------------
    void World::BeginPlay()
    {

    }
	//--------------------------------------------------------------------------------------------------------
    void World::Tick(float DeltaTime)
    {
		//std::string Message = "World is ticking at framerate: " + std::to_string(1.f / DeltaTime);
        //Helpers::WriteLog(GLog, Helpers::LogLevel::Info, Message);
    }
}
