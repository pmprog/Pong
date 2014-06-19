
#pragma once

#include "../framework/stage.h"

class MenuNetwork : public Stage
{
	private:
		ALLEGRO_FONT* titleFont;
		ALLEGRO_FONT* itemFont;
		int itemFontHeight;
		int selectedItem;
		int fadeDown;
		int slideIn;

  public:
		MenuNetwork();
		~MenuNetwork();

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