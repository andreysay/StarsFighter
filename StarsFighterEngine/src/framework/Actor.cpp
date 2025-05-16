#include "framework/Actor.hpp"
#include "framework/Core.hpp"
#include "framework/World.hpp"
#include "framework/AssetManager.hpp"
#include <math.h>
#include <numbers>

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
		auto ActorTexturePtr = AssetManager::Get().LoadTexture(FilePath);
		if (!ActorTexturePtr)
		{
			std::string Message = "Actor " + GetName() + "Failed to load texture from file: " + FilePath.string();
			Helpers::WriteLog(GLog, Helpers::LogLevel::Error, Message);
		}
		else
		{
			ActorTexture = *ActorTexturePtr;
			ActorSprite.setTexture(ActorTexture);
			ActorSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0, 0},
				sf::Vector2i{static_cast<int>(ActorTexture.getSize().x), static_cast<int>(ActorTexture.getSize().y)} });
			ActorSprite.setOrigin({ 0.f, 0.f});
			std::string Message = "Actor " + GetName() + "Texture loaded successfully from file: " + FilePath.string();
			Helpers::WriteLog(GLog, Helpers::LogLevel::Info, Message);
			CenterPivot();
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
	void Actor::SetActorLocation(const sf::Vector2f& Location)
	{
		ActorSprite.setPosition(Location);
	}
	void Actor::SetActorRotation(float Rotation)
	{
		ActorSprite.setRotation(sf::degrees( Rotation ));
	}
	void Actor::AddActorLocationOffset(const sf::Vector2f& Offset)
	{
		SetActorLocation(GetActorLocation() + Offset);
	}
	void Actor::AddActorRotationOffset(float Offset)
	{
		SetActorRotation(GetActorRotation() + Offset);
	}
	sf::Vector2f Actor::GetActorLocation() const
	{
		return ActorSprite.getPosition();
	}
	float Actor::GetActorRotation(bool bIsRadians) const
	{
		if (bIsRadians)
		{
			return ActorSprite.getRotation().asRadians();
		}

		return ActorSprite.getRotation().asDegrees();
	}
	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		float Rotation = GetActorRotation(true);
		return sf::Vector2f(std::cosf(Rotation), std::sinf(Rotation));
	}
	sf::Vector2f Actor::GetActorRightDirection() const
	{
		float Rotation = GetActorRotation(true) + std::numbers::pi_v<float> / 2.f;
		return sf::Vector2f(std::cosf(Rotation), std::sinf(Rotation));
	}
	void Actor::CenterPivot()
	{
		sf::FloatRect Bounds = ActorSprite.getGlobalBounds();
		ActorSprite.setOrigin(Bounds.getCenter());
	}
}
