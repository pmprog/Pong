
#include "menu.h"
#include "../framework/framework.h"

void Menu::Begin()
{
}

void Menu::Pause()
{
}

void Menu::Resume()
{
}

void Menu::Finish()
{
}

void Menu::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
		}
	}
}

void Menu::Update()
{
}

void Menu::Render()
{
	al_clear_to_color( al_map_rgb( 64, 80, 128 ) );
}

bool Menu::IsTransition()
{
	return false;
}
