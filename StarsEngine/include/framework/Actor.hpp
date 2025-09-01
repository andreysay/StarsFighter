/*
*  Actor.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
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
	//! Base class for any entity in the game
	//! Inherits from Object and provides functionality for rendering, updating, and interacting with the game world.
	class Actor : public Object
	{
		//---------------------------------------------------------------------
		//! Default team id for the actor, used for identification of a groups objects in the game
		const static uint32_t DefaultTeamId = 0; 
	public:
		Actor() = delete;
		Actor(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName = "Actor");
		Actor(const Actor&) = delete;
		Actor(Actor&&) = delete;
		Actor& operator=(const Actor&) = delete;
		Actor& operator=(Actor&&) = delete;
		virtual ~Actor() = default;

		//! Called when the actor is first created and added to the world
		virtual void BeginPlay();
		//! Called every frame to update the actor state
		virtual void Tick(float DeltaTime);
		//! Called when another actor begins overlapping with this actor
		virtual void OnActorBeginOverlap(Actor* OtherActor);
		//! Called when another actor ends overlapping with this actor
		virtual void OnActorEndOverlap(Actor* OtherActor);
		//! Disables the actor physics body and call parent object class for destruction
		virtual void Destroy() override;
		//! Applies damage to the actor, can be overridden by derived classes
		virtual void ApplyDamage(float DamageAmount);

		//! Called internally to update the actor state
		void TickIntelrnal(float DeltaTime);
		//! Called internally to begin play for the actor
		void BeginPlayInternal();
		//! Set the world that owns this actor
		void SetWorld(World* InWorld);
		//! Get the world that owns this actor
		const World* GetWorld() const;
		World* GetWorld();
		//! Set the name of the actor
		void SetName(const std::string& InName);
		//! Get the name of the actor
		const std::string& GetName() const;
		//! Set the texture for the actor from a file path
		void SetTexture(const std::filesystem::path& FilePath);
		//! Render the actor to the specified window
		void Render(sf::RenderWindow& Window);
		//! Set the actor's location
		void SetActorLocation(const sf::Vector2f& Location);
		//! Set the actor's rotation in degrees
		void SetActorRotation(float Rotation);
		//! Set the actor's location offset
		void AddActorLocationOffset(const sf::Vector2f& Offset);
		//! Set the actor's rotation offset in degrees
		void AddActorRotationOffset(float Offset);
		//! Set the actor's location
		sf::Vector2f GetActorLocation() const;
		//! Get the actor's rotation in degrees or radians
		float GetActorRotation(bool bIsRadians = false) const;
		//! Get the actor's forward direction
		sf::Vector2f GetActorForwardDirection() const;
		//! Get the actor's right direction
		sf::Vector2f GetActorRightDirection() const;
		//! Get the actor's global bounds
		sf::FloatRect GetActorGlobalBounds() const;

		//! Set the actor's visibility
		void SetActorVisible(bool InVisible);
		//! Check if the actor is visible
		bool IsActorVisible() const { return bIsVisible; }
		// ! Determine if the actor is within the screen bounds
		bool IsActorOutOfScreen(float Offset = 20.f) const;

		//! Enable or disable physics for the actor
		//! Called at the beginning of the actor's life cycle
		void SetEnablePhysics(bool bInEnable);
		//! Set the actor's physics body to sleep mode
		void EnablePhysicsSleep();
		//! Awake the actor's physics body
		void AwakePhysics();

		//! Get the actor's team id
		void SetTeamId(uint32_t InTeamId);
		//! Get the actor's team id
		uint32_t GetTeamId() const;
		//! Check if the other actor is part of a hostile team
		bool IsHostileTeam(const Actor* OtherActor) const;
		virtual bool IsNotBullet() const { return true; } // Default implementation, can be overridden by derived classes

		sf::Sprite& GetActorSprite() { return ActorSprite; }
		const sf::Sprite& GetActorSprite() const { return ActorSprite; }

	private:
		//! Center the pivot of the actor sprite
		void CenterPivot();
		//! Initialize the physics body for the actor
		void InitiallizePhysics();
		//! Disable the physics body for the actor
		void DisablePhysics();
		//! Update the physics body transform based on the actor's position and rotation
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

		std::optional<uint32_t> TeamId; // Optional team id for the actor, used for identification of a groups objects in the game
	};
}