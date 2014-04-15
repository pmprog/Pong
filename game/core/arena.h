
#pragma once

#include "../../library/vector2.h"

#ifndef Projectile
class Projectile;
#endif

class Arena
{

	public:
		virtual void ProcessProjectileCollisions( Projectile* Source, Vector2* TargetPosition, bool* Continue ) = 0;
};