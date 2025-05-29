/*
*  PhysicsSystem.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <memory>
#include <unordered_map>
#include <box2d/box2d.h>

namespace SF
{
	class Actor;

	//! PhysicsSystem class is responsible for managing the physics simulation in the game.
	class PhysicsSystem
	{
	public:
		//! Get the singleton instance of PhysicsSystem
		static PhysicsSystem& Get();
		//! Clean up and reset the PhysicsSystem instance
		static void Cleanup();
		//! Enable or disable contact events for a specific physics body
		static void EnableContactEvents(b2BodyId BodyId, bool bEnable);

		//! Step the physics simulation by a given time delta
		void Step(float DeltaTime);
		//! Create a physics body for an actor and add it to the physics world
		b2BodyId AddPhysicsOwnerActor(Actor* InActor);
		//! Remove a physics body from the simulation, marking it for removal
		void PhysicsBodyToRemove(b2BodyId BodyToRemove);
		//! Get the physics scale used in the simulation
		float GetPhysicsScale() const { return PhysicsScale; }
		//! Enable/disable sleep mode for a physics body
		void EnableSleepPhysicsBody(b2BodyId BodyId, bool bEnable);

		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem& operator=(const PhysicsSystem&) = delete;
		PhysicsSystem(PhysicsSystem&&) = delete;
		PhysicsSystem& operator=(PhysicsSystem&&) = delete;
		~PhysicsSystem();
	protected:
		//! Constructor for PhysicsSystem, initializes the physics world
		PhysicsSystem();
		//! Fetch the begin contact event for two bodies
		void BeginContact(b2BodyId BodyIdA, b2BodyId BodyIdB);
		//! Fetch the end contact event for two bodies
		void EndContact(b2BodyId BodyIdA, b2BodyId BodyIdB);
		//! Process and remove all pending bodies marked for removal
		void ProcessPendingBodiesRemoval();

	private:
		// Private members for physics simulation
		static std::unique_ptr<PhysicsSystem> PhysicsSystemInstance;
		b2WorldId  PhysicsWorldId;
		float PhysicsScale{};
		int32_t VelocityTterations{8};
		int32_t PositionIterations{4};
		std::unordered_map<int32_t, b2BodyId> PendingBodiesToRemove{};
	};
}