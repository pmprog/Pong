
#include "battle.h"
#include "../../framework/framework.h"
#include "../../shaders/shaders.h"
#include "../../transitions/transitions.h"
#include "battleover.h"

#include "particle.h"
#include "../assetDefines.h"

#define INVENTORY_LEFT_X_POS      12
#define INVENTORY_LEFT_Y_POS      36
#define INVENTORY_LEFT_Y_SPACING   6
#define INVENTORY_RIGHT_X_POS    724
#define INVENTORY_RIGHT_Y_POS     36
#define INVENTORY_RIGHT_Y_SPACING  6
#define INVENTORY_ITEM_SIZE       64

#define HEALTH_LEFT_X_POS    38
#define HEALTH_LEFT_Y_POS   280
#define HEALTH_LEFT_WIDTH    12
#define HEALTH_LEFT_HEIGHT  186
#define HEALTH_LEFT_BORDER    2
#define HEALTH_RIGHT_X_POS  750
#define HEALTH_RIGHT_Y_POS  280
#define HEALTH_RIGHT_WIDTH   12
#define HEALTH_RIGHT_HEIGHT 186
#define HEALTH_RIGHT_BORDER   2

#define LABEL_FONT_SIZE 24

#define MAIN_POS_X   90
#define MAIN_POS_Y   10
#define MAIN_WIDTH  620
#define MAIN_HEIGHT 460
#define MAIN_BORDER   2

#define PLAYER_LEFT_X  110
#define PLAYER_RIGHT_X 690

BattleStage::BattleStage()
{
	labelFont = al_load_font( GAME_FONT, LABEL_FONT_SIZE, 0 );
	backgroundImage = al_load_bitmap( "resources/background.png" );
	inventoryIcons = new SpriteSheet( "resources/inventory.png", INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE );
	GameObjects.push_back( new BattleBall( this, new Vector2( FRAMEWORK->Display_GetWidth() / 2, FRAMEWORK->Display_GetHeight() / 2 ), new Angle( rand() % 360 ), 3.0f ) );
	LeftPlayer = (Player*)(new BattlePlayer( this, new Vector2( PLAYER_LEFT_X, FRAMEWORK->Display_GetHeight() / 2 ), MAIN_POS_Y, MAIN_POS_Y + MAIN_HEIGHT ));
	RightPlayer = (Player*)(new BattlePlayer( this, new Vector2( PLAYER_RIGHT_X, FRAMEWORK->Display_GetHeight() / 2 ), MAIN_POS_Y, MAIN_POS_Y + MAIN_HEIGHT ));

	// Game area = 460
	for( int i = 1; i < 5; i++ )
	{
		GamePickups.push_back( new Pickup( this, FRAMEWORK->Display_GetWidth() / 2, 10 + (92 * i) ) );
	}
}

