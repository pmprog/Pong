
#pragma once

#include "../framework/stage.h"

class MenuNetwork : public Stage
{
	private:
		int selectedItem;

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