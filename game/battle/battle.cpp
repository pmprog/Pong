
#include "battle.h"
#include "../../framework/framework.h"
#include "../../shaders/shaders.h"
#include "../../transitions/transitions.h"

BattleStage::BattleStage()
{
	backgroundImage = al_load_bitmap( "resources/background.png" );
	Ball = new ClassicBall( this, new Vector2( FRAMEWORK->Display_GetWidth() / 2, FRAMEWORK->Display_GetHeight() / 2 ), new Angle( rand() % 360 ), 6.0f );
	LeftPlayer = (Player*)(new BattlePlayer( this, new Vector2( 130, FRAMEWORK->Display_GetHeight() / 2 ), 10, 470 ));
	RightPlayer = (Player*)(new BattlePlayer( this, new Vector2( 670, FRAMEWORK->Display_GetHeight() / 2 ), 10, 470 ));
}

BattleStage::~BattleStage()
{
	al_destroy_bitmap( backgroundImage );
	delete Ball;
	delete LeftPlayer;
	delete RightPlayer;
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
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Up", ALLEGRO_KEY_UP ) )
		{
			LeftPlayer->UpPressed = true;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Down", ALLEGRO_KEY_DOWN ) )
		{
			LeftPlayer->DownPressed = true;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Up", ALLEGRO_KEY_PGUP ) )
		{
			RightPlayer->UpPressed = true;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Down", ALLEGRO_KEY_PGDN ) )
		{
			RightPlayer->DownPressed = true;
		}
	}
	if( e->Type == EVENT_KEY_UP )
	{
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Up", ALLEGRO_KEY_UP ) )
		{
			LeftPlayer->UpPressed = false;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Down", ALLEGRO_KEY_DOWN ) )
		{
			LeftPlayer->DownPressed = false;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Up", ALLEGRO_KEY_PGUP ) )
		{
			RightPlayer->UpPressed = false;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Down", ALLEGRO_KEY_PGDN ) )
		{
			RightPlayer->DownPressed = false;
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
	BattlePlayer* ply;

	al_draw_bitmap( backgroundImage, 0, 0, 0 );

	Ball->Render();
	LeftPlayer->Render();
	RightPlayer->Render();

	al_draw_line(  90,  10, 710,  10, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line(  90, 470, 710, 470, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line(  90,  10,  90, 470, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line( 710,  10, 710, 470, al_map_rgb( 255, 255, 255 ), 3 );

	// Left player inventory
	al_draw_rectangle( 21,  10, 69,  58, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_rectangle( 21,  64, 69, 112, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_rectangle( 21, 118, 69, 166, al_map_rgb( 255, 255, 255 ), 3 );

	// Left player health
	ply = (BattlePlayer*)LeftPlayer;
	al_draw_filled_rectangle( 21, 198, 69, 462, al_map_rgb( 255, 255, 255 ) );
	al_draw_filled_rectangle( 23, 460 - ((ply->Health / (float)ply->MaxHealth) * 260.0f), 67, 460, al_map_rgb( 0, 255, 0 ) );

	// Right player inventory
	al_draw_rectangle( 731,  10, 779,  58, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_rectangle( 731,  64, 779, 112, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_rectangle( 731, 118, 779, 166, al_map_rgb( 255, 255, 255 ), 3 );

	// Right player health
	ply = (BattlePlayer*)RightPlayer;
	al_draw_filled_rectangle( 731, 198, 779, 462, al_map_rgb( 255, 255, 255 ) );
	al_draw_filled_rectangle( 733, 460 - ((ply->Health / (float)ply->MaxHealth) * 260.0f), 777, 460, al_map_rgb( 0, 255, 0 ) );


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
		((BattlePlayer*)LeftPlayer)->TakeDamage( 2 );
	}
	if( TargetPosition->X > 710 - Source->Radius )
	{
		TargetPosition->X = (710 - Source->Radius) - (TargetPosition->X - (710 - Source->Radius));
		angV->X *= -1;
		collisionFound = true;
		((BattlePlayer*)RightPlayer)->TakeDamage( 2 );
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

	// TODO: Fix to check when projectiles aren't balls!
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
