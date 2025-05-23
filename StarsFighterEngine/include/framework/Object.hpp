#pragma once

namespace SF
{
	//! Base class for all actors in the game
	class Object
	{
	public:
		Object() = default;
		virtual ~Object();
		virtual void Destroy();
		bool IsPendingDestroy() const { return bHasPendingDestroy; }
	private:
		bool bHasPendingDestroy = false;
	};
}