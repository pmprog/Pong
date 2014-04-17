
#pragma once

#include "../framework/stage.h"
#include "../framework/includes.h"

class GetKeyPress : public Stage
{
	private:
		int FadeIn;

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