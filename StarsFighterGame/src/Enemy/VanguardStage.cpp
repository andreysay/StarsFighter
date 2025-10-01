#include "Enemy/VanguardStage.hpp"
#include "framework/World.hpp"
#include "framework/TimersHandler.hpp"
#include  "Enemy/Vanguard.hpp"

namespace SF
{
	VanguardStage::VanguardStage(World* InWorld)
		: GameStage{ InWorld }
		, SpawnInterwal{ 1.5f } // Time interval between enemy spawns
		, SwitchInterwal{ 5.f } // Time interval to switch spawn side
		, SpawnDistanceToEdge{ 100.f } // Distance from the edge of the screen to spawn enemies
		, LeftSpawnPoint{ 0.f, 0.f } // Left spawn point (will be set in constructor body)
		, RightSpawnPoint{ 0.f, 0.f } // Right spawn point (will be set in constructor body)
		, CurrentSpawnPoint{ 0.f, 0.f } // Current spawn point (will be set in constructor body)
		, RowsToSpawn{ 2 } // Number of rows of enemies to spawn
		, RowSpawnedCount{ 0 } // Number of rows spawned so far
		, VanguardsPerRow{ 5 } // Number of enemies per row
		, VanguardsSpawnedInCurrentRow{ 0 } // Number of enemies spawned in the current row
	{
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------
	void VanguardStage::StartStage()
	{
		WriteLog(GLog, GLoglevel, "VanguardStage started.");
		// Calculate left and right spawn points based on the world size and spawn distance to edge
		auto WindowSize = GetWorld()->GetWindowSize();

		LeftSpawnPoint = sf::Vector2f{ SpawnDistanceToEdge, -100.f }; // Spawn just above the top edge
		RightSpawnPoint = sf::Vector2f{ WindowSize.x - SpawnDistanceToEdge, -100.f }; // Spawn just above the top edge
		CurrentSpawnPoint = LeftSpawnPoint; // Start spawning from the left side

		SwitchRow(); // Initialize the first spawn side
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------
	void VanguardStage::StageFinished()
	{
		TimersHandler::Get().ExpireTimer(SpawnTimer);
		TimersHandler::Get().ExpireTimer(SwitchTimer);
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------
	void VanguardStage::SpawnVanguardRow()
	{
		std::weak_ptr<Vanguard> NewVanguardWeakPtr = GetWorld()->SpawnActor<Vanguard>();
		NewVanguardWeakPtr.lock()->SetActorLocation(CurrentSpawnPoint);
		++VanguardsSpawnedInCurrentRow;
		if (VanguardsSpawnedInCurrentRow == VanguardsPerRow)
		{
			TimersHandler::Get().ExpireTimer(SpawnTimer); // Stop spawning more in this row
			SwitchTimer = TimersHandler::Get().RegisterTimer(GetWeakPtr(), &VanguardStage::SwitchRow, SwitchInterwal, false);
			VanguardsSpawnedInCurrentRow = 0; // Reset for the next row
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------
	void VanguardStage::SwitchRow()
	{
		if (RowSpawnedCount == RowsToSpawn)
		{
			// All rows have been spawned, no need to switch
			FinishStage();
			return;
		}

		if (RowSpawnedCount > 0 && CurrentSpawnPoint == LeftSpawnPoint)
		{
			CurrentSpawnPoint = RightSpawnPoint;
		}
		else
		{
			CurrentSpawnPoint = LeftSpawnPoint;
		}

		SpawnTimer = TimersHandler::Get().RegisterTimer(GetWeakPtr(), &VanguardStage::SpawnVanguardRow, SpawnInterwal, true);
		++RowSpawnedCount; // Increment the count of spawned rows
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------
	void VanguardStage::TickStage(float DeltaTime)
	{

	}

} // namespace SF