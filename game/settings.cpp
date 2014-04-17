
#include "settings.h"
#include "../framework/framework.h"
#include "../shaders/shaders.h"
#include "../transitions/transitions.h"

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
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Fullscreen : Yes" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Shader : Scanlines" );
	yPos += itemFontHeight; curItem++;

	yPos += 20;
	al_draw_text( titleFont, al_map_rgb( 255, 192, 96 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Audio" );
	yPos += titleFontHeight;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Music: On" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "SoundFX : On" );
	yPos += itemFontHeight; curItem++;

	yPos += 20;
	al_draw_text( titleFont, al_map_rgb( 255, 192, 96 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Left Player Controls" );
	yPos += titleFontHeight;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Up Key : {Up}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Down Key : {Down}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Send Key : {Right}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 1 Key : {Q}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 2 Key : {A}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 3 Key : {Z}" );
	yPos += itemFontHeight; curItem++;

	yPos += 20;
	al_draw_text( titleFont, al_map_rgb( 255, 192, 96 ), FRAMEWORK->Display_GetWidth() / 2, yPos, ALLEGRO_ALIGN_CENTRE, "Right Player Controls" );
	yPos += titleFontHeight;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Up Key : {Page Up}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Down Key : {Page Down}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Send Key : {Home}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 1 Key : {O}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 2 Key : {K}" );
	yPos += itemFontHeight; curItem++;
	al_draw_text( itemFont, (selectedItem == curItem ? selectedColour : itemColour), 40, yPos, ALLEGRO_ALIGN_LEFT, "Inventory 3 Key : {M}" );
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
