
#pragma once

#include "../../framework/stage.h"
#include "../../framework/includes.h"
#include "../../library/box.h"
#include "../../library/spritesheet.h"
#include "battleball.h"
#include "battleplayer.h"
#include "pickup.h"

class BattleStage : public Stage, Arena
{
	private:
		ALLEGRO_BITMAP* backgroundImage;
		SpriteSheet* inventoryIcons;
		std::list<Projectile*> GameObjects;
		std::list<Projectile*> GameObjectsToAdd;
		std::list<Projectile*> GameObjectsToRemove;
		std::list<Pickup*> GamePickups;

  public:
		BattleStage();
		~BattleStage();

    // Stage control
    virtual void Begin();
    virtual void Pause();
    virtual void Resume();
    virtual void Finish();
    virtual void EventOccurred(Event *e);
    virtual void Update();
    virtual void Render();
		virtual bool IsTransition();

		// Arena
		virtual void ProcessProjectileCollisions( Projectile* Source, Vector2* TargetPosition, bool* Continue );

		void AddObject( Projectile* Object );
		void RemoveObject( Projectile* Object );

		Angle* GetAttackAngle( Player* Controller );
		Player* GetOpponent( Player* Controller );
		BattleBall* GetBall();
		SpriteSheet* GetInventoryIcons();
};