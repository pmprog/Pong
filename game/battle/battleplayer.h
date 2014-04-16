
#pragma once

#include "../core/player.h"

class BattlePlayer : private Player
{
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

		BattlePlayer( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY );
		~BattlePlayer();

		virtual void Update();
		// virtual void Render(); // Not needed

		void TakeDamage( int Amount );
};