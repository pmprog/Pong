
#pragma once

#include "battleball.h"

class FreezeBall : public BattleBall
{
	private:
		// Vector2* positionHistory[10];

	public:
		FreezeBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void Update();
		virtual void Render();
		virtual void OnCollision( Player* WithPlayer );
		virtual void OnCollisionPlayersWall( Player* WithPlayer );

};