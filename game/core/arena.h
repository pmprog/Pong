
#pragma once

#include "../../library/vector2.h"

#ifndef Projectile
class Projectile;
#endif
#ifndef Player
class Player;
#endif

class Arena
{

	public:
		Player* LeftPlayer;
		Player* RightPlayer;

		virtual void ProcessProjectileCollisions( Projectile* Source, Vector2* TargetPosition, bool* Continue ) = 0;
};