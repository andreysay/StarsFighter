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

        template<typename ActorType>
		std::weak_ptr<ActorType> SpawnActor(const std::string& Name = "Actor");

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

	template<typename ActorType>
	inline std::weak_ptr<ActorType> World::SpawnActor(const std::string& Name)
	{
        std::shared_ptr<ActorType> NewActor{ new ActorType{this, Name} };
		//NewActor->SetWorld(this);
		PendingActors.push_back(NewActor);
		return NewActor;
	}
}
