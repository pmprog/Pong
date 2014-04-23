
#include "fireball.h"
#include "../../framework/framework.h"
#include "battle.h"
#include "particle.h"

FireBall::FireBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
}


void FireBall::Update()
{
	BattleBall::Update();

	Particle* p = new Particle( al_map_rgb( 255, 220, 128 ), currentArena, new Vector2(Position), new Angle( Direction->ToDegrees() + 180.0f + (rand() % 41) - 21 ), Speed * 2.0f );
	((BattleStage*)currentArena)->AddObject( p );
}

void FireBall::Render()
{
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgb( 255, 220, 128 ) );
}

void FireBall::OnCollision( Player* WithPlayer )
{
	BattlePlayer* ply = (BattlePlayer*)WithPlayer;
	if( ply->FreezeLevel > 0 )
	{
		ply->FreezeLevel--;
		ply->FreezeTime = 0;
	} else {
		ply->TakeDamage( 2 );
	}
	((BattleStage*)currentArena)->RemoveObject( this );
}

void FireBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattleStage*)currentArena)->RemoveObject( this );
}

