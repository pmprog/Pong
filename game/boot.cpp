
#include "boot.h"
#include "../framework/framework.h"
#include "menu.h"
#include "../transitions/transitions.h"

void BootUp::Begin()
{
	bootBarSize = 0;
	bootBarAdjust = (FRAMEWORK->Display_GetWidth() / (FRAMES_PER_SECOND * 1.5f));
	logoSpriteP = new SpriteSheet( "resources/pmprog.png" );
	logoSpriteF = new SpriteSheet( "resources/foxblock.png" );
	logoFadeIn = 0;
}

void BootUp::Pause()
{
}

void BootUp::Resume()
{
}

void BootUp::Finish()
{
}

void BootUp::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
		} else {
			StartGame();
		}
	}
}

void BootUp::Update()
{
	if( logoFadeIn < 128 )
	{
		logoFadeIn += 4;
	}
	if( bootBarSize < FRAMEWORK->Display_GetWidth() )
	{
		bootBarSize += bootBarAdjust;
	} else {
		StartGame();
		return;
	}
}

void BootUp::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	int qrtWidth = (FRAMEWORK->Display_GetWidth() / 4);
	int hlfHeight = FRAMEWORK->Display_GetHeight() / 2;
	float scale = logoFadeIn / 128.0f;

	logoSpriteP->DrawSprite( 0, qrtWidth - ((logoSpriteP->GetFrame( 0 )->Width * scale) / 2), hlfHeight - ((logoSpriteP->GetFrame( 0 )->Height * scale) / 2), scale, scale, 0 );
	logoSpriteF->DrawSprite( 0, (qrtWidth * 3) - ((logoSpriteF->GetFrame( 0 )->Width * scale) / 2), hlfHeight - ((logoSpriteF->GetFrame( 0 )->Height * scale) / 2), scale, scale, 0 );

	int xPos = (FRAMEWORK->Display_GetWidth() / 2) - (bootBarSize / 2);
	int yPos = FRAMEWORK->Display_GetHeight() - 12;
	al_draw_filled_rectangle( xPos, yPos, xPos + bootBarSize, yPos + 8, al_map_rgb( 255, 128, 0 ) );
}

void BootUp::StartGame()
{
	delete Framework::System->ProgramStages->Pop();
	Framework::System->ProgramStages->Push( new TransitionFadeIn( new Menu(), al_map_rgb( 0, 0, 0 ), 50 ) );

}

bool BootUp::IsTransition()
{
	return false;
}
