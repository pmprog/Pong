
#pragma once

#include "../../framework/includes.h"
#include "../../library/vector2.h"
#include "../../library/angle.h"
#include "arena.h"

class Player
{

	protected:
		Arena* currentArena;
		int roofY;
		int floorY;

		bool up;
		bool down;

	public:
		Vector2* Position;
		float UpVelocity;
		int Size;
		int Width;
		float Speed;

		Player( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY );
		~Player();

		virtual void UpPushed();
		virtual void UpReleased();
		virtual void DownPushed();
		virtual void DownReleased();

		virtual void Update();
		virtual void Render();
};