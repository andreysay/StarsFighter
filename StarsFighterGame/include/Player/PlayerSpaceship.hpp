#pragma once
#include "Spaceship/Spaceship.hpp"

namespace SF
{
	class BulletShooter;

	constexpr std::string_view PlayerSpaceshipTexturePath = "StarsFighter/Player/Player_Spritesheet.png";

	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* InWorld, const std::filesystem::path& FilePath, bool IsAnimated = false, const std::string& InName = "PlayerSpaceship");
		void Tick(float DeltaTime) override;
		void Shoot() override;

		void SetSpeed(float InSpeed) { Speed = InSpeed; }
		float GetSpeed() const { return Speed; }
		void SetShooterLocation();
	private:
		void HandleInput(float DeltaTime);
		void Move(float DeltaTime);
		void Rotate(float DeltaTime);
		void ClampInputOnEdges(sf::Vector2f& Direction);
	private:
		sf::Vector2f PlayerVelocity;
		float Speed{200.f};

		std::unique_ptr<BulletShooter> ShooterInstance;
	};
}