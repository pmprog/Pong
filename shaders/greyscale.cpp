
#include "greyscale.h"
#include "../framework/framework.h"

void ShaderGreyscale::Apply( ALLEGRO_BITMAP* Target )
{
	ALLEGRO_BITMAP* o = FRAMEWORK->Display_GetCurrentTarget();

	int imgW = al_get_bitmap_width( Target );
	int imgH = al_get_bitmap_height( Target );

	ALLEGRO_LOCKED_REGION* rgn = al_lock_bitmap( Target, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_READWRITE );

	FRAMEWORK->Display_SetTarget( Target );

	for( int y = 0; y < imgH; y++ )
	{
		for( int x = 0; x < imgW; x++ )
		{
			ALLEGRO_COLOR c = al_get_pixel( Target, x, y );
			c.r = (c.r * 0.35f) + (c.g * 0.5f) + (c.b * 0.15f);
			c.g = c.r;
			c.b = c.r;
			al_put_pixel( x, y, c );
		}
	}

	al_unlock_bitmap( Target );

	FRAMEWORK->Display_SetTarget( o );
}
