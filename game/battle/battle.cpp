
#include "battle.h"
#include "../../framework/framework.h"
#include "../../shaders/shaders.h"
#include "../../transitions/transitions.h"

BattleStage::BattleStage()
{
	backgroundImage = al_load_bitmap( "resources/background.png" );
	Ball = new ClassicBall( this, new Vector2( FRAMEWORK->Display_GetWidth() / 2, FRAMEWORK->Display_GetHeight() / 2 ), new Angle( rand() % 360 ), 6.0f );
	LeftPlayer = new Player( this, new Vector2( FRAMEWORK->Display_GetWidth() / 4, FRAMEWORK->Display_GetHeight() / 2 ), 0, FRAMEWORK->Display_GetHeight() );
	RightPlayer = new Player( this, new Vector2( FRAMEWORK->Display_GetWidth() / 4.0f * 3.0f, FRAMEWORK->Display_GetHeight() / 2 ), 0, FRAMEWORK->Display_GetHeight() );
}

BattleStage::~BattleStage()
{
	al_destroy_bitmap( backgroundImage );
}

void BattleStage::Begin()
{
}

void BattleStage::Pause()
{
}

void BattleStage::Resume()
{
}

void BattleStage::Finish()
{
}

void BattleStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{

		switch( e->Data.Keyboard.KeyCode )
		{
			case ALLEGRO_KEY_ESCAPE:
				FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::NORTHWEST_TO_SOUTHEAST, 20, 20 ) );
				break;
		}
	}
}

void BattleStage::Update()
{
	Ball->Update();
	LeftPlayer->Update();
	RightPlayer->Update();
}

void BattleStage::Render()
{
	al_draw_bitmap( backgroundImage, 0, 0, 0 );

	Ball->Render();
	LeftPlayer->Render();
	RightPlayer->Render();

	al_draw_line(  90,  10, 710,  10, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line(  90, 470, 710, 470, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line(  90,  10,  90, 470, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line( 710,  10, 710, 470, al_map_rgb( 255, 255, 255 ), 3 );

	Shader* s = new ShaderScanlines();
	s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
	delete s;
}

bool BattleStage::IsTransition()
{
	return false;
}

void BattleStage::ProcessProjectileCollisions( Projectile* Source, Vector2* TargetPosition, bool* Continue )
{
	Vector2* angV = Source->Direction->ToVector();
	bool collisionFound = false;

	if( TargetPosition->X - 90 < Source->Radius )
	{
		TargetPosition->X = Maths::Abs(TargetPosition->X - 90 - Source->Radius) + Source->Radius + 90;
		angV->X *= -1;
		collisionFound = true;
	}
	if( TargetPosition->X > 710 - Source->Radius )
	{
		TargetPosition->X = (710 - Source->Radius) - (TargetPosition->X - (710 - Source->Radius));
		angV->X *= -1;
		collisionFound = true;
	}

	if( TargetPosition->Y - 10 < Source->Radius )
	{
		TargetPosition->Y = Maths::Abs(TargetPosition->Y - 10 - Source->Radius) + Source->Radius + 10;
		angV->Y *= -1;
		collisionFound = true;
	}
	if( TargetPosition->Y > 470 - Source->Radius )
	{
		TargetPosition->Y = (470 - Source->Radius) - (TargetPosition->Y - (470 - Source->Radius));
		angV->Y *= -1;
		collisionFound = true;
	}

	if( collisionFound )
	{
		delete Source->Direction;
		Source->Direction = angV->ToAngle();
	}
	delete angV;
}
