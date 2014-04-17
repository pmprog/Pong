
#pragma once

#include "../classic/classicball.h"

class BattleBall : public ClassicBall
{
	private:

	public:
		BattleBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void OnCollisionPlayersWall( Player* WithPlayer ); // Not needed

};