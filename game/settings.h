
#pragma once

#include "../framework/stage.h"
#include "../framework/includes.h"
#include "../library/spritesheet.h"
#include "../library/vector2.h"

class SettingsStage : public Stage
{
	private:
		ALLEGRO_FONT* titleFont;
		ALLEGRO_FONT* itemFont;
		int titleFontHeight;
		int itemFontHeight;

		int selectedItem;
		int scrollPosition;

  public:
		SettingsStage();
		~SettingsStage();

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