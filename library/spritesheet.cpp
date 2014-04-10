
#include "spritesheet.h"

SpriteSheet::SpriteSheet( std::string Filename )
{
	sheet = al_load_bitmap( Filename.c_str() );
}

SpriteSheet::SpriteSheet( std::string Filename, int FrameWidth, int FrameHeight )
{
	sheet = al_load_bitmap( Filename.c_str() );

	for( int y = 0; y < al_get_bitmap_height( sheet ); y += FrameHeight )
	{
		for( int x = 0; x < al_get_bitmap_width( sheet ); x += FrameWidth )
		{
			AddSprite( x, y, FrameWidth, FrameHeight );
		}
	}
}

SpriteSheet::~SpriteSheet()
{
	al_destroy_bitmap( sheet );
}

ALLEGRO_BITMAP* SpriteSheet::GetSheet()
{
	return sheet;
}

int SpriteSheet::AddSprite( int FrameX, int FrameY, int FrameWidth, int FrameHeight )
{
	/*
	SDL_Rect* r = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
	r->x = FrameX;
	r->y = FrameY;
	r->w = FrameWidth;
	r->h = FrameHeight;
	frames.push_back( r );
	*/
	return frames.size() - 1;
}

void SpriteSheet::DrawSprite( int FrameNumber, int ScreenX, int ScreenY, float ScaleX, float ScaleY, Angle* Rotation )
{
	if( FrameNumber < 0 || FrameNumber >= (int)frames.size() )
	{
		return;
	}

	/*
	SDL_Rect* r = frames.at( FrameNumber );
	if( Rotation == 0 )
	{
		spRotozoomSurfacePart( ScreenX, ScreenY, -1, sheet, r->x, r->y, r->w,	r->h, ScaleX * SP_ONE, ScaleY * SP_ONE, 0 );
	} else {
		spRotozoomSurfacePart( ScreenX, ScreenY, -1, sheet, r->x, r->y, r->w,	r->h, ScaleX * SP_ONE, ScaleY * SP_ONE, Rotation->ToRadiansSparrow() );
	}
	*/
}

