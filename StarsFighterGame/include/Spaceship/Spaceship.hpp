#pragma once
#include "framework/Actor.hpp"
#include "framework/Core.hpp"
#include "framework/HealthComponent.hpp"

namespace SF
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName = "Spaceship");

		~Spaceship() = default;

		//virtual void BeginPlay() override;
		
		virtual void Tick(float DeltaTime) override;
		virtual void Shoot();
		virtual void BeginPlay() override;


		void SetVelocity(const sf::Vector2f& InVelocity);

		inline sf::Vector2f GetVelocity() const { return SpaceshipVelocity; }

	private:
		sf::Vector2f SpaceshipVelocity;
		HealthComponent HealthComponent;
	};
}