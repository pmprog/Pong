
#include "menunetwork.h"
#include "../framework/framework.h"

MenuNetwork::MenuNetwork()
{
}

MenuNetwork::~MenuNetwork()
{
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
}

void MenuNetwork::Render()
{
	FRAMEWORK->ProgramStages->Previous( this )->Render();

	al_draw_filled_rectangle( 10, FRAMEWORK->Display_GetHeight() / 2, FRAMEWORK->Display_GetWidth() - 10, FRAMEWORK->Display_GetHeight() - 10, al_map_rgba( 0, 0, 0, 128 ) );
}

bool MenuNetwork::IsTransition()
{
	return false;
}
