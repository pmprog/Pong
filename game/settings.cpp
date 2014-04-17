
#include "settings.h"
#include "../framework/framework.h"
#include "../shaders/shaders.h"
#include "../transitions/transitions.h"
#include "getkeypress.h"

SettingsStage::SettingsStage()
{
	titleFont = al_load_font( "resources/title.ttf", 32, 0 );
	titleFontHeight = al_get_font_line_height( titleFont );
	itemFont = al_load_font( "resources/title.ttf", 24, 0 );
	itemFontHeight = al_get_font_line_height( itemFont );

	selectedItem = 0;
	scrollPosition = 0;
}

SettingsStage::~SettingsStage()
{
	al_destroy_font( titleFont );
	al_destroy_font( itemFont );
}

void SettingsStage::Begin()
{
}

void SettingsStage::Pause()
{
}

void SettingsStage::Resume()
{
}

void SettingsStage::Finish()
{
}

void SettingsStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{

		switch( e->Data.Keyboard.KeyCode )
		{
			case ALLEGRO_KEY_ESCAPE:
				FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::SPIRAL_INWARDS, 9, 9 ) );
				break;
			case ALLEGRO_KEY_UP:
				selectedItem = (selectedItem + 16) % 17;
				scrollPosition = selectedItem * (itemFontHeight * 0.7f);
				break;
			case ALLEGRO_KEY_DOWN:
				selectedItem = (selectedItem + 1) % 17;
				scrollPosition = selectedItem * (itemFontHeight * 0.7f);
				break;
			case ALLEGRO_KEY_ENTER:
			case ALLEGRO_KEY_SPACE:
			case ALLEGRO_KEY_PGDN:
			case ALLEGRO_KEY_END:
				FRAMEWORK->ProgramStages->Push( new GetKeyPress() );
				break;
		}
	}

	if( e->Type == EVENT_USER )
	{
		// User has remapped a key
		switch( selectedItem )
		{
			case 4:
				FRAMEWORK->Settings->SetIntegerValue( "Left.Up", e->Data.Keyboard.KeyCode );
				break;
			case 5:
				FRAMEWORK->Settings->SetIntegerValue( "Left.Down", e->Data.Keyboard.KeyCode );
				break;
			case 6:
				FRAMEWORK->Settings->SetIntegerValue( "Left.Send", e->Data.Keyboard.KeyCode );
				break;
			case 7:
				FRAMEWORK->Settings->SetIntegerValue( "Left.Inv1", e->Data.Keyboard.KeyCode );
				break;
			case 8:
				FRAMEWORK->Settings->SetIntegerValue( "Left.Inv2", e->Data.Keyboard.KeyCode );
				break;
			case 9:
				FRAMEWORK->Settings->SetIntegerValue( "Left.Inv3", e->Data.Keyboard.KeyCode );
				break;
			case 10:
				FRAMEWORK->Settings->SetIntegerValue( "Right.Up", e->Data.Keyboard.KeyCode );
				break;
			case 11:
				FRAMEWORK->Settings->SetIntegerValue( "Right.Down", e->Data.Keyboard.KeyCode );
				break;
			case 12:
				FRAMEWORK->Settings->SetIntegerValue( "Right.Send", e->Data.Keyboard.KeyCode );
				break;
			case 13:
				FRAMEWORK->Settings->SetIntegerValue( "Right.Inv1", e->Data.Keyboard.KeyCode );
				break;
			case 14:
				FRAMEWORK->Settings->SetIntegerValue( "Right.Inv2", e->Data.Keyboard.KeyCode );
				break;
			case 15:
				FRAMEWORK->Settings->SetIntegerValue( "Right.Inv3", e->Data.Keyboard.KeyCode );
				break;
		}
	}

}

void SettingsStage::Update()
{
}

void SettingsStage::Render()
{
	ALLEGRO_COLOR itemColour = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR selectedColour = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR disabledColour = al_map_rgb(96, 96, 96);

	al_clear_to_color( al_map_rgb( 48, 64, 96 ) );

	int yPos = 40 - scrollPosition;
	int curItem = 0;
	al_draw_text( titleFont, al_map_rgb( 255, 192, 96 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Video" );
	yPos += titleFontHeight;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Fullscreen : Yes" );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Shader : Scanlines" );
	yPos += itemFontHeight; curItem++;

	yPos += 20;
	al_draw_text( titleFont, al_map_rgb( 255, 192, 96 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Audio" );
	yPos += titleFontHeight;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Music: On" );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "SoundFX : On" );
	yPos += itemFontHeight; curItem++;

	yPos += 20;
	al_draw_text( titleFont, al_map_rgb( 255, 192, 96 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Left Player Controls" );
	yPos += titleFontHeight;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Up Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Up", ALLEGRO_KEY_UP ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Down Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Down", ALLEGRO_KEY_DOWN ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Send Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Send", ALLEGRO_KEY_RIGHT ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 1 Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Inv1", ALLEGRO_KEY_Q ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 2 Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Inv2", ALLEGRO_KEY_A ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 3 Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Inv3", ALLEGRO_KEY_Z ) ) );
	yPos += itemFontHeight; curItem++;

	yPos += 20;
	al_draw_text( titleFont, al_map_rgb( 255, 192, 96 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Right Player Controls" );
	yPos += titleFontHeight;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Up Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Up", ALLEGRO_KEY_PGUP ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Down Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Down", ALLEGRO_KEY_PGDN ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Send Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Send", ALLEGRO_KEY_HOME ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 1 Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Inv1", ALLEGRO_KEY_O ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 2 Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Inv2", ALLEGRO_KEY_K ) ) );
	yPos += itemFontHeight; curItem++;
	al_draw_textf( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 3 Key : %s", al_keycode_to_name( FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Inv3", ALLEGRO_KEY_M ) ) );
	yPos += itemFontHeight; curItem++;

	yPos += 20;
	al_draw_text( titleFont, al_map_rgb( 255, 255, 255 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Other" );
	yPos += titleFontHeight;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Return" );
	yPos += itemFontHeight; curItem++;

	Shader* s = new ShaderScanlines();
	s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
	delete s;
}

bool SettingsStage::IsTransition()
{
	return false;
}
