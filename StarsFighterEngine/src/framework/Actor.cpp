#include "framework/Actor.hpp"
#include "framework/Core.hpp"
#include "framework/World.hpp"

namespace SF
{
	Actor::Actor(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName)
		: WorldOwningActor{ InWorld }
		, ActorTexture{}
		, ActorSprite{ ActorTexture }
		, Name{ InName }
	{}
	void Actor::BeginPlay()
	{
		//std::string Message = "Actor begin play.";
		//Helpers::WriteLog(GLog, Helpers::LogLevel::Info, Message);
	}
	void Actor::Tick(float DeltaTime)
	{
		//std::string Message = "Actor is ticking at framerate: " + std::to_string(1.f / DeltaTime);
		//Helpers::WriteLog(GLog, Helpers::LogLevel::Info, Message);
	}
	void Actor::TickIntelrnal(float DeltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(DeltaTime);
		}
	}
	void Actor::BeginPlayInternal()
	{
		if (!bBeginPlay)
		{
			bBeginPlay = true;
			BeginPlay();
		}
	}
	void Actor::SetWorld(World* InWorld)
	{
	}
	World* Actor::GetWorld() const
	{
		return nullptr;
	}
	void Actor::SetName(const std::string& InName)
	{
		Name = InName;
	}
	const std::string& Actor::GetName() const
	{
		// TODO: insert return statement here
		return Name;
	}
	void Actor::SetTexture(const std::filesystem::path& FilePath)
	{
		if (!ActorTexture.loadFromFile(FilePath))
		{
			std::string Message = "Failed to load texture from file: " + FilePath.string();
			Helpers::WriteLog(GLog, Helpers::LogLevel::Error, Message);
		}
		else
		{
			ActorSprite.setTexture(ActorTexture);
			ActorSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0, 0},
				sf::Vector2i{static_cast<int>(ActorTexture.getSize().x), static_cast<int>(ActorTexture.getSize().y)} });
			ActorSprite.setOrigin({ 0.f, 0.f});
			std::string Message = "Texture loaded successfully from file: " + FilePath.string();
			Helpers::WriteLog(GLog, Helpers::LogLevel::Info, Message);
		}
	}
	void Actor::Render(sf::RenderWindow& Window)
	{
		if (IsPendingDestroy())
		{
			return;
		}
		Window.draw(ActorSprite);
	}
}
