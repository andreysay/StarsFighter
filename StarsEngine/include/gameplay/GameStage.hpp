#pragma once

#include "framework/Object.hpp"
#include "framework/Delegate.hpp"

namespace SF
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* InWorld);
		const World* GetWorld() const { return GameWorld; }
		World* GetWorld() { return GameWorld; }

		Delegate<> OnStageFinished;

		virtual void StartStage();
		virtual void TickStage(float DeltaTime);

		void FinishStage();
		bool IsStageFinish() const { return IsStageFinished; }

	protected:
		virtual void StageFinished();

	private:
		World* GameWorld;
		bool IsStageFinished;
	};
}