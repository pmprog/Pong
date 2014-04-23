
#include "fireball.h"
#include "../../framework/framework.h"
#include "battle.h"

FireBall::FireBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : BattleBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
}


void FireBall::Update()
{
	BattleBall::Update();
}

void FireBall::Render()
{
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgb( 255, 220, 128 ) );
}

void FireBall::OnCollision( Player* WithPlayer )
{
	((BattlePlayer*)WithPlayer)->TakeDamage( 1 );
	((BattleStage*)currentArena)->RemoveObject( this );
}

void FireBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattleStage*)currentArena)->RemoveObject( this );
}

