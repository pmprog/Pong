
#pragma once

#include "../core/projectile.h"

class ClassicBall : public Projectile
{
	private:
		int spin;
		// Vector2* positionHistory[10];

	public:
		ClassicBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );
		~ClassicBall();

		virtual void Update();
		virtual void Render();
		virtual void OnCollision( Player* WithPlayer );
		//virtual void OnCollisionPlayersWall( Player* WithPlayer ); // Not needed

};