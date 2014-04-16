
#include "classic.h"
#include "../../framework/framework.h"
#include "../../shaders/shaders.h"
#include "../../transitions/transitions.h"

ClassicStage::ClassicStage()
{
	backgroundImage = al_load_bitmap( "resources/background.png" );
	Ball = new ClassicBall( this, new Vector2( FRAMEWORK->Display_GetWidth() / 2, FRAMEWORK->Display_GetHeight() / 2 ), new Angle( rand() % 360 ), 5.0f );
	LeftPlayer = new Player( this, new Vector2( 40, FRAMEWORK->Display_GetHeight() / 2 ), 0, FRAMEWORK->Display_GetHeight() );
	RightPlayer = new Player( this, new Vector2( FRAMEWORK->Display_GetWidth() - 40, FRAMEWORK->Display_GetHeight() / 2 ), 0, FRAMEWORK->Display_GetHeight() );
	LeftScore = 0;
	RightScore = 0;
	scoreFont = al_load_font( "resources/title.ttf", 64, 0 );
}

ClassicStage::~ClassicStage()
{
	al_destroy_bitmap( backgroundImage );
	al_destroy_font( scoreFont );
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
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Up", ALLEGRO_KEY_UP ) )
		{
			LeftPlayer->UpPushed();
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Down", ALLEGRO_KEY_DOWN ) )
		{
			LeftPlayer->DownPushed();
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Up", ALLEGRO_KEY_PGUP ) )
		{
			RightPlayer->UpPushed();
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Down", ALLEGRO_KEY_PGDN ) )
		{
			RightPlayer->DownPushed();
		}
	}
	if( e->Type == EVENT_KEY_UP )
	{
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Up", ALLEGRO_KEY_UP ) )
		{
			LeftPlayer->UpReleased();
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Down", ALLEGRO_KEY_DOWN ) )
		{
			LeftPlayer->DownReleased();
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Up", ALLEGRO_KEY_PGUP ) )
		{
			RightPlayer->UpReleased();
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Down", ALLEGRO_KEY_PGDN ) )
		{
			RightPlayer->DownReleased();
		}
	}
}

void ClassicStage::Update()
{
	Ball->Update();
	LeftPlayer->Update();
	RightPlayer->Update();
}

void ClassicStage::Render()
{
	al_draw_bitmap( backgroundImage, 0, 0, 0 );

	Ball->Render();
	LeftPlayer->Render();
	RightPlayer->Render();

	al_draw_line(   0,  10, 800,  10, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line(   0, 470, 800, 470, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line( 400,  10, 400, 470, al_map_rgba( 255, 255, 255, 128 ), 3 );

	al_draw_textf( scoreFont, al_map_rgba( 255, 255, 255, 192 ), (FRAMEWORK->Display_GetWidth() / 2) - 20, 40, ALLEGRO_ALIGN_RIGHT, "%d", LeftScore );
	al_draw_textf( scoreFont, al_map_rgba( 255, 255, 255, 192 ), (FRAMEWORK->Display_GetWidth() / 2) + 20, 40, ALLEGRO_ALIGN_LEFT, "%d", RightScore );

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

	if( TargetPosition->X < 0 )
	{
		TargetPosition->X = FRAMEWORK->Display_GetWidth() / 6;
		TargetPosition->Y = FRAMEWORK->Display_GetHeight() / 2;
		Source->Direction->Set( (rand() % 160) + 10 );
		RightScore++;
	}
	if( TargetPosition->X > FRAMEWORK->Display_GetWidth() )
	{
		TargetPosition->X = FRAMEWORK->Display_GetWidth() / 6.0f * 5.0f;
		TargetPosition->Y = FRAMEWORK->Display_GetHeight() / 2;
		Source->Direction->Set( (rand() % 160) + 190 );
		LeftScore++;
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

	Box* ballBounds = new Box( TargetPosition->X - Source->Radius, TargetPosition->Y - Source->Radius, Source->Radius * 2, Source->Radius * 2 );
	if( angV->X < 0 )
	{
		Box* leftPlyBounds = new Box( LeftPlayer->Position->X - (LeftPlayer->Width / 2), LeftPlayer->Position->Y - (LeftPlayer->Size / 2), LeftPlayer->Width, LeftPlayer->Size );
		if( leftPlyBounds->Collides( ballBounds ) )
		{
			angV->X *= -1;
			collisionFound = true;
		}
		delete leftPlyBounds;
	}
	if( angV->X > 0 )
	{
		Box* rightPlyBounds = new Box( RightPlayer->Position->X - (RightPlayer->Width / 2), RightPlayer->Position->Y - (RightPlayer->Size / 2), RightPlayer->Width, RightPlayer->Size );
		if( rightPlyBounds->Collides( ballBounds ) )
		{
			angV->X *= -1;
			collisionFound = true;
		}
		delete rightPlyBounds;
	}
	delete ballBounds;

	if( collisionFound )
	{
		delete Source->Direction;
		Source->Direction = angV->ToAngle();
	}
	delete angV;
}
