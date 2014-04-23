
#include "homingfireball.h"
#include "../../framework/framework.h"
#include "battle.h"

HomingFireBall::HomingFireBall( Player* TargetPlayer, Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	target = TargetPlayer;
	targetUpdateDelay = 0;
}

void HomingFireBall::Update()
{
	Angle* targetDirection;

	BattleBall::Update();

	targetUpdateDelay++;
	if( targetUpdateDelay >= HOMING_RETARGET_DELAY )
	{
		targetDirection = new Angle( Position->AngleTo( target->Position ) );

		float shortDist = Direction->ShortestAngleTo( targetDirection );
		if( shortDist > HOMING_RETARGET_TURN )
		{
			shortDist = HOMING_RETARGET_TURN;
		}
		if( Direction->ClockwiseShortestTo( targetDirection ) )
		{
			Direction->Add( shortDist );
		} else {
			Direction->Add( -shortDist );
		}

		delete targetDirection;
		targetUpdateDelay = 0;
	}
}

void HomingFireBall::Render()
{
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgb( 220, 128, 255 ) );
}

void HomingFireBall::OnCollision( Player* WithPlayer )
{
	BattlePlayer* ply = (BattlePlayer*)WithPlayer;
	if( ply->FreezeLevel > 0 )
	{
		ply->FreezeLevel--;
		ply->FreezeTime = 0;
	} else {
		ply->TakeDamage( 1 );
	}
	((BattleStage*)currentArena)->RemoveObject( this );
}

void HomingFireBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattleStage*)currentArena)->RemoveObject( this );
}

