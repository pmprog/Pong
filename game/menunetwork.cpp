
#include "menunetwork.h"
#include "../framework/framework.h"
#include "assetDefines.h"

MenuNetwork::MenuNetwork()
{
	itemFont = al_load_font( GAME_FONT, 24, 0 );
	itemFontHeight = al_get_font_line_height( itemFont );
	fadeDown = 0;
	slideIn = 0;
	selectedItem = 0;
}

MenuNetwork::~MenuNetwork()
{
	al_destroy_font( itemFont );
}


void MenuNetwork::Begin()
{
}

void MenuNetwork::Pause()
{
}

void MenuNetwork::Resume()
{
}

void MenuNetwork::Finish()
{
}

void MenuNetwork::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{

		switch( e->Data.Keyboard.KeyCode )
		{
			case ALLEGRO_KEY_ESCAPE:
				delete FRAMEWORK->ProgramStages->Pop();
				break;
		}
	}
}

void MenuNetwork::Update()
{
	FRAMEWORK->ProgramStages->Previous( this )->Update();
	if( fadeDown < 128 )
	{
		fadeDown++;
	}
	if( slideIn < FRAMEWORK->Display_GetWidth() / 2 )
	{
		slideIn += 16;
		if( slideIn > FRAMEWORK->Display_GetWidth() / 2 )
		{
			slideIn = FRAMEWORK->Display_GetWidth() / 2;
		}
	}
}

void MenuNetwork::Render()
{
	ALLEGRO_COLOR itemCol = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR selCol = al_map_rgb(255, 255, 0);

	int slideY = slideIn; // / 2;
	if( slideY > (FRAMEWORK->Display_GetHeight() / 3) - 20 )
	{
		slideY = (FRAMEWORK->Display_GetHeight() / 3) - 20;
	}

	FRAMEWORK->ProgramStages->Previous( this )->Render();
	al_draw_filled_rectangle( 0, 0, FRAMEWORK->Display_GetWidth(), FRAMEWORK->Display_GetHeight(), al_map_rgba( 0, 0, 0, fadeDown ) );
	al_draw_filled_rectangle( 20, FRAMEWORK->Display_GetHeight() - 20 - slideY, 20 + slideIn, FRAMEWORK->Display_GetHeight() - 20, al_map_rgb( 64, 80, 128 ) );
	al_draw_rectangle( 20, FRAMEWORK->Display_GetHeight() - 20 - slideY, 20 + slideIn, FRAMEWORK->Display_GetHeight() - 20, al_map_rgb( 128, 160, 255 ), 3 );

	if( slideIn == FRAMEWORK->Display_GetWidth() / 2 )
	{
		int yPos = ((FRAMEWORK->Display_GetHeight() / 3) * 2) + 30;
		al_draw_text( itemFont, (selectedItem == 0 ? selCol : itemCol), 40, yPos, ALLEGRO_ALIGN_LEFT, "Battle (Local PvP)" );
		yPos += itemFontHeight + 2;
		al_draw_text( itemFont, (selectedItem == 1 ? selCol : itemCol), 40, yPos, ALLEGRO_ALIGN_LEFT, "Battle (Local PvP)" );
		yPos += itemFontHeight + 2;
		al_draw_text( itemFont, (selectedItem == 2 ? selCol : itemCol), 40, yPos, ALLEGRO_ALIGN_LEFT, "Battle (Local PvP)" );
	}
}

bool MenuNetwork::IsTransition()
{
	return false;
}
