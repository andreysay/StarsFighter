/*
*  PhysicsSystem.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "framework/PhysicsSystem.hpp"
#include "framework/Actor.hpp"
#include "framework/Core.hpp"
#include "Windows.h"

namespace SF
{
	std::unique_ptr<PhysicsSystem> PhysicsSystem::PhysicsSystemInstance{ nullptr };
	//--------------------------------------------------------------------------------------------------------
	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!PhysicsSystemInstance)
		{
			PhysicsSystemInstance = std::unique_ptr<PhysicsSystem>( new PhysicsSystem );
		}
		return *PhysicsSystemInstance;
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::Cleanup()
	{
		if (PhysicsSystemInstance)
		{
			PhysicsSystemInstance->ProcessPendingBodiesRemoval();
			PhysicsSystemInstance.reset(new PhysicsSystem);
		}
		else
		{
			PhysicsSystemInstance = std::unique_ptr<PhysicsSystem>(new PhysicsSystem);
		}
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::Step(float DeltaTime)
	{
		ProcessPendingBodiesRemoval();
		b2World_Step(PhysicsWorldId, DeltaTime, PositionIterations);

		// Process contact begin touch events.
		b2ContactEvents ContactEvents = b2World_GetContactEvents(PhysicsWorldId);
		for (int i = 0; i < ContactEvents.beginCount; ++i)
		{
			b2ContactBeginTouchEvent BeginEvent = ContactEvents.beginEvents[i];
			b2BodyId BodyIdA = b2Shape_GetBody(BeginEvent.shapeIdA);
			b2BodyId BodyIdB = b2Shape_GetBody(BeginEvent.shapeIdB);
			BeginContact(BodyIdA, BodyIdB);
		}

		for (int i = 0; i < ContactEvents.endCount; ++i)
		{
			b2ContactEndTouchEvent* EndEvent = ContactEvents.endEvents + i;

			// Use b2Shape_IsValid because a shape may have been destroyed
			if (b2Shape_IsValid(EndEvent->shapeIdA) && b2Shape_IsValid(EndEvent->shapeIdB))
			{
				b2BodyId BodyIdA = b2Shape_GetBody(EndEvent->shapeIdA);
				b2BodyId BodyIdB = b2Shape_GetBody(EndEvent->shapeIdB);
				EndContact(BodyIdA, BodyIdB);
			}
		}

		//b2SensorEvents sensorEvents = b2World_GetSensorEvents(PhysicsWorldId);
		//for (int i = 0; i < sensorEvents.beginCount; ++i)
		//{
		//	b2SensorBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
		//	void* myUserData = b2Shape_GetUserData(beginTouch->visitorShapeId);
		//	// process begin event
		//	std::string Message = "Sensor event: " + std::to_string(beginTouch->visitorShapeId.index1);
		//	WriteLog(GLog, GLoglevel, Message);
		//}

		//b2BodyEvents events = b2World_GetBodyEvents(PhysicsWorldId);
		//for (int i = 0; i < events.moveCount; ++i)
		//{
		//	const b2BodyMoveEvent* event = events.moveEvents + i;
		//	b2BodyId BodyIdA = event->bodyId;
		//	b2Vec2 position = b2Body_GetPosition(BodyIdA);
		//	b2Rot rotation = b2Body_GetRotation(BodyIdA);
		//	std::string Message = "Body moved: " + std::to_string(BodyIdA.index1) + std::format(" (X:{}, Y:{}) Angle = {}", position.x, position.y, b2Rot_GetAngle(rotation));
		//	WriteLog(GLog, GLoglevel, Message);
		//}

	}
	//--------------------------------------------------------------------------------------------------------
	b2BodyId PhysicsSystem::AddPhysicsOwnerActor(Actor* InActor)
	{
		if (!InActor || InActor->IsPendingDestroy() /*|| !InActor->IsActorVisible()*/)
		{
			return b2_nullBodyId;
		}

		b2BodyDef BodyDef = b2DefaultBodyDef();
		BodyDef.type = b2_dynamicBody;
		BodyDef.position = b2Vec2{ InActor->GetActorLocation().x, InActor->GetActorLocation().y };
		BodyDef.rotation = b2MakeRot(InActor->GetActorRotation(true));
		b2BodyId BodyId = b2CreateBody(PhysicsWorldId, &BodyDef);

		auto ActorBounds = InActor->GetActorGlobalBounds();
		b2Polygon ShapeBox = b2MakeBox(ActorBounds.size.x / 2.f * GetPhysicsScale(), ActorBounds.size.y / 2.f * GetPhysicsScale());
		b2ShapeDef ShapeDef = b2DefaultShapeDef();
		ShapeDef.density = 1.f;
		ShapeDef.material.friction = 0.3f;

		b2CreatePolygonShape(BodyId, &ShapeDef, &ShapeBox);
		b2Body_EnableContactEvents(BodyId, true);
		b2Body_SetUserData(BodyId, InActor);
		b2Body_EnableSleep(BodyId, false);

		return BodyId;
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::PhysicsBodyToRemove(b2BodyId BodyToRemove)
	{
		if (PendingBodiesToRemove.try_emplace(BodyToRemove.index1, BodyToRemove).second)
		{
			std::string Message = "Body to remove: " + std::to_string(BodyToRemove.index1);
			WriteLog(GLog, GLoglevel, Message);
			PendingBodiesToRemove.emplace(BodyToRemove.index1, BodyToRemove);
		}
		else
		{
			std::string Message = "Body already in pending removal: " + std::to_string(BodyToRemove.index1);
			WriteLog(GLog, GLoglevel, Message);
		}
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::EnableSleepPhysicsBody(b2BodyId BodyId, bool bEnable)
	{
		if (bEnable && b2Body_IsSleepEnabled(BodyId))
		{
			WriteLog(GLog, GLoglevel, "Physics body is already in sleep mode.");
			return;
		}

		if (B2_IS_NON_NULL(BodyId))
		{
			b2Body_EnableSleep(BodyId, bEnable);
		}
		else
		{
			WriteLog(GLog, GLoglevel, "Physics body is null, cannot enable sleep.");
		}
	}
	//--------------------------------------------------------------------------------------------------------
	PhysicsSystem::~PhysicsSystem()
	{
		b2DestroyWorld(PhysicsWorldId);
	}
	//--------------------------------------------------------------------------------------------------------
	PhysicsSystem::PhysicsSystem()
		: PhysicsScale{ 0.01f }
	{
		b2WorldDef PhysicsWorldDef = b2DefaultWorldDef();
		PhysicsWorldDef.gravity = b2Vec2_zero;
		PhysicsWorldId = b2CreateWorld(&PhysicsWorldDef);
		b2World_EnableSleeping(PhysicsWorldId, false);
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::BeginContact(b2BodyId BodyIdA, b2BodyId BodyIdB)
	{
		std::string Message = "Begin contact: " + std::to_string(BodyIdA.index1) + " and " + std::to_string(BodyIdB.index1);
		//WriteLog(GLog, GLoglevel, Message);

		Actor* ActorA = static_cast<Actor*>(b2Body_GetUserData(BodyIdA));
		Actor* ActorB = static_cast<Actor*>(b2Body_GetUserData(BodyIdB));

		if (ActorA && ActorB && !ActorA->IsPendingDestroy())
		{
			ActorA->OnActorBeginOverlap(ActorB);
			if (!ActorB->IsPendingDestroy())
			{
				ActorB->OnActorBeginOverlap(ActorA);
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::EndContact(b2BodyId BodyIdA, b2BodyId BodyIdB)
	{
		std::string Message = "End contact: " + std::to_string(BodyIdA.index1) + " and " + std::to_string(BodyIdB.index1);
		//WriteLog(GLog, GLoglevel, Message);
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (B2_IS_NON_NULL(BodyIdA))
		{
			ActorA = static_cast<Actor*>(b2Body_GetUserData(BodyIdA));
		}
		if (B2_IS_NON_NULL(BodyIdB))
		{
			ActorB = static_cast<Actor*>(b2Body_GetUserData(BodyIdB));
		}

		if (ActorA && !ActorA->IsPendingDestroy())
		{
			ActorA->OnActorEndOverlap(ActorB);
		}
		if (ActorB && !ActorB->IsPendingDestroy())
		{
			ActorB->OnActorEndOverlap(ActorA);
		}
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::ProcessPendingBodiesRemoval()
	{
		for (auto& [index, BodyToRemove] : PendingBodiesToRemove)
		{
			b2Body_Disable(BodyToRemove);
		}
		PendingBodiesToRemove.clear();
	}
	//--------------------------------------------------------------------------------------------------------
	void PhysicsSystem::EnableContactEvents(b2BodyId BodyId, bool bEnable)
	{
		if (B2_IS_NON_NULL(BodyId))
		{
			b2Body_EnableContactEvents(BodyId, bEnable);
		}
	}
}

