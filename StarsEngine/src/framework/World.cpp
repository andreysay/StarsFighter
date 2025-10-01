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
#include "gameplay/GameStage.hpp"


namespace SF
{
	//--------------------------------------------------------------------------------------------------------
    World::World(const GameBaseApp& OwningApp)
    : WorldOwningApp{OwningApp}
		, Actors{}
		, PendingActors{}
        , CurrentStageIndex{-1}
        , GameStages{}
    {

    }
	//--------------------------------------------------------------------------------------------------------
    void World::BeginPlayInternal()
    {
        if(!bBeginPlay)
        {
            bBeginPlay = true;
            BeginPlay();
            InitGameStages();
            NextGameStage();
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
			ActorIterator->get()->TickIntelrnal(DeltaTime);
			++ActorIterator;
        }

        if (CurrentStageIndex >= 0 && CurrentStageIndex < GameStages.size())
        {
            GameStages[CurrentStageIndex]->TickStage(DeltaTime);
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
    //--------------------------------------------------------------------------------------------------------
    sf::Vector2u World::GetWindowSize() const
    {
        return WorldOwningApp.GetWindowSize();
    }
    //--------------------------------------------------------------------------------------------------------
    void World::CleanCycle()
    {
        for (auto ActorIterator = Actors.begin(); ActorIterator != Actors.end();)
        {
            if (ActorIterator->get()->IsPendingDestroy())
            {
                ActorIterator = Actors.erase(ActorIterator);
            }
            else
            {
                ++ActorIterator;
            }
        }

        for (auto StageIter = GameStages.begin(); StageIter != GameStages.end();)
        {
            if (StageIter->get()->IsStageFinish())
            {
                StageIter = GameStages.erase(StageIter);
            }
            else
            {
                ++StageIter;
            }
        }
    }
    void World::AddStage(const std::shared_ptr<GameStage>& NewStage)
    {
        GameStages.push_back(NewStage);
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
    //--------------------------------------------------------------------------------------------------------
    void World::InitGameStages()
    {
    }
    //--------------------------------------------------------------------------------------------------------
    void World::AllGameStageFinished()
    {
    }
    //--------------------------------------------------------------------------------------------------------
    void World::NextGameStage()
    {
        CurrentStageIndex++;
        if (CurrentStageIndex >= 0 && CurrentStageIndex < GameStages.size())
        {
            GameStages[CurrentStageIndex]->OnStageFinished.BindDelegate(GetWeakPtr(), &World::NextGameStage);
            GameStages[CurrentStageIndex]->StartStage();
        }
        else
        {
            AllGameStageFinished();
        }
    }
}
