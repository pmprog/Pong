
#pragma once

#include "../../framework/stage.h"
#include "../../framework/includes.h"
#include "../../library/box.h"
#include "../classic/classicball.h"
#include "battleplayer.h"

class BattleStage : public Stage, Arena
{
	private:
		ALLEGRO_BITMAP* backgroundImage;
		ClassicBall* Ball;

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
};