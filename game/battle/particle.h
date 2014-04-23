
#pragma once

#include "battleball.h"

class Particle : public ClassicBall
{
	private:
		int LifeSpan;
		ALLEGRO_COLOR particleColour;
		// Vector2* positionHistory[10];

	public:
		Particle( ALLEGRO_COLOR Colour, Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed );

		virtual void Update();
		virtual void Render();
		//virtual void OnCollision( Player* WithPlayer );	// Not needed
		//virtual void OnCollisionPlayersWall( Player* WithPlayer ); // Not needed

};