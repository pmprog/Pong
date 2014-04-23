
#include "battleover.h"
#include "../../framework/framework.h"
#include "../../shaders/shaders.h"
#include "../../transitions/transitions.h"
#include "battle.h"

BattleOver::BattleOver(BattleStage* Battle)
{
	battleStage = Battle;
	itemFont = al_load_font( "resources/title.ttf", 64, 0 );
	itemFontHeight = al_get_font_line_height( itemFont );
	slideAngleX = new Angle( 0 );
	slideAngleY = new Angle( 0 );
}

BattleOver::~BattleOver()
{
	al_destroy_font( itemFont );
	delete slideAngleX;
	delete slideAngleY;
	delete battleStage;
}

void BattleOver::Begin()
{
	FRAMEWORK->ProgramStages->Remove( battleStage );
}

void BattleOver::Pause()
{
}

void BattleOver::Resume()
{
}

void BattleOver::Finish()
{
}

void BattleOver::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::NORTHWEST_TO_SOUTHEAST, 7, 7 ) );
	}
}

void BattleOver::Update()
{
	slideAngleX->Add( 4.0f );
	slideAngleY->Add( 8.0f );
}

void BattleOver::Render()
{
	al_clear_to_color( al_map_rgb( 128, 128, 192 ) );

	al_draw_filled_rectangle( 0, (FRAMEWORK->Display_GetHeight() / 2) - (itemFontHeight / 1.5f), FRAMEWORK->Display_GetWidth(), (FRAMEWORK->Display_GetHeight() / 2) + (itemFontHeight / 1.5f), al_map_rgb( 64, 96, 128 ) );
	//al_draw_text( itemFont, al_map_rgb( 255, 255, 255 ), FRAMEWORK->Display_GetWidth() / 2, (FRAMEWORK->Display_GetHeight() / 2) - (itemFontHeight / 2), ALLEGRO_ALIGN_CENTER, "Winner" );
	al_draw_text( itemFont, al_map_rgb( 255, 255, 255 ), (FRAMEWORK->Display_GetWidth() / 2) + (slideAngleX->Sine() * 4.5f), (FRAMEWORK->Display_GetHeight() / 2) - (itemFontHeight / 2)  + (slideAngleY->Sine() * 7.0f), ALLEGRO_ALIGN_CENTER, "Player 1 (Left)" );

	Shader* s = new ShaderScanlines();
	s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
	delete s;
}

bool BattleOver::IsTransition()
{
	return false;
}
