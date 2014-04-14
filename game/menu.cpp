
#include "menu.h"
#include "../framework/framework.h"
#include "../shaders/shaders.h"

int Menu::itemSwayOffsets[16] = { 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, -1, -1, -2, -1, -1 };

void Menu::Begin()
{
	titleFont = al_load_font( "resources/title.ttf", 64, 0 );
	itemFont = al_load_font( "resources/title.ttf", 24, 0 );
	itemFontHeight = al_get_font_line_height( itemFont );

	selectedItem = 0;

	itemSwayIndex = 0;
	itemSwayDelay = 0;

}

void Menu::Pause()
{
}

void Menu::Resume()
{
}

void Menu::Finish()
{
	al_destroy_font( titleFont );
	al_destroy_font( itemFont );
}

void Menu::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{

		switch( e->Data.Keyboard.KeyCode )
		{
			case ALLEGRO_KEY_ESCAPE:
				delete FRAMEWORK->ProgramStages->Pop();
				break;
			case ALLEGRO_KEY_UP:
				selectedItem = (selectedItem + 4) % 5;
				itemSwayIndex = 0;
				break;
			case ALLEGRO_KEY_DOWN:
				selectedItem = (selectedItem + 1) % 5;
				itemSwayIndex = 0;
				break;
			case ALLEGRO_KEY_ENTER:
			case ALLEGRO_KEY_SPACE:
			case ALLEGRO_KEY_PGDN:
			case ALLEGRO_KEY_END:
				switch( selectedItem )
				{
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						delete FRAMEWORK->ProgramStages->Pop();
						break;
				}
				break;
		}
	}
}

void Menu::Update()
{
	itemSwayDelay = (itemSwayDelay + 1) % 3;
	if( itemSwayDelay == 0 )
	{
		itemSwayIndex = (itemSwayIndex + 1) % 16;
	}
}

void Menu::Render()
{
	ALLEGRO_COLOR itemCol = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR selCol = al_map_rgb(255, 255, 0);

	al_clear_to_color( al_map_rgb( 64, 80, 128 ) );

	al_draw_text( titleFont, al_map_rgb( 255, 255, 255 ), FRAMEWORK->Display_GetWidth() / 2, 40, ALLEGRO_ALIGN_CENTRE, "Battle Pong" );

	int yPos = FRAMEWORK->Display_GetHeight() - (itemFontHeight * 6);

	al_draw_text( itemFont, (selectedItem == 0 ? selCol : itemCol), 40 + (selectedItem == 0 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Single Player" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 1 ? selCol : itemCol), 40 + (selectedItem == 1 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Multiplayer (Local)" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 2 ? selCol : itemCol), 40 + (selectedItem == 2 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Multiplayer (Network)" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 3 ? selCol : itemCol), 40 + (selectedItem == 3 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Settings" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 4 ? selCol : itemCol), 40 + (selectedItem == 4 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Quit" );
	yPos += itemFontHeight;

	Shader* s = new ShaderScanlines( 5, 2, 24 );
	s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
	delete s;
}

bool Menu::IsTransition()
{
	return false;
}
