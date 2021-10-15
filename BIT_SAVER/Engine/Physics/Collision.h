#include <glm/glm.hpp>

struct AABB
{
	glm::vec2 min{ 0};
	glm::vec2 max{ 0 };
};

class Collision
{
public:
	Collision() = default;
	Collision(glm::vec2 scale);

	const AABB& GetAABB() const;
	void UpdateCollision(glm::vec2 pos);
private:
	AABB collision_box;
	glm::vec2 texture_scale;
};