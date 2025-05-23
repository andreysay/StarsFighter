#pragma once
#include "framework/Core.hpp"
#include "framework/Actor.hpp"
#include <vector>

namespace SF
{
    class GameBaseApp;

    class World
    {
    public:
        explicit World(GameBaseApp* OwningApp);
        virtual ~World() = default;

        void BeginPlayInternal();
        void TickInternal(float DeltaTime);
        void Render(sf::RenderWindow& Window);
        sf::Vector2u GetWindowSize() const;

        template<typename ActorType, typename... Args>
		std::weak_ptr<ActorType> SpawnActor(Args... InArgs);

    protected:
        void BeginPlay();
        void Tick(float DeltaTime);

    private:
        GameBaseApp* WorldOwningApp{nullptr};
        bool bBeginPlay{false};
        // Main Actors array
		std::vector<std::shared_ptr<Actor>> Actors;
		// Actors pending to be added to the world
		std::vector<std::shared_ptr<Actor>> PendingActors;
    };

	template<typename ActorType, typename... Args>
	std::weak_ptr<ActorType> World::SpawnActor(Args... InArgs)
	{
        std::shared_ptr<ActorType> NewActor{ new ActorType(this, InArgs...) };
		//NewActor->SetWorld(this);
		PendingActors.push_back(NewActor);
		return NewActor;
	}
}
