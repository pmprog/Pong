
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
	PackedARGB8888* gsCol;
	int imgW = al_get_bitmap_width( Target );
	int imgH = al_get_bitmap_height( Target );
	int linesForScan = nonScanLineWidth + scanLineWidth;

	ALLEGRO_LOCKED_REGION* rgn = al_lock_bitmap( Target, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_READWRITE );

	for( int y = 0; y < imgH; y++ )
	{
		if( (y % linesForScan) >= nonScanLineWidth )
		{
			for( int x = 0; x < imgW; x++ )
			{
				PackedARGB8888* pxRow = (PackedARGB8888*)((char*)rgn->data + (y * rgn->pitch));
				gsCol = &pxRow[x];
				gsCol->r = (gsCol->r > scanDecrease ? gsCol->r - scanDecrease : 0);
				gsCol->g = (gsCol->g > scanDecrease ? gsCol->g - scanDecrease : 0);
				gsCol->b = (gsCol->b > scanDecrease ? gsCol->b - scanDecrease : 0);
			}
		}
	}

	al_unlock_bitmap( Target );

}
