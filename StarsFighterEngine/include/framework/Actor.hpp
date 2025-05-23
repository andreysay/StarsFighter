#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "framework/Object.hpp"

namespace SF
{
	class World;
	class GameBaseApp;
	//! Base class for all actors in the game
	class Actor : public Object
	{
	public:
		Actor() = default;
		Actor(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName = "Actor");
		virtual ~Actor() = default;
		virtual void BeginPlay();
		virtual void Tick(float DeltaTime);
		virtual void OnActorBeginOverlap(Actor* OtherActor);
		virtual void OnActorEndOverlap(Actor* OtherActor);
		virtual void Destroy() override;

		void TickIntelrnal(float DeltaTime);
		void BeginPlayInternal();
		void SetWorld(World* InWorld);
		World* GetWorld() const;
		void SetName(const std::string& InName);
		const std::string& GetName() const;
		void SetTexture(const std::filesystem::path& FilePath);
		void Render(sf::RenderWindow& Window);
		void SetActorLocation(const sf::Vector2f& Location);
		void SetActorRotation(float Rotation);
		void AddActorLocationOffset(const sf::Vector2f& Offset);
		void AddActorRotationOffset(float Offset);
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation(bool bIsRadians = false) const;
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

		sf::FloatRect GetActorGlobalBounds() const;

		void SetActorVisible(bool InVisible);
		bool IsActorVisible() const { return bIsVisible; }
		// ! Determine if the actor is within the screen bounds
		bool IsActorOutOfScreen() const;

		void SetEnablePhysics(bool bInEnable);

	private:
		void CenterPivot();
		void InitiallizePhysics();
		void DisablePhysics();
		void UpdatePhysicsBodyTransform();

	private:
		World* WorldOwningActor = nullptr;
		std::string Name{};
		bool bBeginPlay{ false };
		bool bIsVisible{ true };

		sf::Texture ActorTexture;
		sf::Sprite ActorSprite;

		b2BodyId PhysicsBodyId = b2_nullBodyId;
		bool bPhysicsEnabled{ false };
	};
}