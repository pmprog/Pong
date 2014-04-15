
#pragma once

#include "../../framework/includes.h"
#include "../../library/vector2.h"
#include "../../library/angle.h"

#ifndef Arena
class Arena;
#endif

class Projectile
{

	protected:
		Arena* currentArena;

	public:
		Vector2* Position;
		Angle* Direction;
		float Speed;
		int Radius;

		Projectile( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );
		~Projectile();

		virtual void Update();
		virtual void Render();

};