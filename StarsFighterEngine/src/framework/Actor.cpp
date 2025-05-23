#include "framework/Actor.hpp"

#include <math.h>
#include <numbers>

#include "framework/Core.hpp"
#include "framework/World.hpp"
#include "framework/AssetManager.hpp"
#include "framework/PhysicsSystem.hpp"


namespace SF
{
	Actor::Actor(World* InWorld, const std::filesystem::path& FilePath, const std::string& InName)
		: WorldOwningActor{ InWorld }
		, ActorTexture{}
		, ActorSprite{ ActorTexture }
		, Name{ InName }
	{
		SetTexture(FilePath);
	}
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
	void Actor::OnActorBeginOverlap(Actor* OtherActor)
	{
		WriteLog(GLog, GLoglevel, "Actor " + GetName() + " begin overlap with actor: " + OtherActor->GetName());
	}
	void Actor::OnActorEndOverlap(Actor* OtherActor)
	{
		WriteLog(GLog, GLoglevel, "Actor " + GetName() + " end overlap with actor: " + OtherActor->GetName());
	}
	void Actor::Destroy()
	{
		DisablePhysics();
		Object::Destroy();
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
		return WorldOwningActor;
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
			std::string Message = "Actor " + GetName() + " Failed to load texture from file: " + FilePath.string();
			Helpers::WriteLog(GLog, Helpers::LogLevel::Error, Message);
		}
		else
		{
			ActorTexture = *ActorTexturePtr;
			ActorSprite.setTexture(ActorTexture);
			ActorSprite.setTextureRect(sf::IntRect{ sf::Vector2i{0, 0},
				sf::Vector2i{static_cast<int>(ActorTexture.getSize().x), static_cast<int>(ActorTexture.getSize().y)} });
			ActorSprite.setOrigin({ 0.f, 0.f});
			std::string Message = "Actor " + GetName() + " Texture loaded successfully from file: " + FilePath.string();
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
		UpdatePhysicsBodyTransform();
	}
	void Actor::SetActorRotation(float Rotation)
	{
		ActorSprite.setRotation(sf::degrees( Rotation ));
		UpdatePhysicsBodyTransform();
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
		float Rotation = (std::numbers::pi_v<float> / 2.f) - GetActorRotation(true);
		return sf::Vector2f(std::cosf(Rotation), std::sinf(Rotation));
	}
	sf::Vector2f Actor::GetActorRightDirection() const
	{
		float Rotation = GetActorRotation(true) + std::numbers::pi_v<float> / 2.f;
		return sf::Vector2f(std::cosf(Rotation), std::sinf(Rotation));
	}
	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return ActorSprite.getGlobalBounds();
	}
	void Actor::SetActorVisible(bool InVisible)
	{
		bIsVisible = InVisible;
		ActorSprite.setColor(InVisible ? sf::Color::White : sf::Color::Transparent);
	}
	bool Actor::IsActorOutOfScreen() const
	{
		auto WindowSize = GetWorld()->GetWindowSize();
		float GlobalWidth = ActorSprite.getGlobalBounds().size.x;
		float GlobalHeight = ActorSprite.getGlobalBounds().size.y;
		sf::Vector2f Location = GetActorLocation();

		if (Location.x < -GlobalWidth || Location.x > WindowSize.x + GlobalWidth ||
			Location.y < -GlobalHeight || Location.y > WindowSize.y + GlobalHeight)
		{
			return true;
		}
		return false;
	}
	void Actor::SetEnablePhysics(bool bInEnable)
	{
		bPhysicsEnabled = bInEnable;
		if (bPhysicsEnabled)
		{
			InitiallizePhysics();
		}
		else
		{
			DisablePhysics();
		}
	}
	void Actor::CenterPivot()
	{
		sf::FloatRect Bounds = ActorSprite.getGlobalBounds();
		ActorSprite.setOrigin(Bounds.getCenter());
	}
	void Actor::InitiallizePhysics()
	{
		if ( B2_IS_NULL(PhysicsBodyId) )
		{
			PhysicsBodyId = PhysicsSystem::Get().AddListener(this);
		}
	}
	void Actor::DisablePhysics()
	{
		if ( B2_IS_NON_NULL(PhysicsBodyId) )
		{
			PhysicsSystem::Get().PhysicsBodyToRemove(PhysicsBodyId);
		}
	}
	void Actor::UpdatePhysicsBodyTransform()
	{
		if (B2_IS_NON_NULL(PhysicsBodyId) )
		{
			float PhysicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 Position = b2Vec2{ GetActorLocation().x * PhysicsScale, GetActorLocation().y * PhysicsScale};
			float Rotation = GetActorRotation(true);
			b2Body_SetTransform(PhysicsBodyId, Position, b2MakeRot(Rotation));
		}
	}
}
