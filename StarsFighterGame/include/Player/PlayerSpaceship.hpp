#pragma once
#include "Spaceship/Spaceship.hpp"

namespace SF
{
	class BulletShooter;

	constexpr std::string_view PlayerSpaceshipTexturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png";

	class PlayerSpaceship : public Spaceship
	{
	public:
		static const uint32_t PlayerSpaceshipDefaultTeamId = 2; // Default team id for the player spaceship, used for identification of a groups objects in the game

	public:
		PlayerSpaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName = "PlayerSpaceship");
		void Tick(float DeltaTime) override;
		void Shoot() override;

		void SetSpeed(float InSpeed) { Speed = InSpeed; }
		float GetSpeed() const { return Speed; }
	private:
		void HandleInput(float DeltaTime);
		void Move(float DeltaTime);
		void Rotate(float DeltaTime);
		void ClampInputOnEdges(sf::Vector2f& Direction);
	private:
		sf::Vector2f PlayerVelocity;
		float Speed{200.f};

		std::shared_ptr<BulletShooter> ShooterInstance;
	};
}