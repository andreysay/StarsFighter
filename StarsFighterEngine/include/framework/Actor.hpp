#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "framework/Object.hpp"


namespace SF
{
	class World;
	class GameBaseApp;
	//! Base class for all actors in the game
	class Actor : public Object
	{
	public:
		Actor(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName = "Actor");
		virtual ~Actor() = default;
		virtual void BeginPlay();
		virtual void Tick(float DeltaTime);

		void TickIntelrnal(float DeltaTime);
		void BeginPlayInternal();
		void SetWorld(World* InWorld);
		World* GetWorld() const;
		void SetName(const std::string& InName);
		const std::string& GetName() const;
		void SetTexture(const std::filesystem::path& FilePath);
		void Render(sf::RenderWindow& Window);
	private:
		World* WorldOwningActor = nullptr;
		std::string Name{};
		bool bBeginPlay = false;

		sf::Texture ActorTexture;
		sf::Sprite ActorSprite;

	};
}