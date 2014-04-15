
#pragma once

#include "../core/projectile.h"

class ClassicBall : public Projectile
{
	private:
		// Vector2* positionHistory[10];

	public:
		ClassicBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );
		~ClassicBall();
		virtual void Update();
		virtual void Render();

};