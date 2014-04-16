
#include "classicball.h"
#include "../core/player.h"

ClassicBall::ClassicBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : Projectile( PlayArena, StartPosition, StartDirection, StartSpeed )
{
	Radius = 8;
}

ClassicBall::~ClassicBall()
{
}

void ClassicBall::Render()
{
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgb( 255, 255, 255 ) );
}
