
#include "particle.h"
#include "../../framework/framework.h"
#include "battle.h"

Particle::Particle( ALLEGRO_COLOR Colour, int LifeTime, Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	MaxLife = LifeTime;
	LifeSpan = LifeTime;
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
	float a = LifeSpan / (float)MaxLife;
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgba_f( particleColour.r, particleColour.g, particleColour.b, a ) );
}
