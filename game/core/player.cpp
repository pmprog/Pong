
#include "player.h"
#include "../../framework/framework.h"

Player::Player( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY )
{
	drawColour = al_map_rgb(255, 255, 255);
	targetColour = al_map_rgb(255, 255, 255);

	currentArena = PlayArena;
	roofY = MinimumY;
	floorY = MaximumY;
	Position = new Vector2( StartPosition );

	UpVelocity = 0.0f;
	Size = 128;

	UpPressed = false;
	DownPressed = false;

	Width = 16;
	Speed = 920.0f / (float)FRAMES_PER_SECOND;
}

Player::~Player()
{
	delete Position;
}

void Player::Update()
{
	UpVelocity = 0.0f;
	if( UpPressed && !DownPressed )
	{
		UpVelocity = -Speed;
	}
	if( !UpPressed && DownPressed )
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

	// Colour merge
	if( targetColour.r > drawColour.r )
	{
		drawColour.r += 0.01f;
		if( targetColour.r < drawColour.r )
		{
			drawColour.r = targetColour.r;
		}
	}
	if( targetColour.r < drawColour.r )
	{
		drawColour.r -= 0.01f;
		if( targetColour.r > drawColour.r )
		{
			drawColour.r = targetColour.r;
		}
	}
	if( targetColour.g > drawColour.g )
	{
		drawColour.g += 0.01f;
		if( targetColour.g < drawColour.g )
		{
			drawColour.g = targetColour.g;
		}
	}
	if( targetColour.g < drawColour.g )
	{
		drawColour.g -= 0.01f;
		if( targetColour.g > drawColour.g )
		{
			drawColour.g = targetColour.g;
		}
	}
	if( targetColour.b > drawColour.b )
	{
		drawColour.b += 0.01f;
		if( targetColour.b < drawColour.b )
		{
			drawColour.b = targetColour.b;
		}
	}
	if( targetColour.b < drawColour.b )
	{
		drawColour.b -= 0.01f;
		if( targetColour.b > drawColour.b )
		{
			drawColour.b = targetColour.b;
		}
	}
	if( targetColour.a > drawColour.a )
	{
		drawColour.a += 0.01f;
		if( targetColour.a < drawColour.a )
		{
			drawColour.a = targetColour.a;
		}
	}
	if( targetColour.a < drawColour.a )
	{
		drawColour.a -= 0.01f;
		if( targetColour.a > drawColour.a )
		{
			drawColour.a = targetColour.a;
		}
	}
}

void Player::Render()
{
	al_draw_filled_rectangle( Position->X - (Width / 2), Position->Y - (Size / 2), Position->X + (Width / 2), Position->Y + (Size / 2), drawColour );
	// al_draw_line( Position->X - (Width / 2), Position->Y - (Size / 2), Position->X + (Width / 2), Position->Y + (Size / 2), al_map_rgb( 255, 255, 255 ), 1 );
}
