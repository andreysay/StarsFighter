#pragma once
#include "Spaceship/Spaceship.hpp"

namespace SF
{
	constexpr std::string_view PlayerSpaceshipTexturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png";

	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName = "PlayerSpaceship");
		virtual void Tick(float DeltaTime) override;
		void SetSpeed(float InSpeed) { Speed = InSpeed; }
		float GetSpeed() const { return Speed; }
	private:
		void HandleInput(float DeltaTime);
		void Move(float DeltaTime);
		void Rotate(float DeltaTime);
	private:
		sf::Vector2f PlayerVelocity;
		float Speed{200.f};
	};
}