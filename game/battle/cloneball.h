
#pragma once

#include "battleball.h"

class CloneBall : public BattleBall
{
	private:
		int LifeSpan;
		// Vector2* positionHistory[10];

	public:
		CloneBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void Update();
		virtual void Render();
		//virtual void OnCollision( Player* WithPlayer );	// Not needed
		virtual void OnCollisionPlayersWall( Player* WithPlayer ); // Not needed

};