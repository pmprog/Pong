
#pragma once

#include "battleball.h"

#define FIREBALL_PARTICLE_DELAY		3

// *******************
// Item: Single fireball (weapon)
// *******************

class FireBall : public ClassicBall
{
	private:
		//int ParticleDelay;
		// Vector2* positionHistory[10];

	public:
		FireBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void Update();
		virtual void Render();
		virtual void OnCollision( Player* WithPlayer );
		virtual void OnCollisionPlayersWall( Player* WithPlayer );

};
