#include "Player/PlayerSpaceship.hpp"
#include <SFML/System.hpp>

namespace SF
{
	PlayerSpaceship::PlayerSpaceship(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName)
		: Spaceship{ InWorld, FilePath, InName }
	{
	}
	void PlayerSpaceship::Tick(float DeltaTime)
	{
		Spaceship::Tick(DeltaTime);
		HandleInput(DeltaTime);
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
		SetVelocity(Direction * Speed);
		AddActorLocationOffset(GetVelocity() * DeltaTime);
	}
	void PlayerSpaceship::Move(float DeltaTime)
	{

	}
	void PlayerSpaceship::Rotate(float DeltaTime)
	{

	}
}