
#include "pickup.h"
#include "battle.h"

Pickup::Pickup( BattleStage* PlayArena, int StartX, int StartY )
{
	gameArena = PlayArena;
	spawnPosition = new Vector2( StartX, StartY );
	InitPickup();
}

Pickup::Pickup( BattleStage* PlayArena, Vector2* StartPosition )
{
	gameArena = PlayArena;
	spawnPosition = new Vector2( StartPosition );
	InitPickup();
}

void Pickup::InitPickup()
{
	pickupItem = (BattleInventory::Inventory)((rand() % (int)BattleInventory::INVENTORY_PADDLE_DECREASE) + 1);

	pickupSprites = new SpriteSheet( "resources/pickups.png", 32, 32 );
	pickupAnimIn = new Animation( pickupSprites, false, 10 );
	pickupAnimAvailable = new Animation( pickupSprites, true, 10 );
	pickupAnimCollected = new Animation( pickupSprites, false, 10 );

	pickupAnimIn->AddFrame( 0 );
	pickupAnimIn->AddFrame( 1 );
	pickupAnimIn->AddFrame( 2 );
	pickupAnimIn->AddFrame( 3 );

	pickupAnimAvailable->AddFrame( 5 );

	pickupAnimCollected->AddFrame( 5 );
	pickupAnimCollected->AddFrame( 7 );
	pickupAnimCollected->AddFrame( 5 );
	pickupAnimCollected->AddFrame( 7 );
	pickupAnimCollected->AddFrame( 7 );
	pickupAnimCollected->AddFrame( 8 );
	pickupAnimCollected->AddFrame( 7 );
	pickupAnimCollected->AddFrame( 8 );
	pickupAnimCollected->AddFrame( 7 );

	animationMode = PICKUP_ANIM_WARPIN;
	pickupAnimIn->Start();
	pickupCooldown = 0;
}

void Pickup::Render()
{
	switch( animationMode )
	{
		case PICKUP_ANIM_WARPIN:
			pickupAnimIn->DrawFrame( spawnPosition->X - 16, spawnPosition->Y - 16 );
			break;
		case PICKUP_ANIM_AVAILABLE:
			pickupAnimAvailable->DrawFrame( spawnPosition->X - 16, spawnPosition->Y - 16 );
			break;
		case PICKUP_ANIM_COLLECTED:
			pickupAnimCollected->DrawFrame( spawnPosition->X - 16, spawnPosition->Y - 16 );
			break;
	}
}

void Pickup::Update()
{
	switch( animationMode )
	{
		case PICKUP_ANIM_WARPIN:
			// TODO: Check if collision with ball, and set to collected and pass to player
			pickupAnimIn->Update();
			if( pickupAnimIn->HasEnded() )
			{
				animationMode = PICKUP_ANIM_AVAILABLE;
				pickupAnimAvailable->Start();
			}
			break;
		case PICKUP_ANIM_AVAILABLE:
			// TODO: Check if collision with ball, and set to collected and pass to player
			pickupAnimAvailable->Update();
			break;
		case PICKUP_ANIM_COLLECTED:
			pickupAnimCollected->Update();
			if( pickupAnimCollected->HasEnded() )
			{
				animationMode = PICKUP_ANIM_COOLDOWN;
				pickupCooldown = 0;
			}
			break;
		case PICKUP_ANIM_COOLDOWN:
			pickupCooldown++;
			if( pickupCooldown >= PICKUP_COOLDOWN_TIME )
			{
				pickupCooldown = 0;
				animationMode = PICKUP_ANIM_WARPIN;
				pickupAnimIn->Start();
				pickupItem = (BattleInventory::Inventory)((rand() % (int)BattleInventory::INVENTORY_PADDLE_DECREASE) + 1);
			}
			break;
	}
}
