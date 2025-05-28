/*
*  Shooter.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "Weapon/Shooter.hpp"

//--------------------------------------------------------------------------------------------------------
void SF::Shooter::Shoot()
{
	if (CanShoot() && !IsOnCooldown())
	{
		Shoot_Impl();
	}
	else
	{
		// Handle the case when the shooter cannot shoot
	}
}
//--------------------------------------------------------------------------------------------------------
SF::Shooter::Shooter(Actor* InOwner)
	: Owner{ InOwner }
{
}
