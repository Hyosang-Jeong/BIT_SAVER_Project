#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include<string>
struct GLModel
{
	struct Vertex
	{
		glm::vec2 position;
		glm::vec3 color;
		glm::vec2 tex_coord;
	};
	GLenum primitive_type;
	GLuint primitive_cnt;
	GLuint vaoid;
	GLuint draw_cnt;
	std::string name;

	void setup_vao();
	void setup_shdrpgm();
	void set_name(std::string model_name);
	void init(); // read mesh data from file ...
};