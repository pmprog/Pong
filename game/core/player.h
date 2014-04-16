
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

	public:
		Vector2* Position;
		float UpVelocity;
		int Size;
		int Width;
		float Speed;

		bool UpPressed;
		bool DownPressed;

		Player( Arena* PlayArena, Vector2* StartPosition, int MinimumY, int MaximumY );
		~Player();

		virtual void Update();
		virtual void Render();
};