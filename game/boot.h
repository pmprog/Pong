
#pragma once

#include "../framework/stage.h"
#include "../framework/includes.h"
#include "../library/spritesheet.h"

class BootUp : public Stage
{
	private:
		int bootBarAdjust;
		int bootBarSize;
		SpriteSheet* logoSpriteP;
		SpriteSheet* logoSpriteF;
		int logoFadeIn;

		void StartGame();

  public:
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