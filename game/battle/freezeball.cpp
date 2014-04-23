
#include "freezeball.h"
#include "../../framework/framework.h"
#include "battle.h"

FreezeBall::FreezeBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
}


void FreezeBall::Update()
{
	BattleBall::Update();
}

void FreezeBall::Render()
{
	al_draw_filled_rectangle( Position->X - Radius, Position->Y - Radius, Position->X + Radius, Position->Y + Radius, al_map_rgb( 128, 192, 255 ) );
}

void FreezeBall::OnCollision( Player* WithPlayer )
{
	BattlePlayer* ply = (BattlePlayer*)WithPlayer;
	if( ply->FreezeLevel < 2 )
	{
		ply->FreezeLevel++;
		ply->FreezeTime = 0;
	}
	((BattleStage*)currentArena)->RemoveObject( this );
}

void FreezeBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattleStage*)currentArena)->RemoveObject( this );
}

