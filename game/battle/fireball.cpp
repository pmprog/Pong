
#include "fireball.h"
#include "../../framework/framework.h"
#include "battle.h"
#include "particle.h"

FireBall::FireBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	//ParticleDelay = 0;
}


void FireBall::Update()
{
	ClassicBall::Update();

	//ParticleDelay = (ParticleDelay + 1) % FIREBALL_PARTICLE_DELAY;
	//if( ParticleDelay == 0 )
	//{
		Particle* p = new Particle( al_map_rgb( 192, 160, 64 ), 20, currentArena, new Vector2(Position), new Angle( Direction->ToDegrees() + 180.0f + (rand() % 61) - 31 ), Speed / 2.5f );
		((BattleStage*)currentArena)->AddObject( p );
	//}
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

