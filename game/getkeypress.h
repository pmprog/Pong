
#pragma once

#include "../framework/stage.h"
#include "../framework/includes.h"

class GetKeyPress : public Stage
{
	private:
		ALLEGRO_FONT* itemFont;
		int itemFontHeight;
		int FadeIn;

  public:
		GetKeyPress();
		~GetKeyPress();

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