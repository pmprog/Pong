
#include "battleball.h"
#include "battle.h"

BattleBall::BattleBall( Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	LastHitBy = 0;
}

void BattleBall::OnCollision( Player* WithPlayer )
{
	LastHitBy = WithPlayer;
	ClassicBall::OnCollision( WithPlayer );
}

void BattleBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattlePlayer*)WithPlayer)->TakeDamage( 2 );
}

