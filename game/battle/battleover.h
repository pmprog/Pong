
#pragma once

#include "../../framework/stage.h"
#include "../../framework/includes.h"
#include "../../library/angle.h"

#ifndef BattleStage
class BattleStage;
#endif

// *******************
// Game over screen for battle mode (showing player scores and whatnot)
// *******************

class BattleOver : public Stage
{
	private:
		ALLEGRO_FONT* itemFont;
		int itemFontHeight;
		BattleStage* battleStage;
		Angle* slideAngleX;
		Angle* slideAngleY;

  public:
		BattleOver(BattleStage* Battle);
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
