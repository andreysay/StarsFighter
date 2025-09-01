#include "gameplay/GameStage.hpp"
#include "framework/Core.hpp"

namespace SF
{
	GameStage::GameStage(World* InWorld)
		: GameWorld{InWorld}
	{

	}

	void GameStage::StartStage()
	{
		Helpers::WriteLog(GLog, Helpers::LogLevel::Error, "Stage Started");
	}

	void GameStage::TickStage(float DeltaTime)
	{
		Helpers::WriteLog(GLog, Helpers::LogLevel::Error, "Stage Ticking");
	}

	void GameStage::FinishStage()
	{
		OnStageFinished.Broadcast();
		IsStageFinished = true;
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		Helpers::WriteLog(GLog, Helpers::LogLevel::Error, "Stage Finished");
	}
}// namespace SF
