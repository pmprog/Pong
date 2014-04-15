
#include "classic.h"
#include "../framework/framework.h"
#include "../shaders/shaders.h"
#include "../transitions/transitions.h"

#define BALL_RADIUS 6

ClassicStage::ClassicStage()
{
	ballPos = new Vector2( (rand() % (FRAMEWORK->Display_GetWidth() - 24)) + (BALL_RADIUS * 2),	(rand() % (FRAMEWORK->Display_GetHeight() - 24)) + (BALL_RADIUS * 2) );
	ballVel = new Vector2( ((rand() % 2) + 1) * (rand() % 2 == 0 ? 1 : -1) , ((rand() % 2) + 1) * (rand() % 2 == 0 ? 1 : -1) );
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
}

void ClassicStage::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	al_draw_filled_rectangle( ballPos->X - BALL_RADIUS, ballPos->Y - BALL_RADIUS, ballPos->X + BALL_RADIUS, ballPos->Y + BALL_RADIUS, al_map_rgb( 255, 255, 255 ) );

	Shader* s = new ShaderScanlines();
	s->Apply( FRAMEWORK->Display_GetCurrentTarget() );
	delete s;
}

bool ClassicStage::IsTransition()
{
	return false;
}
