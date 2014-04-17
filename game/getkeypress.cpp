
#include "getkeypress.h"
#include "../framework/framework.h"
#include "menu.h"
#include "../transitions/transitions.h"

GetKeyPress::GetKeyPress()
{
	itemFont = al_load_font( "resources/title.ttf", 24, 0 );
	itemFontHeight = al_get_font_line_height( itemFont );
}

GetKeyPress::~GetKeyPress()
{
	al_destroy_font( itemFont );
}

void GetKeyPress::Begin()
{
	FadeIn = 0;
}

void GetKeyPress::Pause()
{
}

void GetKeyPress::Resume()
{
}

void GetKeyPress::Finish()
{
}

void GetKeyPress::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
		} else {
			Event* ev = new Event();
			ev->Type = EVENT_USER;
			ev->Data.Keyboard.KeyCode = e->Data.Keyboard.KeyCode;
			ev->Data.Keyboard.Modifiers = e->Data.Keyboard.Modifiers;
			FRAMEWORK->PushEvent(ev);
			delete FRAMEWORK->ProgramStages->Pop();
		}
	}
}

void GetKeyPress::Update()
{
	if( FadeIn < 255 )
	{
		FadeIn += 17;
	}
}

void GetKeyPress::Render()
{
	FRAMEWORK->ProgramStages->Previous()->Render();

	al_draw_filled_rectangle( 0, 0, FRAMEWORK->Display_GetWidth(), FRAMEWORK->Display_GetHeight(), al_map_rgba( 0, 0, 0, FadeIn / 1.5f ) );

	al_draw_filled_rectangle( 0, (FRAMEWORK->Display_GetHeight() / 2) - 30, FRAMEWORK->Display_GetWidth(), (FRAMEWORK->Display_GetHeight() / 2) + 30, al_map_rgba( 64, 96, 128, FadeIn ) );
	al_draw_text( itemFont, al_map_rgba( 255, 255, 255, FadeIn ), FRAMEWORK->Display_GetWidth() / 2, (FRAMEWORK->Display_GetHeight() / 2) - (itemFontHeight / 2), ALLEGRO_ALIGN_CENTER, "Press desired key" );
}

bool GetKeyPress::IsTransition()
{
	return false;
}
