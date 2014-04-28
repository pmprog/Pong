
#pragma once

#include "battleball.h"
#include "battleplayer.h"

class SendBall : public ClassicBall
{
	private:
		BattleInventory::Inventory sendingItem;
		Angle* sendingRotation;

	public:
		SendBall( BattleInventory::Inventory Item, Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void Render();
		virtual void OnCollision( Player* WithPlayer );
		virtual void OnCollisionPlayersWall( Player* WithPlayer );

};