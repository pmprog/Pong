
#include "particle.h"
#include "../../framework/framework.h"
#include "battle.h"

Particle::Particle( ALLEGRO_COLOR Colour, Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	LifeSpan = FRAMES_PER_SECOND / 2;
	particleColour = Colour;
}


void Particle::Update()
{
	ClassicBall::Update();
	LifeSpan--;
	if( LifeSpan <= 0 )
	{
		((BattleStage*)currentArena)->RemoveObject( this );
	}
}

void Particle::Render()
{
	float a = LifeSpan / (FRAMES_PER_SECOND / 2);
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgba_f( particleColour.r, particleColour.g, particleColour.b, a ) );
}
