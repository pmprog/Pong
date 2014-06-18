
#pragma once

#include "../core/player.h"

#ifndef BattleStage
class BattleStage;
#endif

#define FREEZE_TIME		4 * FRAMES_PER_SECOND
#define SIZING_DELAY	10
#define SIZING_MAX		192	
#define SIZING_MIN		64
#define SIZING_STEP		32
#define REVERSE_TIME	4 * FRAMES_PER_SECOND

namespace BattleInventory
{
	enum Inventory
	{
		INVENTORY_NONE = 0,
		INVENTORY_FIREBALL,
		INVENTORY_TRIFIRE,
		INVENTORY_HOMING,
		INVENTORY_FREEZE,
		INVENTORY_REVERSE_BALL_VERT,
		INVENTORY_REVERSE_BALL_HORZ,
		INVENTORY_PADDLE_INCREASE,
		INVENTORY_PADDLE_REVERSE_CONTROLS,
		INVENTORY_PADDLE_DECREASE
	};
}

class BattlePlayer : private Player
{
	private:
		BattleStage* currentArena;
		void setFreezeColour();

	public:
		int MaxHealth;

		int TargetSize;
		int SizeDelay;

		float Health;
		int TargetHealth;

		BattleInventory::Inventory Inventory[3];

		bool SendPressed;
		bool Inv1Pressed;
		bool Inv2Pressed;
		bool Inv3Pressed;

		int FreezeLevel;
		int FreezeTime;

		int ReverseControlTime;

		BattlePlayer( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY );
		~BattlePlayer();

		virtual void Update();
		// virtual void Render(); // Not needed

		void Freeze();
		void Burn();
		void TakeDamage( int Amount );
		void UseInventory( int Slot );
		void SendInventory( int Slot );

};