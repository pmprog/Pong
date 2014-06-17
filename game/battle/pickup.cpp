
#include "pickup.h"

Pickup::Pickup( BattleStage* PlayArena, Vector2* StartPosition )
{
	gameArena = PlayArena;
	spawnPosition = new Vector2( StartPosition );
	
	// TODO: pickupItem =

	pickupSprites = new SpriteSheet( "resources/pickups.png", 32, 32 );
	pickupAnimIn = new Animation( pickupSprites, false, 10 );
	pickupAnimAvailable = new Animation( pickupSprites, true, 10 );
	pickupAnimCollected = new Animation( pickupSprites, false, 10 );

	animationMode = PICKUP_ANIM_WARPIN;
	pickupAnimIn->Start();
	pickupCooldown = 0;
}

void Pickup::Render()
{
	switch( animationMode )
	{
		case PICKUP_ANIM_WARPIN:
			break;
		case PICKUP_ANIM_AVAILABLE:
			break;
		case PICKUP_ANIM_COLLECTED:
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
			if( pickupCooldown == PICKUP_COOLDOWN_TIME )
			{
				animationMode = PICKUP_ANIM_WARPIN;
				pickupAnimIn->Start();
				// TODO: pickupItem =
			}
			break;
	}
}
