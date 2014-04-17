
#include "projectile.h"

Projectile::Projectile(Arena* PlayArena, Vector2* StartPosition, Angle* StartDirection, float StartSpeed)
{
	currentArena = PlayArena;
	Position = new Vector2( StartPosition );
	Direction = StartDirection;
	Speed = StartSpeed;
	Radius = 1;
}

Projectile::~Projectile()
{
	delete Position;
	delete Direction;
}

void Projectile::Update()
{
	bool moveToTarget = true;

	Vector2* target = Direction->ToVector();
	target->Multiply( Speed );
	target->Add( Position );

	currentArena->ProcessProjectileCollisions( this, target, &moveToTarget );
	if( moveToTarget )
	{
		Position->X = target->X;
		Position->Y = target->Y;
	}
	delete target;
}

void Projectile::Render()
{
	al_draw_filled_ellipse( Position->X, Position->Y, Radius, Radius, al_map_rgb( 128, 128, 128 ) );
}

void Projectile::OnCollision( Player* WithPlayer )
{
}

void Projectile::OnCollisionPlayersWall( Player* WithPlayer )
{
}
