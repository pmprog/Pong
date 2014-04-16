
#pragma once

#include "../../framework/stage.h"
#include "../../framework/includes.h"
#include "../../library/box.h"
#include "classicball.h"
#include "../core/player.h"


class ClassicStage : public Stage, Arena
{
	private:
		ALLEGRO_BITMAP* backgroundImage;
		ClassicBall* Ball;
		ALLEGRO_FONT* scoreFont;

  public:
		int LeftScore;
		int RightScore;

		ClassicStage();
		~ClassicStage();

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