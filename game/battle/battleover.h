
#pragma once

#include "../../framework/stage.h"
#include "../../framework/includes.h"

#ifndef BattleStage
class BattleStage;
#endif

class BattleOver : public Stage
{
	private:
		ALLEGRO_FONT* itemFont;
		int itemFontHeight;
		int FadeIn;
		BattleStage* battleStage;

  public:
		BattleOver();
		~BattleOver();

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