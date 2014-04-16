
#include "player.h"
#include "../../framework/framework.h"

Player::Player( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY )
{
	currentArena = PlayArena;
	roofY = MinimumY;
	floorY = MaximumY;
	Position = new Vector2( StartPosition );

	UpVelocity = 0.0f;
	Size = 128;

	Width = 6;
	Speed = 920.0f / (float)FRAMES_PER_SECOND;
}

Player::~Player()
{
	delete Position;
}

void Player::UpPushed()
{
	up = true;
}

void Player::UpReleased()
{
	up = false;
}

void Player::DownPushed()
{
	down = true;
}

void Player::DownReleased()
{
	down = false;
}

void Player::Update()
{
	UpVelocity = 0.0f;
	if( up && !down )
	{
		UpVelocity = -Speed;
	}
	if( !up && down )
	{
		UpVelocity = Speed;
	}
	Position->Y += UpVelocity;
	if( Position->Y < roofY + (Size / 2) )
	{
		Position->Y = roofY + (Size / 2.0f);
	}
	if( Position->Y > floorY - (Size / 2) )
	{
		Position->Y = floorY - (Size / 2.0f);
	}
}

void Player::Render()
{
	al_draw_filled_rectangle( Position->X - (Width / 2), Position->Y - (Size / 2), Position->X + (Width / 2), Position->Y + (Size / 2), al_map_rgb( 255, 255, 255 ) );
}
