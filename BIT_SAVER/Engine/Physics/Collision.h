#include "..\Component.h"
#include"../GLModel/GLModel.h"


struct AABB
{
	glm::vec2 min{ 0};
	glm::vec2 max{ 0 };
};

class Render {
public:
	Render(void);
	//~Render(void);
	void SetColor(glm::vec3 c);
	void DrawLine(glm::vec2 P, glm::vec2 Q);
private:
	GLint program;
	GLint ucolor, aposition;
};


class Collision : public Component
{
public:
	Collision() = default;
	Collision(glm::vec2 size);
	//Collision(glm::vec2 min, glm::vec2 max);
	const AABB& GetAABB() const;
	void UpdateCollision(glm::vec2 pos,glm::vec2 scale);
	void Draw();
private:
	AABB collision_box;
	glm::vec2 box_size;
	Render render;
};

