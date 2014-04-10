
#include "menu.h"
#include "../framework/framework.h"
#include "../shaders/shaders.h"

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

	Shader* s = new ShaderScanlines( 5, 2, 30 );
	s->Apply( FRAMEWORK->Display_GetBackBuffer() );
	delete s;
}

bool Menu::IsTransition()
{
	return false;
}
