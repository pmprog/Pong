
#pragma once

#include "../framework/stage.h"
#include "../framework/includes.h"
#include "../library/spritesheet.h"

class Menu : public Stage
{
	private:
		ALLEGRO_FONT* titleFont;
		ALLEGRO_FONT* itemFont;
		int itemFontHeight;

		static int itemSwayOffsets[16];
		int itemSwayIndex;
		int itemSwayDelay;

		int selectedItem;

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