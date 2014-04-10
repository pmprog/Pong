
#include "boot.h"
#include "../framework/framework.h"

void BootUp::Begin()
{
	bootBarSize = 0;
	bootBarAdjust = (FRAMEWORK->Display_GetWidth() / (FRAMES_PER_SECOND * 1.5));
	logoSpriteP = new SpriteSheet( "Resource/pmprog.png", 204, 200 );
	logoSpriteF = new SpriteSheet( "Resource/foxblock.png", 204, 200 );
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

	logoSpriteP->DrawSprite( 0, (FRAMEWORK->Display_GetWidth() / 4), FRAMEWORK->Display_GetHeight() / 2, logoFadeIn / 128.0f, logoFadeIn / 128.0f, 0 );
	logoSpriteF->DrawSprite( 0, (FRAMEWORK->Display_GetWidth() / 4) * 3, FRAMEWORK->Display_GetHeight() / 2, logoFadeIn / 128.0f, logoFadeIn / 128.0f, 0 );

	int xPos = (FRAMEWORK->Display_GetWidth() / 2) - (bootBarSize / 2);
	int yPos = FRAMEWORK->Display_GetHeight() - 12;
	al_draw_filled_rectangle( xPos, yPos, xPos + bootBarSize, yPos + 8, al_map_rgb( 255, 128, 0 ) );
}

void BootUp::StartGame()
{
	delete Framework::System->ProgramStages->Pop();
	// TODO: Boot stage
	// Framework::System->ProgramStages->Push( new TransitionFadeIn( spGetFastRGB(0, 0, 0), new Menu(), 50 ) );
}

bool BootUp::IsTransition()
{
	return false;
}
