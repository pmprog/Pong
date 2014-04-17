
#include "battleball.h"
#include "battle.h"

BattleBall::BattleBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
}

void BattleBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattlePlayer*)WithPlayer)->TakeDamage( 2 );
}

