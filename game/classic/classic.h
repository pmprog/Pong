
#pragma once

#include "../../framework/stage.h"
#include "../../framework/includes.h"
#include "../../library/vector2.h"

class ClassicStage : public Stage
{
	private:
		ALLEGRO_BITMAP* backgroundImage;
		Vector2* ballPos;
		Vector2* ballVel;

  public:
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
};