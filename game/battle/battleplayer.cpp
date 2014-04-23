
#include "battleplayer.h"
#include "battle.h"
#include "fireball.h"
#include "freezeball.h"
#include "cloneball.h"
#include "homingfireball.h"
#include "../../framework/framework.h"

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

	FreezeLevel = 0;
	FreezeTime = 0;
}

BattlePlayer::~BattlePlayer()
{
}

void BattlePlayer::Update()
{

	switch( FreezeLevel )
	{
		case 0:
			Speed = 920.0f / FRAMES_PER_SECOND;
			break;
		case 1:
			Speed = 230.0f / FRAMES_PER_SECOND;
			break;
		case 2:
			Speed = 0.0f;
			break;
	}
	Player::Update();
	if( TargetHealth < Health )
	{
		Health -= 0.1f;
	}
	if( TargetHealth > Health )
	{
		Health += 0.1f;
	}

	// Unfreeze player
	if( FreezeLevel > 0 )
	{
		FreezeTime++;
		if( FreezeTime >= FREEZE_TIME )
		{
			FreezeLevel--;
			FreezeTime = 0;
		}
	}

	// TODO: Fix to use actual inventory
	Angle* attackAngle = currentArena->GetAttackAngle( this );
	if( Inv1Pressed )
	{
		currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, attackAngle, 4.0f ) );
		Inv1Pressed = false;
	}
	if( Inv2Pressed )
	{
		currentArena->AddObject( new HomingFireBall( currentArena->GetOpponent( this ), (Arena*)currentArena, this->Position, attackAngle, 3.0f ) );
		//currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, new Angle( attackAngle->ToDegrees() - 25.0f ), 4.0f ) );
		//currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, new Angle( attackAngle->ToDegrees() + 25.0f ), 4.0f ) );
		Inv2Pressed = false;
	}
	if( Inv3Pressed )
	{
		currentArena->AddObject( new FreezeBall( (Arena*)currentArena, this->Position, attackAngle, 2.0f ) );
		Inv3Pressed = false;
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
