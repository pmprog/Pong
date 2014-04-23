
#include "battleplayer.h"
#include "battle.h"
#include "fireball.h"
#include "cloneball.h"

BattlePlayer::BattlePlayer( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY ) : Player( PlayArena, StartPosition, MinimumY, MaximumY )
{
	currentArena = (BattleStage*)PlayArena;
	MaxHealth = 10;
	TargetHealth = 10;
	Health = 0.1f;
	TargetSize = Size;

	SendPressed = false;
	Inv1Pressed = false;
	Inv2Pressed = false;
	Inv3Pressed = false;

	Inventory[0] = 0;
	Inventory[1] = 0;
	Inventory[2] = 0;
}

BattlePlayer::~BattlePlayer()
{
}

void BattlePlayer::Update()
{
	Player::Update();
	if( TargetHealth < Health )
	{
		Health -= 0.1f;
	}
	if( TargetHealth > Health )
	{
		Health += 0.1f;
	}

	// TODO: Fix to use actual inventory
	if( Inv1Pressed )
	{
		currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, new Angle( 90 ), 4.0f ) );
		Inv1Pressed = false;
	}
}

void BattlePlayer::TakeDamage( int Amount )
{
	TargetHealth -= Amount;
	if( TargetHealth < 0 )
	{
		TargetHealth = 0;
	}
}
