
#pragma once

#include "../framework/stage.h"
#include "../framework/includes.h"
#include "../library/spritesheet.h"
#include "../library/vector2.h"

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

		Vector2* ballPos;
		Vector2* ballVel;
		Vector2* ballHistory[10];

  public:
		Menu();

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