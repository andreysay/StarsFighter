#pragma once
#include <memory>
#include "framework/Delegate.hpp"

namespace SF
{
	//! Base class for all actors in the game
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object() = default;
		virtual ~Object();
		virtual void Destroy();
		bool IsPendingDestroy() const { return bHasPendingDestroy; }

		std::weak_ptr<Object> GetWeakPtr();
		std::weak_ptr<const Object> GetWeakPtr() const;
		Delegate<Object*> OnDestroy;

	private:
		bool bHasPendingDestroy = false;
	};
}