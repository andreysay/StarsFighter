/*
*  World.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include "framework/Core.hpp"
#include "framework/Actor.hpp"
#include <vector>

namespace SF
{
    class GameBaseApp;

    /*
	* The class World represents a level or a game world in which actors exist and interact.
    */
    class World
    {
    public:
		World() = delete;
        explicit World(const GameBaseApp& OwningApp);
		World(const World&) = delete;
		World(World&&) = delete;
		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;
		virtual ~World() = default; // Check if this is needed

		// Called internally to begin play in the world
        void BeginPlayInternal();
		// Called internally to update the world state
        void TickInternal(float DeltaTime);
		// Called internally to render the world
        void Render(sf::RenderWindow& Window);
		// Gets current world size
		[[nodiscard]]
        sf::Vector2u GetWindowSize() const;
		// Spawns a new actor of the specified type with given arguments and returns a weak pointer to it.
        template<typename ActorType, typename... Args>
		std::weak_ptr<ActorType> SpawnActor(Args... InArgs);

    protected:
        void BeginPlay();
        void Tick(float DeltaTime);

    private:
        //GameBaseApp* WorldOwningApp{ nullptr };
        const GameBaseApp& WorldOwningApp;
        bool bBeginPlay{false};
        // Main Actors array
		std::vector<std::shared_ptr<Actor>> Actors;
		// Actors pending to be added to the world
		std::vector<std::shared_ptr<Actor>> PendingActors;
    };
	//--------------------------------------------------------------------------------------------------------
	template<typename ActorType, typename... Args>
	std::weak_ptr<ActorType> World::SpawnActor(Args... InArgs)
	{
        std::shared_ptr<ActorType> NewActor{ new ActorType(this, InArgs...) };
		PendingActors.push_back(NewActor);
		return NewActor;
	}
}
