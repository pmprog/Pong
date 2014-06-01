
#include "sendball.h"
#include "../../framework/framework.h"
#include "battle.h"
//#include "particle.h"

SendBall::SendBall( BattleInventory::Inventory Item, Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed ) : ClassicBall(PlayArena, StartPosition, StartDirection, StartSpeed)
{
	sendingItem = Item;
	sendingRotation = new Angle();
	Radius = 34; // 26;
}

void SendBall::Render()
{
	al_draw_filled_circle( Position->X, Position->Y, Radius + 2, al_map_rgb( 255, 255, 255 ) );
	al_draw_filled_circle( Position->X, Position->Y, Radius, al_map_rgb( 0, 0, 0 ) );
	((BattleStage*)currentArena)->GetInventoryIcons()->DrawSprite( sendingItem - 1, Position->X - 24, Position->Y - 24, 1.0f, 1.0f, sendingRotation );
	sendingRotation->Add( 5 );
}

void SendBall::OnCollision( Player* WithPlayer )
{
	BattlePlayer* ply = (BattlePlayer*)WithPlayer;
	// TODO: Give object to player (auto-activiate?)
	((BattleStage*)currentArena)->RemoveObject( this );
}

void SendBall::OnCollisionPlayersWall( Player* WithPlayer )
{
	((BattleStage*)currentArena)->RemoveObject( this );
}

