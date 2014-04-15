
#pragma once

#include "projectile.h"

class Arena
{

	public:
		virtual int Collisions_ProjectileToPlayer( Projectile* Source, Vector2* TargetPosition ) = 0;
		virtual bool Collisions_ProjectileToBounds( Projectile* Source, Vector2* TargetPosition ) = 0;
		virtual int Collisions_ProjectileToPickups( Projectile* Source, Vector2* TargetPosition ) = 0;

};