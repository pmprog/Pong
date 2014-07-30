
#pragma once

#include "battleball.h"

#define FREEZEBALL_PARTICLE_DELAY		8

// *******************
// Item: Freezeball (weapon)
// *******************

class FreezeBall : public ClassicBall
{
	private:
		int ParticleDelay;
		// Vector2* positionHistory[10];

	public:
		FreezeBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void Update();
		virtual void Render();
		virtual void OnCollision( Player* WithPlayer );
		virtual void OnCollisionPlayersWall( Player* WithPlayer );

};
