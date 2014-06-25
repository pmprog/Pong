
#include "battleplayer.h"
#include "battle.h"
#include "fireball.h"
#include "freezeball.h"
#include "cloneball.h"
#include "homingfireball.h"
#include "sendball.h"
#include "../../framework/framework.h"

BattlePlayer::BattlePlayer( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY ) : Player( PlayArena, StartPosition, MinimumY, MaximumY )
{
	currentArena = (BattleStage*)PlayArena;
	MaxHealth = 10;
	TargetHealth = 10;
	Health = 0.1f;
	TargetSize = Size;
	SizeDelay = 0;

	ReverseControlTime = 0;

	SendPressed = false;
	Inv1Pressed = false;
	Inv2Pressed = false;
	Inv3Pressed = false;

	Inventory[0] = BattleInventory::INVENTORY_NONE;
	Inventory[1] = BattleInventory::INVENTORY_NONE;
	Inventory[2] = BattleInventory::INVENTORY_NONE;

	FreezeLevel = 0;
	FreezeTime = 0;

	IsNetworkPlayer = false;
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
	if( ReverseControlTime > 0 )
	{
		Speed *= -1;
	}
	Player::Update();
	if( ReverseControlTime > 0 )
	{
		Speed *= -1;
		ReverseControlTime--;
	}
	if( TargetHealth < Health )
	{
		Health -= 0.1f;
	}
	if( TargetHealth > Health )
	{
		Health += 0.1f;
	}
	if( TargetSize < Size )
	{
		SizeDelay = (SizeDelay + 1) % SIZING_DELAY;
		if( SizeDelay == 0 )
		{
			Size--;
		}
	}
	if( TargetSize > Size )
	{
		SizeDelay = (SizeDelay + 1) % SIZING_DELAY;
		if( SizeDelay == 0 )
		{
			Size++;
		}
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
		setFreezeColour();
	}

	if( SendPressed )
	{
		if( Inv1Pressed )
		{
			SendInventory( 0 );
		}
		if( Inv2Pressed )
		{
			SendInventory( 1 );
		}
		if( Inv3Pressed )
		{
			SendInventory( 2 );
		}
	} else {
		if( Inv1Pressed )
		{
			UseInventory( 0 );
		}
		if( Inv2Pressed )
		{
			UseInventory( 1 );
		}
		if( Inv3Pressed )
		{
			UseInventory( 2 );
		}
	}
}

void BattlePlayer::setFreezeColour()
{
	switch( FreezeLevel )
	{
		case 0:
			targetColour = al_map_rgb( 255, 255, 255 );
			break;
		case 1:
			targetColour = al_map_rgb( 128, 192, 255 );
			break;
		case 2:
			targetColour = al_map_rgb( 64, 128, 220 );
			break;
	}
}

void BattlePlayer::Freeze()
{
	if( FreezeLevel < 2 )
	{
		FreezeLevel++;
		FreezeTime = 0;
	}
	setFreezeColour();
}

void BattlePlayer::Burn()
{
	drawColour = al_map_rgb( 255, 220, 128 );
	if( FreezeLevel > 0 )
	{
		FreezeLevel--;
		FreezeTime = 0;
		setFreezeColour();
	} else {
		TakeDamage( 2 );
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

void BattlePlayer::UseInventory( int Slot )
{
	Angle* attackAngle = 0;
	BattleBall* b = 0;
	Vector2* v = 0;
	switch( Inventory[Slot] )
	{
		case BattleInventory::INVENTORY_FIREBALL:
			attackAngle = currentArena->GetAttackAngle( this );
			currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, attackAngle, 4.0f ) );
			break;
		case BattleInventory::INVENTORY_TRIFIRE:
			attackAngle = currentArena->GetAttackAngle( this );
			currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, attackAngle, 4.0f ) );
			currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, new Angle( attackAngle->ToDegrees() - 25.0f ), 4.0f ) );
			currentArena->AddObject( new FireBall( (Arena*)currentArena, this->Position, new Angle( attackAngle->ToDegrees() + 25.0f ), 4.0f ) );
			break;
		case BattleInventory::INVENTORY_HOMING:
			attackAngle = currentArena->GetAttackAngle( this );
			currentArena->AddObject( new HomingFireBall( currentArena->GetOpponent( this ), (Arena*)currentArena, this->Position, attackAngle, 3.0f ) );
			break;
		case BattleInventory::INVENTORY_FREEZE:
			attackAngle = currentArena->GetAttackAngle( this );
			currentArena->AddObject( new FreezeBall( (Arena*)currentArena, this->Position, attackAngle, 2.0f ) );
			break;
		case BattleInventory::INVENTORY_REVERSE_BALL_VERT:
			b = currentArena->GetBall();
			v = b->Direction->ToVector();
			v->Y *= -1;
			delete b->Direction;
			b->Direction = v->ToAngle();
			delete v;
			break;
		case BattleInventory::INVENTORY_REVERSE_BALL_HORZ:
			b = currentArena->GetBall();
			v = b->Direction->ToVector();
			v->X *= -1;
			delete b->Direction;
			b->Direction = v->ToAngle();
			delete v;
			break;
		case BattleInventory::INVENTORY_PADDLE_INCREASE:
			TargetSize += SIZING_STEP;
			if( TargetSize > SIZING_MAX )
			{
				TargetSize = SIZING_MAX;
			}
			break;
		case BattleInventory::INVENTORY_PADDLE_DECREASE:
			TargetSize -= SIZING_STEP;
			if( TargetSize < SIZING_MIN )
			{
				TargetSize = SIZING_MIN;
			}
			break;
		case BattleInventory::INVENTORY_PADDLE_REVERSE_CONTROLS:
			ReverseControlTime = REVERSE_TIME;
			UpPressed = false;
			DownPressed = false;
			break;
	}
	Inventory[Slot] = BattleInventory::INVENTORY_NONE;
}

void BattlePlayer::SendInventory( int Slot )
{
	Angle* attackAngle = 0;
	if( Inventory[Slot] != 0 )
	{
		Angle* attackAngle = currentArena->GetAttackAngle( this );
		currentArena->AddObject( new SendBall( Inventory[Slot], (Arena*)currentArena, this->Position, attackAngle, 2.0f ) );
	}
	Inventory[Slot] = BattleInventory::INVENTORY_NONE;
}
