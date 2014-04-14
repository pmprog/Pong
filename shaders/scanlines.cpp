
#include "scanlines.h"
#include "../framework/framework.h"

ShaderScanlines::ShaderScanlines()
{
	nonScanLineWidth = 4;
	scanLineWidth = 2;
	scanDecrease = 32;
}

ShaderScanlines::ShaderScanlines(int NonScanWidth, int ScanWidth, int ScanDecrease)
{
	nonScanLineWidth = NonScanWidth;
	scanLineWidth = ScanWidth;
	scanDecrease = ScanDecrease;
}

void ShaderScanlines::Apply( ALLEGRO_BITMAP* Target )
{
	ALLEGRO_BITMAP* o = FRAMEWORK->Display_GetCurrentTarget();

	int imgW = al_get_bitmap_width( Target );
	int imgH = al_get_bitmap_height( Target );
	int linesForScan = nonScanLineWidth + scanLineWidth;
	float decCol = scanDecrease / 255.0f;

	ALLEGRO_LOCKED_REGION* rgn = al_lock_bitmap( Target, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_READWRITE );

	FRAMEWORK->Display_SetTarget( Target );

	for( int y = 0; y < imgH; y++ )
	{
		if( (y % linesForScan) >= nonScanLineWidth )
		{
			for( int x = 0; x < imgW; x++ )
			{
				ALLEGRO_COLOR c = al_get_pixel( Target, x, y );
				c.r = (c.r > decCol ? c.r - decCol : 0.0f);
				c.g = (c.g > decCol ? c.g - decCol : 0.0f);
				c.b = (c.b > decCol ? c.b - decCol : 0.0f);
				al_put_pixel( x, y, c );
			}
		}
	}

	al_unlock_bitmap( Target );
	FRAMEWORK->Display_SetTarget( o );
}
