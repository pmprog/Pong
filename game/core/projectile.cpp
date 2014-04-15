
#include "projectile.h"

Projectile::Projectile(Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed)
{
	currentArena = PlayArena;
	Position = new Vector2( StartPosition );
	Direction = StartDirection;
	Speed = StartSpeed;
}

Projectile::~Projectile()
{
	delete Position;
	delete Direction;
}

void Projectile::Update()
{
	Vector2* velocity = Direction->ToVector();
	velocity->Multiply( Speed );

}

void Projectile::Render()
{
}