BattleStage::~BattleStage()
{
	al_destroy_font( labelFont );
	al_destroy_bitmap( backgroundImage );
	delete inventoryIcons;
	delete LeftPlayer;
	delete RightPlayer;

	while( GameObjects.size() > 0 )
	{
		delete GameObjects.front();
		GameObjects.pop_front();
	}

	while( GamePickups.size() > 0 )
	{
		delete GamePickups.front();
		GamePickups.pop_front();
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
			case ALLEGRO_KEY_F2:
				Particle* p = new Particle( al_map_rgb( 255, 220, 128 ), FRAMES_PER_SECOND, this, new Vector2(400, 240), new Angle( rand() % 360 ), 0.4f );
				AddObject( p );
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

	for( std::list<Pickup*>::const_iterator i = GamePickups.begin(); i != GamePickups.end(); i++ )
	{
		Pickup* p = (*i);
		p->Update();
	}
}

void BattleStage::Render()
{
	BattlePlayer* ply;

	al_draw_bitmap( backgroundImage, 0, 0, 0 );


	for( std::list<Pickup*>::const_iterator i = GamePickups.begin(); i != GamePickups.end(); i++ )
	{
		Pickup* p = (*i);
		p->Render();
	}

	for( std::list<Projectile*>::const_reverse_iterator i = GameObjects.rbegin(); i != GameObjects.rend(); i++ )
	{
		Projectile* p = (*i);
		p->Render();
	}
	LeftPlayer->Render();
	RightPlayer->Render();

	// Boundaries of playing area
	al_draw_line( MAIN_POS_X - MAIN_BORDER, MAIN_POS_Y - MAIN_BORDER/ 2.0f,
			MAIN_POS_X + MAIN_WIDTH + MAIN_BORDER, MAIN_POS_Y - MAIN_BORDER/ 2.0f, al_map_rgb( 255, 255, 255 ), MAIN_BORDER );
	al_draw_line( MAIN_POS_X + MAIN_WIDTH + MAIN_BORDER / 2.0f,  MAIN_POS_Y,
			MAIN_POS_X + MAIN_WIDTH + MAIN_BORDER / 2.0f, MAIN_POS_Y + MAIN_HEIGHT, al_map_rgb( 255, 255, 255 ), MAIN_BORDER );
	al_draw_line( MAIN_POS_X - MAIN_BORDER,  MAIN_POS_Y + MAIN_HEIGHT + MAIN_BORDER/ 2.0f,
			MAIN_POS_X + MAIN_WIDTH + MAIN_BORDER, MAIN_POS_Y + MAIN_HEIGHT + MAIN_BORDER/ 2.0f, al_map_rgb( 255, 255, 255 ), MAIN_BORDER );
	al_draw_line( MAIN_POS_X - MAIN_BORDER/ 2.0f, MAIN_POS_Y,
			MAIN_POS_X - MAIN_BORDER/ 2.0f, MAIN_POS_Y + MAIN_HEIGHT, al_map_rgb( 255, 255, 255 ), MAIN_BORDER );

	ply = (BattlePlayer*)LeftPlayer;

	// Left player inventory
	al_draw_text( labelFont, al_map_rgb( 255, 255, 255 ),
			INVENTORY_LEFT_X_POS + INVENTORY_ITEM_SIZE / 2.0f, INVENTORY_LEFT_Y_POS - LABEL_FONT_SIZE * 1.2f,
			ALLEGRO_ALIGN_CENTRE, "items" );
	inventoryIcons->DrawSprite( ply->Inventory[0], INVENTORY_LEFT_X_POS,
			INVENTORY_LEFT_Y_POS,
			1.0f, 1.0f, 0 );
	inventoryIcons->DrawSprite( ply->Inventory[1], INVENTORY_LEFT_X_POS,
			INVENTORY_LEFT_Y_POS + INVENTORY_ITEM_SIZE + INVENTORY_LEFT_Y_SPACING,
			1.0f, 1.0f, 0 );
	inventoryIcons->DrawSprite( ply->Inventory[2], INVENTORY_LEFT_X_POS,
			INVENTORY_LEFT_Y_POS + (INVENTORY_ITEM_SIZE + INVENTORY_LEFT_Y_SPACING) * 2,
			1.0f, 1.0f, 0 );

	// Left player health
	al_draw_text( labelFont, al_map_rgb( 255, 255, 255 ),
			HEALTH_LEFT_X_POS + HEALTH_LEFT_WIDTH / 2.0f, HEALTH_LEFT_Y_POS - HEALTH_LEFT_BORDER - LABEL_FONT_SIZE * 1.2f,
			ALLEGRO_ALIGN_CENTRE, "health" );
	al_draw_filled_rectangle( HEALTH_LEFT_X_POS - HEALTH_LEFT_BORDER,
			HEALTH_LEFT_Y_POS - HEALTH_LEFT_BORDER,
			HEALTH_LEFT_X_POS + HEALTH_LEFT_WIDTH + HEALTH_LEFT_BORDER,
			HEALTH_LEFT_Y_POS + HEALTH_LEFT_HEIGHT + HEALTH_LEFT_BORDER,
			al_map_rgb( 255, 255, 255 ) );
	al_draw_filled_rectangle( HEALTH_LEFT_X_POS,
			HEALTH_LEFT_Y_POS + (1.0f - (ply->Health / (float)ply->MaxHealth)) * HEALTH_LEFT_HEIGHT,
			HEALTH_LEFT_X_POS + HEALTH_LEFT_WIDTH,
			HEALTH_LEFT_Y_POS + HEALTH_LEFT_HEIGHT,
			al_map_rgb( 168, 0, 0 ) );


	ply = (BattlePlayer*)RightPlayer;

	// Right player inventory
	al_draw_text( labelFont, al_map_rgb( 255, 255, 255 ),
			INVENTORY_RIGHT_X_POS + INVENTORY_ITEM_SIZE / 2.0f, INVENTORY_RIGHT_Y_POS - LABEL_FONT_SIZE * 1.2f,
			ALLEGRO_ALIGN_CENTRE, "items" );
	inventoryIcons->DrawSprite( ply->Inventory[0], INVENTORY_RIGHT_X_POS,
			INVENTORY_RIGHT_Y_POS,
			1.0f, 1.0f, 0 );
	inventoryIcons->DrawSprite( ply->Inventory[1], INVENTORY_RIGHT_X_POS,
			INVENTORY_RIGHT_Y_POS + INVENTORY_ITEM_SIZE + INVENTORY_RIGHT_Y_SPACING,
			1.0f, 1.0f, 0 );
	inventoryIcons->DrawSprite( ply->Inventory[2], INVENTORY_RIGHT_X_POS,
			INVENTORY_RIGHT_Y_POS + (INVENTORY_ITEM_SIZE + INVENTORY_RIGHT_Y_SPACING) * 2,
			1.0f, 1.0f, 0 );

	// Right player health
	al_draw_text( labelFont, al_map_rgb( 255, 255, 255 ),
			HEALTH_RIGHT_X_POS + HEALTH_RIGHT_WIDTH / 2.0f, HEALTH_RIGHT_Y_POS - HEALTH_RIGHT_BORDER- LABEL_FONT_SIZE * 1.2f,
			ALLEGRO_ALIGN_CENTRE, "health" );
	al_draw_filled_rectangle( HEALTH_RIGHT_X_POS - HEALTH_RIGHT_BORDER,
			HEALTH_RIGHT_Y_POS - HEALTH_RIGHT_BORDER,
			HEALTH_RIGHT_X_POS + HEALTH_RIGHT_WIDTH + HEALTH_RIGHT_BORDER,
			HEALTH_RIGHT_Y_POS + HEALTH_RIGHT_HEIGHT + HEALTH_RIGHT_BORDER,
			al_map_rgb( 255, 255, 255 ) );
	al_draw_filled_rectangle( HEALTH_RIGHT_X_POS,
			HEALTH_RIGHT_Y_POS + (1.0f - (ply->Health / (float)ply->MaxHealth)) * HEALTH_RIGHT_HEIGHT,
			HEALTH_RIGHT_X_POS + HEALTH_RIGHT_WIDTH,
			HEALTH_RIGHT_Y_POS + HEALTH_RIGHT_HEIGHT,
			al_map_rgb( 168, 0, 0 ) );
}

bool BattleStage::IsTransition()
{
	return false;
}

void BattleStage::ProcessProjectileCollisions( Projectile* Source, Vector2* TargetPosition, bool* Continue )
{
	Vector2* angV = Source->Direction->ToVector();
	bool collisionFound = false;

	if( TargetPosition->X - MAIN_POS_X < Source->Radius )
	{
		TargetPosition->X = Maths::Abs(TargetPosition->X - MAIN_POS_X - Source->Radius) + Source->Radius + MAIN_POS_X;
		angV->X *= -1;
		collisionFound = true;
		Source->OnCollisionPlayersWall( LeftPlayer );
	}
	if( TargetPosition->X > MAIN_POS_X + MAIN_WIDTH - Source->Radius )
	{
		TargetPosition->X = (MAIN_POS_X + MAIN_WIDTH - Source->Radius) - (TargetPosition->X - (MAIN_POS_X + MAIN_WIDTH - Source->Radius));
		angV->X *= -1;
		collisionFound = true;
		Source->OnCollisionPlayersWall( RightPlayer );
	}

	if( TargetPosition->Y - MAIN_POS_Y < Source->Radius )
	{
		TargetPosition->Y = Maths::Abs(TargetPosition->Y - MAIN_POS_Y - Source->Radius) + Source->Radius + MAIN_POS_Y;
		angV->Y *= -1;
		collisionFound = true;
	}
	if( TargetPosition->Y > MAIN_POS_Y + MAIN_HEIGHT - Source->Radius )
	{
		TargetPosition->Y = (MAIN_POS_Y + MAIN_HEIGHT - Source->Radius) - (TargetPosition->Y - (MAIN_POS_Y + MAIN_HEIGHT - Source->Radius));
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

BattleBall* BattleStage::GetBall()
{
	return (BattleBall*)GameObjects.front();
}

SpriteSheet* BattleStage::GetInventoryIcons()
{
	return inventoryIcons;
}
