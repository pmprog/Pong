
#include "battle.h"
#include "../../framework/framework.h"
#include "../../shaders/shaders.h"
#include "../../transitions/transitions.h"
#include "battleover.h"

BattleStage::BattleStage()
{
	backgroundImage = al_load_bitmap( "resources/background.png" );
	inventoryIcons = new SpriteSheet( "resources/inventory.png", 48, 48 );
	GameObjects.push_back( new BattleBall( this, new Vector2( FRAMEWORK->Display_GetWidth() / 2, FRAMEWORK->Display_GetHeight() / 2 ), new Angle( rand() % 360 ), 3.0f ) );
	LeftPlayer = (Player*)(new BattlePlayer( this, new Vector2( 130, FRAMEWORK->Display_GetHeight() / 2 ), 10, 470 ));
	RightPlayer = (Player*)(new BattlePlayer( this, new Vector2( 670, FRAMEWORK->Display_GetHeight() / 2 ), 10, 470 ));
}

BattleStage::~BattleStage()
{
	al_destroy_bitmap( backgroundImage );
	delete inventoryIcons;
	delete LeftPlayer;
	delete RightPlayer;

	while( GameObjects.size() > 0 )
	{
		delete GameObjects.front();
		GameObjects.pop_front();
	}
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
	bool pressDown;
	if( e->Type == EVENT_KEY_DOWN || e->Type == EVENT_KEY_UP )
	{
		pressDown = (e->Type == EVENT_KEY_DOWN);
		switch( e->Data.Keyboard.KeyCode )
		{
			case ALLEGRO_KEY_ESCAPE:
				FRAMEWORK->ProgramStages->Push( new TransitionTiled( TiledTransitions::NORTHWEST_TO_SOUTHEAST, 20, 20 ) );
				break;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Up", ALLEGRO_KEY_UP ) )
		{
			LeftPlayer->UpPressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Down", ALLEGRO_KEY_DOWN ) )
		{
			LeftPlayer->DownPressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Send", ALLEGRO_KEY_RIGHT ) )
		{
			((BattlePlayer*)LeftPlayer)->SendPressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Inv1", ALLEGRO_KEY_Q ) )
		{
			((BattlePlayer*)LeftPlayer)->Inv1Pressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Inv2", ALLEGRO_KEY_A ) )
		{
			((BattlePlayer*)LeftPlayer)->Inv2Pressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Left.Inv3", ALLEGRO_KEY_Z ) )
		{
			((BattlePlayer*)LeftPlayer)->Inv3Pressed = pressDown;
		}

		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Up", ALLEGRO_KEY_PGUP ) )
		{
			RightPlayer->UpPressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Down", ALLEGRO_KEY_PGDN ) )
		{
			RightPlayer->DownPressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Send", ALLEGRO_KEY_HOME ) )
		{
			((BattlePlayer*)RightPlayer)->SendPressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Inv1", ALLEGRO_KEY_O ) )
		{
			((BattlePlayer*)RightPlayer)->Inv1Pressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Inv2", ALLEGRO_KEY_K ) )
		{
			((BattlePlayer*)RightPlayer)->Inv2Pressed = pressDown;
		}
		if( e->Data.Keyboard.KeyCode == FRAMEWORK->Settings->GetQuickIntegerValue( "Right.Inv3", ALLEGRO_KEY_M ) )
		{
			((BattlePlayer*)RightPlayer)->Inv3Pressed = pressDown;
		}
	}
}

void BattleStage::Update()
{

	while( GameObjectsToAdd.size() > 0 )
	{
		Projectile* p = GameObjectsToAdd.front();
		GameObjectsToAdd.pop_front();
		GameObjects.push_back( p );
	}

	while( GameObjectsToRemove.size() > 0 )
	{
		Projectile* p = GameObjectsToRemove.front();
		GameObjectsToRemove.pop_front();
		GameObjects.remove( p );
		delete p;
	}

	for( std::list<Projectile*>::const_iterator i = GameObjects.begin(); i != GameObjects.end(); i++ )
	{
		Projectile* p = (*i);
		p->Update();
	}

	LeftPlayer->Update();
	RightPlayer->Update();

	if( ((BattlePlayer*)LeftPlayer)->TargetHealth == 0 || ((BattlePlayer*)RightPlayer)->TargetHealth == 0 )
	{
		FRAMEWORK->ProgramStages->Push( new TransitionStrips( new BattleOver( this ), FRAMES_PER_SECOND, 80 ) );
	}
}

void BattleStage::Render()
{
	BattlePlayer* ply;

	al_draw_bitmap( backgroundImage, 0, 0, 0 );

	for( std::list<Projectile*>::const_iterator i = GameObjects.begin(); i != GameObjects.end(); i++ )
	{
		Projectile* p = (*i);
		p->Render();
	}
	LeftPlayer->Render();
	RightPlayer->Render();

	al_draw_line(  90,  10, 710,  10, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line(  90, 470, 710, 470, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line(  90,  10,  90, 470, al_map_rgb( 255, 255, 255 ), 3 );
	al_draw_line( 710,  10, 710, 470, al_map_rgb( 255, 255, 255 ), 3 );

	ply = (BattlePlayer*)LeftPlayer;

	// Left player inventory
	if( ply->Inventory[0] != 0 )
	{
		inventoryIcons->DrawSprite( ply->Inventory[0] - 1, 21, 10, 1.0f, 1.0f, 0 );
	}
	al_draw_rectangle( 21,  10, 69,  58, al_map_rgb( 255, 255, 255 ), 3 );
	if( ply->Inventory[1] != 0 )
	{
		inventoryIcons->DrawSprite( ply->Inventory[1] - 1, 21, 69, 1.0f, 1.0f, 0 );
	}
	al_draw_rectangle( 21,  64, 69, 112, al_map_rgb( 255, 255, 255 ), 3 );
	if( ply->Inventory[2] != 0 )
	{
		inventoryIcons->DrawSprite( ply->Inventory[2] - 1, 21, 118, 1.0f, 1.0f, 0 );
	}
	al_draw_rectangle( 21, 118, 69, 166, al_map_rgb( 255, 255, 255 ), 3 );

	// Left player health
	al_draw_filled_rectangle( 21, 198, 69, 462, al_map_rgb( 255, 255, 255 ) );
	al_draw_filled_rectangle( 23, 460 - ((ply->Health / (float)ply->MaxHealth) * 260.0f), 67, 460, al_map_rgb( 0, 255, 0 ) );


	ply = (BattlePlayer*)RightPlayer;

	// Right player inventory
	if( ply->Inventory[0] != 0 )
	{
		inventoryIcons->DrawSprite( ply->Inventory[0] - 1, 731, 10, 1.0f, 1.0f, 0 );
	}
	al_draw_rectangle( 731,  10, 779,  58, al_map_rgb( 255, 255, 255 ), 3 );
	if( ply->Inventory[1] != 0 )
	{
		inventoryIcons->DrawSprite( ply->Inventory[1] - 1, 731, 64, 1.0f, 1.0f, 0 );
	}
	al_draw_rectangle( 731,  64, 779, 112, al_map_rgb( 255, 255, 255 ), 3 );
	if( ply->Inventory[2] != 0 )
	{
		inventoryIcons->DrawSprite( ply->Inventory[2] - 1, 731, 118, 1.0f, 1.0f, 0 );
	}
	al_draw_rectangle( 731, 118, 779, 166, al_map_rgb( 255, 255, 255 ), 3 );

	// Right player health
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
		Source->OnCollisionPlayersWall( LeftPlayer );
	}
	if( TargetPosition->X > 710 - Source->Radius )
	{
		TargetPosition->X = (710 - Source->Radius) - (TargetPosition->X - (710 - Source->Radius));
		angV->X *= -1;
		collisionFound = true;
		Source->OnCollisionPlayersWall( RightPlayer );
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
			Source->OnCollision( LeftPlayer );
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
			Source->OnCollision( RightPlayer );
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

void BattleStage::AddObject( Projectile* Object )
{
	GameObjectsToAdd.push_back( Object );
}

void BattleStage::RemoveObject( Projectile* Object )
{
	GameObjectsToRemove.push_back( Object );
}

Angle* BattleStage::GetAttackAngle( Player* Controller )
{
	return new Angle( (Controller == LeftPlayer ? 90.0f : 270.0f) );
}

Player* BattleStage::GetOpponent( Player* Controller )
{
	return (Controller == LeftPlayer ? RightPlayer : LeftPlayer);
}
