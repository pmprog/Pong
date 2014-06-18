
#pragma once

#include "../classic/classicball.h"

class BattleBall : public ClassicBall
{
	private:

	public:
		Player* LastHitBy;

		BattleBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void OnCollision( Player* WithPlayer );
		virtual void OnCollisionPlayersWall( Player* WithPlayer ); // Not needed

};