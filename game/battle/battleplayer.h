
#pragma once

#include "../core/player.h"

#ifndef BattleStage
class BattleStage;
#endif

#define FREEZE_TIME		4 * FRAMES_PER_SECOND

class BattlePlayer : private Player
{
	private:
		BattleStage* currentArena;

	public:
		int MaxHealth;

		int TargetSize;
		float Health;
		int TargetHealth;

		int Inventory[3];

		bool SendPressed;
		bool Inv1Pressed;
		bool Inv2Pressed;
		bool Inv3Pressed;

		int FreezeLevel;
		int FreezeTime;

		BattlePlayer( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY );
		~BattlePlayer();

		virtual void Update();
		// virtual void Render(); // Not needed

		void TakeDamage( int Amount );
};