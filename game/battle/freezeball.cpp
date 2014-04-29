
#include "freezeball.h"
#include "../../framework/framework.h"
#include "battle.h"
#include "particle.h"

FreezeBall::FreezeBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	ParticleDelay = 0;
}


void FreezeBall::Update()
{
	ClassicBall::Update();

	ParticleDelay = (ParticleDelay + 1) % FREEZEBALL_PARTICLE_DELAY;
	if( ParticleDelay == 0 )
	{
		float ax = rand() % 90;
		float sx = ((rand() % 30) / 10.0f) + 1.0f;
		Particle* p = new Particle( al_map_rgb( 64, 160, 192 ), 20, currentArena, new Vector2(Position), new Angle( Direction->ToDegrees() + 180.0f + ax ), Speed / sx );
		((BattleStage*)currentArena)->AddObject( p );
		p = new Particle( al_map_rgb( 64, 160, 192 ), 20, currentArena, new Vector2(Position), new Angle( Direction->ToDegrees() + 180.0f - ax ), Speed / sx );
		((BattleStage*)currentArena)->AddObject( p );
	}
}

void FreezeBall::Render()
{
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgb( 128, 192, 255 ) );
}

void FreezeBall::OnCollision( Player* WithPlayer )
{
	((BattlePlayer*)WithPlayer)->Freeze();
	((BattleStage*)currentArena)->RemoveObject( this );
}

void FreezeBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattleStage*)currentArena)->RemoveObject( this );
}

