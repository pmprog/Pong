
#include "classic.h"
#include "../../framework/framework.h"
#include "../../shaders/shaders.h"
#include "../../transitions/transitions.h"

#define BALL_RADIUS 6

ClassicStage::ClassicStage()
{
	backgroundImage = al_load_bitmap( "resources/background.png" );
	Ball = new ClassicBall( this, new Vector2( FRAMEWORK->Display_GetWidth() / 2, FRAMEWORK->Display_GetHeight() / 2 ), new Angle( rand() % 360 ), 6.0f );
}

ClassicStage::~ClassicStage()
{
	al_destroy_bitmap( backgroundImage );
}

void ClassicStage::Begin()
{
}

void ClassicStage::Pause()
{
}

void ClassicStage::Resume()
{
}

void ClassicStage::Finish()
{
}

void ClassicStage::EventOccurred(Event *e)
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

void ClassicStage::Update()
{
	Ball->Update();
}

void ClassicStage::Render()
{
	//al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
	al_draw_bitmap( backgroundImage, 0, 0, 0 );

	// al_draw_filled_rectangle( ballPos->X - BALL_RADIUS, ballPos->Y - BALL_RADIUS, ballPos->X + BALL_RADIUS, ballPos->Y + BALL_RADIUS, al_map_rgb( 255, 255, 255 ) );
	Ball->Render();

	Shader* s = new ShaderScanlines();
	s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
	delete s;
}

bool ClassicStage::IsTransition()
{
	return false;
}

void ClassicStage::ProcessProjectileCollisions( Projectile* Source, Vector2* TargetPosition, bool* Continue )
{
	Vector2* angV = Source->Direction->ToVector();
	bool collisionFound = false;

	if( TargetPosition->X < Source->Radius )
	{
		TargetPosition->X = Maths::Abs(TargetPosition->X - Source->Radius) + Source->Radius;
		angV->X *= -1;
		collisionFound = true;
	}
	if( TargetPosition->X > FRAMEWORK->Display_GetWidth() - Source->Radius )
	{
		TargetPosition->X = (FRAMEWORK->Display_GetWidth() - Source->Radius) - (TargetPosition->X - (FRAMEWORK->Display_GetWidth() - Source->Radius));
		angV->X *= -1;
		collisionFound = true;
	}

	if( TargetPosition->Y < Source->Radius )
	{
		TargetPosition->Y = Maths::Abs(TargetPosition->Y - Source->Radius) + Source->Radius;
		angV->Y *= -1;
		collisionFound = true;
	}
	if( TargetPosition->Y > FRAMEWORK->Display_GetHeight() - Source->Radius )
	{
		TargetPosition->Y = (FRAMEWORK->Display_GetHeight() - Source->Radius) - (TargetPosition->Y - (FRAMEWORK->Display_GetHeight() - Source->Radius));
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
