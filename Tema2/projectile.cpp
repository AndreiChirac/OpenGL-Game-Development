#include "lab_m1/Tema2/projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(float x_spawn, float y_spawn, float z_spawn, int ttl, glm::vec3 forward)
{
	this->spawn.x = x_spawn;
	this->spawn.y = y_spawn;
	this->spawn.z = z_spawn;
	this->curr_pos.x = x_spawn;
	this->curr_pos.y = y_spawn;
	this->curr_pos.z = z_spawn;
	this->ttl = ttl;
	this->forward = forward;
}

Projectile::~Projectile()
{
}