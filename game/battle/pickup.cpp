
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
	pickupItem = (BattleInventory::Inventory)((rand() % ((int)BattleInventory::INVENTORY_PADDLE_EOL-1)) + 1);

	pickupSprites = new SpriteSheet( "resources/pickups.png", PICKUP_GRAPHIC_SIZE, PICKUP_GRAPHIC_SIZE );
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
	Animation* cur = 0;
	switch( animationMode )
	{
		case PICKUP_ANIM_WARPIN:
			cur = pickupAnimIn;
			break;
		case PICKUP_ANIM_AVAILABLE:
			cur = pickupAnimAvailable;
			break;
		case PICKUP_ANIM_COLLECTED:
			cur = pickupAnimCollected;
			break;
	}
	if( cur != 0 )
	{
		cur->DrawFrame( spawnPosition->X - (PICKUP_GRAPHIC_SIZE/2), spawnPosition->Y - (PICKUP_GRAPHIC_SIZE/2) );
	}
}

void Pickup::Update()
{
	BattleBall* ball;
	switch( animationMode )
	{
		case PICKUP_ANIM_WARPIN:
			ball = gameArena->GetBall();
			if( ball->LastHitBy != 0 && spawnPosition->DistanceTo( ball->Position ) < (float)PICKUP_GRAPHIC_SIZE )
			{
				GiveItem( (BattlePlayer*)ball->LastHitBy );
				animationMode = PICKUP_ANIM_COLLECTED;
				pickupAnimCollected->Start();
			} else {
				pickupAnimIn->Update();
				if( pickupAnimIn->HasEnded() )
				{
					animationMode = PICKUP_ANIM_AVAILABLE;
					pickupAnimAvailable->Start();
				}
			}
			break;
		case PICKUP_ANIM_AVAILABLE:
			ball = gameArena->GetBall();
			if( ball->LastHitBy != 0 && spawnPosition->DistanceTo( ball->Position ) < (float)PICKUP_GRAPHIC_SIZE )
			{
				GiveItem( (BattlePlayer*)ball->LastHitBy );
				animationMode = PICKUP_ANIM_COLLECTED;
				pickupAnimCollected->Start();
			} else {
				pickupAnimAvailable->Update();
			}
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
				pickupItem = (BattleInventory::Inventory)((rand() % ((int)BattleInventory::INVENTORY_PADDLE_EOL-1)) + 1);
			}
			break;
	}
}

void Pickup::GiveItem( BattlePlayer* ToPlayer )
{
	for( int i = 0; i < 3; i++ )
	{
		if( ToPlayer->Inventory[i] ==	BattleInventory::INVENTORY_NONE )
		{
			ToPlayer->Inventory[i] = pickupItem;
			return;
		}
	}
}
