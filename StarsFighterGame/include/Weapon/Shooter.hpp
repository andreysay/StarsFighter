/*
*  Shooter.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once

namespace SF
{
	class Actor;

	//! Shooter class is an abstract base class for any entity that can shoot projectiles
	class Shooter 
	{
	public:
		void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() const { return Owner; }
	protected:
		Shooter(Actor* InOwner);

	private:
		virtual void Shoot_Impl() = 0;
		Actor* Owner{ nullptr };
	};
}