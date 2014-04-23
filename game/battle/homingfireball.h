
#pragma once

#include "battleball.h"

#define HOMING_RETARGET_DELAY		FRAMES_PER_SECOND / 8
#define HOMING_RETARGET_TURN		10.0f

class HomingFireBall : public ClassicBall
{
	private:
		Player* target;
		int targetUpdateDelay;

	public:
		HomingFireBall( Player* TargetPlayer, Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void Update();
		virtual void Render();
		virtual void OnCollision( Player* WithPlayer );
		virtual void OnCollisionPlayersWall( Player* WithPlayer );

};