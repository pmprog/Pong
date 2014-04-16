
#pragma once

#include "../core/player.h"

class BattlePlayer : public Player
{
	public:
		int TargetSize;

		int Inventory[3];


		BattlePlayer( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY );
		~BattlePlayer();

		virtual void UpPushed();
		virtual void UpReleased();
		virtual void DownPushed();
		virtual void DownReleased();

		virtual void Update();
		// virtual void Render(); // Not needed
};