#include "Spaceship/Spaceship.hpp"

namespace SF
{
	Spaceship::Spaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName)
		: Actor{ InWorld, FilePath, InName }
	{
	}
	void Spaceship::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);
		AddActorLocationOffset(GetVelocity() * DeltaTime);
		//WriteLog(GLog, Helpers::LogLevel::Info, "Spaceship is ticking at framerate: " + std::to_string(1.f / DeltaTime));
	}
	void Spaceship::Shoot()
	{
	}
	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
	void Spaceship::SetVelocity(const sf::Vector2f& InVelocity)
	{
		SpaceshipVelocity = InVelocity;
	}
}


