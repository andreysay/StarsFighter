#include "Player/PlayerSpaceship.hpp"
#include <SFML/System.hpp>
#include "framework/MathUtility.hpp"
#include "framework/World.hpp"
#include "Weapon/BulletShooter.hpp"

namespace SF
{
	PlayerSpaceship::PlayerSpaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName)
		: Spaceship{ InWorld, FilePath, InName }
	{
		SetTeamId(PlayerSpaceshipDefaultTeamId);
		ShooterInstance = std::make_unique<BulletShooter>(this, 0.1f); // Initialize the BooletShooter with a cooldown time
		std::string LogMessage = "PlayerSpaceship created with ID: " + std::to_string(GetTeamId());
		WriteLog(GLog, GLoglevel, LogMessage);
	}
	void PlayerSpaceship::Tick(float DeltaTime)
	{
		Spaceship::Tick(DeltaTime);
		HandleInput(DeltaTime);
	}
	void PlayerSpaceship::Shoot()
	{
		if (ShooterInstance)
		{
			ShooterInstance->Shoot();
		}
	}
	void PlayerSpaceship::HandleInput(float DeltaTime)
	{
		sf::Vector2f Direction{ 0.f, 0.f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			Direction.y = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			Direction.y = 1.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			Direction.x = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			Direction.x = 1.f;

		ClampInputOnEdges(Direction);
		SF::Math::NormalizeVector(Direction);
		//std::string DirectionString = std::to_string(Direction.x) + ", " + std::to_string(Direction.y);
		//WriteLog(GLog, GLoglevel, DirectionString);
		SetVelocity(Direction * Speed);
		AddActorLocationOffset(GetVelocity() * DeltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			Shoot();
		}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		//{
		//	GetWorld()->GetOwningApp()->Close();
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))
		//{
		//	WriteLog(GLog, GLoglevel, "F1 pressed");
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))
		//{
		//	WriteLog(GLog, GLoglevel, "F2 pressed");
		//}
	}
	void PlayerSpaceship::Move(float DeltaTime)
	{

	}
	void PlayerSpaceship::Rotate(float DeltaTime)
	{

	}
	void PlayerSpaceship::ClampInputOnEdges(sf::Vector2f& Direction)
	{
		if (GetWorld() == nullptr)
			return;

		sf::Vector2f CurrentLocation = GetActorLocation();
		sf::Vector2u WindowSize = GetWorld()->GetWindowSize();

		if (CurrentLocation.x < 0.f && Direction.x == -1.f)
			Direction.x = 0.f;
		if (CurrentLocation.x > WindowSize.x && Direction.x == 1.f)
			Direction.x = 0.f;
		if (CurrentLocation.y < 0.f && Direction.y == -1)
			Direction.y = 0.f;
		if (CurrentLocation.y > WindowSize.y && Direction.y == 1)
			Direction.y = 0.f;
	}
}