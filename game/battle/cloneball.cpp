
#include "cloneball.h"
#include "../../framework/framework.h"
#include "battle.h"

CloneBall::CloneBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : BattleBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	LifeSpan = FRAMES_PER_SECOND * 4;
}


void CloneBall::Update()
{
	BattleBall::Update();
	LifeSpan--;
	if( LifeSpan <= 0 )
	{
		((BattleStage*)currentArena)->RemoveObject( this );
	}
}

void CloneBall::Render()
{
	if( LifeSpan > (FRAMES_PER_SECOND / 2) || (LifeSpan % 10) > 5 )
	{
		BattleBall::Render();
	}
}

void CloneBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	BattleBall::OnCollisionPlayersWall( WithPlayer );
	LifeSpan = 0;
}

