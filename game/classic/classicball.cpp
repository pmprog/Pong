
#include "classicball.h"
#include "../core/player.h"

ClassicBall::ClassicBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : Projectile( PlayArena, StartPosition, StartDirection, StartSpeed )
{
	Radius = 8;
	spin = 0;
}

ClassicBall::~ClassicBall()
{
}

void ClassicBall::Update()
{
	Projectile::Update();
	if( spin != 0 )
	{
		Direction->RotateShortestBy( (spin > 0 ? 180.0f : 0.0f), Maths::Abs(spin) );
		spin = 0;
	}

	// Stuck ball, get it moving
	if( Direction->ShortestAngleTo( 0.0f ) < 10.0f || Direction->ShortestAngleTo( 180.0f ) < 10.0f )
	{
		Direction->Add( (float)((rand() % 25) - 13) );
	}
}

void ClassicBall::Render()
{
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgb( 255, 255, 255 ) );
}

void ClassicBall::OnCollision( Player* WithPlayer )
{
	if( WithPlayer->DownPressed && !WithPlayer->UpPressed )
	{
		spin = Maths::Min( Direction->ShortestAngleTo( 180.0f ), 40.0f );
	}
	if( !WithPlayer->DownPressed && WithPlayer->UpPressed )
	{
		spin = -Maths::Min( Direction->ShortestAngleTo( 0.0f ), 40.0f );
	}
}
