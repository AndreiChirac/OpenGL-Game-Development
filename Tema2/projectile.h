#include "lab_m1/Tema2/util.h"

class Projectile
{
public:
	Projectile();
	//Projectile(float x_spawn, float z_spawn, int ttl, glm::vec3 forward);
	Projectile(float x_spawn, float y_spawn, float z_spawn, int ttl, glm::vec3 forward);
	~Projectile();

	Point3D spawn;
	Point3D curr_pos;
	int ttl;
	std::string projectile = "projectile";
	float speed = 2;
	float radius = 0.1;
	glm::vec3 forward;
private:
	
};
