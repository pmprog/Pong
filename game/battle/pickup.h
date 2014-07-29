
#pragma once

#include "../../framework/framework.h"
#include "../../library/vector2.h"
#include "../../library/animation.h"
#include "battleplayer.h"

#ifndef BattleStage
class BattleStage;
#endif

#define PICKUP_GRAPHIC_SIZE			32
#define PICKUP_ANIM_COOLDOWN		0
#define PICKUP_ANIM_WARPIN			1
#define PICKUP_ANIM_AVAILABLE		2
#define PICKUP_ANIM_COLLECTED		3
#define PICKUP_COOLDOWN_TIME		FRAMES_PER_SECOND * 8

class Pickup
{

	private:
		BattleStage* gameArena;
		Vector2* spawnPosition;
		SpriteSheet* pickupSprites;
		Animation* pickupAnimIn;
		Animation* pickupAnimAvailable;
		Animation* pickupAnimCollected;
		BattleInventory::Inventory pickupItem;

		int animationMode;
		int pickupCooldown;

		void InitPickup();

	public:
		Pickup( BattleStage* PlayArena, int StartX, int StartY );
		Pickup( BattleStage* PlayArena, Vector2* StartPosition );
		void Render();
		void Update();
		void GiveItem( BattlePlayer* ToPlayer );
};
