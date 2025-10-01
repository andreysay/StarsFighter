#pragma once
#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.hpp"
#include "framework/TimersHandler.hpp"

namespace SF
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* InWorld);
		virtual ~VanguardStage() override = default;
		virtual void StartStage() override;
		virtual void TickStage(float DeltaTime) override;

	protected:
		virtual void StageFinished() override;
		void SpawnVanguardRow();
		void SwitchRow();
	private:
		float SpawnInterwal; // Time interval between enemy spawns
		float SwitchInterwal; // Time interval to switch spawn side
		float SpawnDistanceToEdge; // Distance from the edge of the screen to spawn enemies

		sf::Vector2f LeftSpawnPoint; // Left spawn point
		sf::Vector2f RightSpawnPoint; // Right spawn point
		sf::Vector2f CurrentSpawnPoint; // Current spawn point

		TimerKey SpawnTimer; // Timer for spawning enemies
		TimerKey SwitchTimer; // Timer for switching spawn side

		uint16_t RowsToSpawn; // Number of rows of enemies to spawn
		uint16_t RowSpawnedCount; // Number of rows spawned so far

		uint16_t VanguardsPerRow; // Number of enemies per row
		uint16_t VanguardsSpawnedInCurrentRow; // Number of enemies spawned in the current row
	};
} // namespace SF