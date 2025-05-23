#pragma once
#include <memory>
#include <unordered_map>
#include <box2d/box2d.h>

namespace SF
{
	class Actor;

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
		static void Cleanup();

		void Step(float DeltaTime);
		b2BodyId AddListener(Actor* ActorListener);
		void PhysicsBodyToRemove(b2BodyId BodyToRemove);
		float GetPhysicsScale() const { return PhysicsScale; }

		~PhysicsSystem();
	protected:
		PhysicsSystem();

		void BeginContact(b2BodyId BodyIdA, b2BodyId BodyIdB);
		void EndContact(b2BodyId BodyIdA, b2BodyId BodyIdB);
		void ProcessPendingBodiesRemoval();
		void EnableContactEvents(b2BodyId BodyId, bool bEnable);

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