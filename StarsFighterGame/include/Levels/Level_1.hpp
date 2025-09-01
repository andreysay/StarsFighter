/*
*  Level_1.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 02.06.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include "framework/World.hpp"
#include "framework/TimersHandler.hpp"

namespace SF
{
	class Level_1 : public World
	{
	public:
		Level_1() = delete;
		Level_1(const GameBaseApp& OwningApp);
		~Level_1() = default;
		//void LoadLevel();
		//void UnloadLevel();
		//void Update(float deltaTime);
		/*void Render();*/

	protected:
		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;

	private:
		void TimerCallbackTest();

	private:
		// Add private members for level data, entities, etc.
		TimerKey Key; // Example timer index for testing
	};
} // namespace SFG::Levels