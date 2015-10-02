
#include "menu.h"
#include "../framework/framework.h"
#include "../shaders/shaders.h"
#include "../transitions/transitions.h"
#include "classic/classic.h"
#include "battle/battle.h"
#include "settings.h"
#include "menunetwork.h"
#include "assetDefines.h"

#define BALL_RADIUS	10
int Menu::itemSwayOffsets[16] = { 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, -1, -1, -2, -1, -1 };

Menu::Menu()
{
	titleFont = al_load_font( GAME_FONT, 64, 0 );
	itemFont = al_load_font( GAME_FONT, 24, 0 );
	itemFontHeight = al_get_font_line_height( itemFont );

	itemSwayIndex = 0;
	itemSwayDelay = 0;
	selectedItem = 0;
	ballPos = new Vector2( (rand() % (FRAMEWORK->Display_GetWidth() - 24)) + (BALL_RADIUS * 2),	(rand() % (FRAMEWORK->Display_GetHeight() - 24)) + (BALL_RADIUS * 2) );
	ballVel = new Vector2( ((rand() % 2) + 1) * (rand() % 2 == 0 ? 1 : -1) , ((rand() % 2) + 1) * (rand() % 2 == 0 ? 1 : -1) );

	for( int i = 0; i < 10; i++ )
	{
		ballHistory[i] = new Vector2( ballPos );
	}

	scanlinesOn = true;
	greyscaleOn = false;

}

Menu::~Menu()
{
	al_destroy_font( titleFont );
	al_destroy_font( itemFont );
}

void Menu::Begin()
{
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
						FRAMEWORK->ProgramStages->Push( new TransitionStrips( new BattleStage(), 30, 30 ) );
						break;
					case 1:
						FRAMEWORK->ProgramStages->Push( new MenuNetwork() );
						break;
					case 2:
						FRAMEWORK->ProgramStages->Push( new TransitionStrips( new ClassicStage(), 30, 30 ) );
						break;
					case 3:
						FRAMEWORK->ProgramStages->Push( new TransitionTiled( new SettingsStage(), TiledTransitions::SPIRAL_INWARDS, 9, 9 ) );
						break;
					case 4:
						delete FRAMEWORK->ProgramStages->Pop();
						break;
				}
				break;
      case ALLEGRO_KEY_S:
        scanlinesOn = !scanlinesOn;
        break;
      case ALLEGRO_KEY_G:
        greyscaleOn = !greyscaleOn;
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

	ballPos->X += ballVel->X;
	if( ballPos->X < BALL_RADIUS )
	{
		ballPos->X = Maths::Abs( ballPos->X );
		ballVel->X *= -1;
	}
	if( ballPos->X > FRAMEWORK->Display_GetWidth() - BALL_RADIUS )
	{
		ballPos->X = (FRAMEWORK->Display_GetWidth() - BALL_RADIUS) - (ballPos->X - (FRAMEWORK->Display_GetWidth() - BALL_RADIUS));
		ballVel->X *= -1;
	}

	ballPos->Y += ballVel->Y;
	if( ballPos->Y < BALL_RADIUS )
	{
		ballPos->Y = Maths::Abs( ballPos->Y );
		ballVel->Y *= -1;
	}
	if( ballPos->Y > FRAMEWORK->Display_GetHeight() - BALL_RADIUS )
	{
		ballPos->Y = (FRAMEWORK->Display_GetHeight() - BALL_RADIUS) - (ballPos->Y - (FRAMEWORK->Display_GetHeight() - BALL_RADIUS));
		ballVel->Y *= -1;
	}

	for( int i = 0; i < 9; i++ )
	{
		ballHistory[i]->X = ballHistory[i + 1]->X;
		ballHistory[i]->Y = ballHistory[i + 1]->Y;
	}
	ballHistory[9]->X = ballPos->X;
	ballHistory[9]->Y = ballPos->Y;
}

void Menu::Render()
{
	ALLEGRO_COLOR itemCol = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR selCol = al_map_rgb(255, 255, 0);

	al_clear_to_color( al_map_rgb( 64, 80, 128 ) );

	for( int i = 0; i < 10; i++ )
	{
		int a = ((i+1) / 14.0f) * 255;
		al_draw_filled_rectangle( ballHistory[i]->X - BALL_RADIUS, ballHistory[i]->Y - BALL_RADIUS,
				ballHistory[i]->X + BALL_RADIUS, ballHistory[i]->Y + BALL_RADIUS, al_map_rgba( 255, 255, 255, a ) );
	}
	al_draw_filled_rectangle( ballPos->X - BALL_RADIUS, ballPos->Y - BALL_RADIUS,
			ballPos->X + BALL_RADIUS, ballPos->Y + BALL_RADIUS, al_map_rgb( 255, 255, 255 ) );

	al_draw_text( titleFont, al_map_rgb( 255, 255, 255 ), FRAMEWORK->Display_GetWidth() / 2, 40, ALLEGRO_ALIGN_CENTRE, "Battle Pong" );

	int yPos = FRAMEWORK->Display_GetHeight() - (itemFontHeight * 6);

	al_draw_text( itemFont, (selectedItem == 0 ? selCol : itemCol),
			40 + (selectedItem == 0 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Battle (Local PvP)" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 1 ? selCol : itemCol),
			40 + (selectedItem == 1 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Battle (Network)" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 2 ? selCol : itemCol),
			40 + (selectedItem == 2 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Classic (Local PvP)" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 3 ? selCol : itemCol),
			40 + (selectedItem == 3 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Settings" );
	yPos += itemFontHeight;
	al_draw_text( itemFont, (selectedItem == 4 ? selCol : itemCol),
			40 + (selectedItem == 4 ? itemSwayOffsets[itemSwayIndex] : 0), yPos, ALLEGRO_ALIGN_LEFT, "Quit" );
	yPos += itemFontHeight;

  if( scanlinesOn )
  {
    Shader* s = new ShaderScanlines();
    s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
    delete s;
  }


	if( greyscaleOn )
  {
    Shader* s = new ShaderGreyscale();
    s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
    delete s;
  }
}

bool Menu::IsTransition()
{
	return false;
}
