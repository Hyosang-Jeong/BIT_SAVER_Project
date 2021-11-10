/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project:
Author:
Creation date:
-----------------------------------------------------------------*/
#include"Sprite.h"
#include"../Engine.h" // get logger
#include"Texture.h"  //texture
#include"Animation.h" //new animation
#include"../Engine/GameObject/GameObject.h" //GameObject*


#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
std::map<GLchar, Character> GLText::Characters;
unsigned int GLText::VAO;
unsigned int GLText::VBO;
std::map<std::string, GLSLShader>::iterator GLText::shd_ref;

//#include"Collision.h"
Sprite::Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object) 
{
	Load(spriteInfoFile, object);
}

Sprite::~Sprite() {
	for (Animation* anim : animations) {
		delete anim;
	}
	animations.clear();
}

void Sprite::Load(const std::filesystem::path& spriteInfoFile,[[maybe_unused]] GameObject* object)
{

	frameTexel.clear();

	if (spriteInfoFile.extension() == ".png") 
	{
		textureptr  = Engine::GetTextureManager().Load(spriteInfoFile.string().c_str());
		model.init({ 1,1 });
	}
	else if (spriteInfoFile.extension() == ".spt")
	{
		std::ifstream inFile(spriteInfoFile);

		if (inFile.is_open() == false) {
			throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
		}

		std::string text;
		inFile >> text;
		textureptr = Engine::GetTextureManager().Load(text.c_str());
		inFile >> text;
		while (inFile.eof() == false)
		{
			if (text == "Anim")
			{
				inFile >> text;
				animations.push_back(new Animation(text));
			}
			else if (text == "FrameSize") 
			{
				inFile >> frameSize.x;
				inFile >> frameSize.y;
			}
			else if (text == "NumFrames") 
			{
				int numFrames;
				inFile >> numFrames;
				float ndc_frame_size = 1.0f / static_cast<float>(numFrames);

				ndc_frameSize.x = ndc_frame_size;
				ndc_frameSize.y = 1.0f;
				object->AddGOComponent(new Collision(ndc_frameSize));

				model.init({ ndc_frame_size,1 });
				for (int i = 0; i < numFrames; i++)
				{
					frameTexel.push_back({ ndc_frame_size * i, 0 });
				}
			}
			else
			{
				Engine::GetLogger().LogError("Unknown spt command " + text);
			}
			inFile >> text;
		}
	}

	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
	if (animations.empty() == true)
	{
		animations.push_back(new Animation());
	}
	
}

glm::vec2 Sprite::GetFrameSize() const
{
	return frameSize;
}

glm::vec2 Sprite::GetFrameTexel(int frameNum) const
{
	if (frameNum > frameTexel.size() - 1 || frameNum < 0)
	{
		Engine::GetLogger().LogError("invalid index!");
	}
	return frameTexel[frameNum];
}


void Sprite::Draw(glm::mat3 displayMatrix, std::string shdr_name)
{
	textureptr->Draw(displayMatrix,  model, shdr_name);
}

bool Sprite::IsAnimationDone()
{
	return animations[currAnim]->IsAnimationDone();
}

int Sprite::GetCurrentAnim()
{
	return currAnim;
}

void Sprite::Update(double dt)
{
	if (is_playing == true)
	{
		model.update(GetFrameTexel(animations[currAnim]->GetDisplayFrame()), ndc_frameSize);
	}
	animations[currAnim]->Update(dt);
}
void Sprite::PlayAnimation(int anim)
{
	if (anim > animations.size() - 1 || anim < 0)
	{
		Engine::GetLogger().LogError("invalid index");
		currAnim = 0;
	}
	animations[anim]->ResetAnimation();
	currAnim = anim;
	is_playing = true;
}


//GLText::GLText(std::string file)
//{
//	shd_ref = Engine::GetGLShader().find("Text");
//	if (shd_ref == Engine::GetGLShader().end())
//	{
//		Engine::GetLogger().LogError("Shader not found!");
//		std::exit(EXIT_FAILURE);
//	}
//	filepath = file;
//	init();
//}
//void GLText::init()
//{
//	shd_ref->second.Use();
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Engine::GetWindow().GetSize().x), 0.0f, static_cast<float>(Engine::GetWindow().GetSize().y));
//
//	GLint uniform_var_loc10 =
//		glGetUniformLocation(shd_ref->second.GetHandle(), "projection");
//	if (uniform_var_loc10 >= 0) {
//		glUniformMatrix4fv(uniform_var_loc10, 1, GL_FALSE, glm::value_ptr(projection));
//	}
//	else {
//		std::cout << "Uniform variable doesn't exist!!!\n";
//		//std::exit(EXIT_FAILURE);
//	}
//	//glUniformMatrix4fv(glGetUniformLocation(shd_ref->second.GetHandle(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//	GLint uniform_var_loc1 =
//		glGetUniformLocation(shd_ref->second.GetHandle(), "text");
//	if (uniform_var_loc1 >= 0) {
//		glUniform1i(uniform_var_loc1, 0);
//	}
//	else {
//		std::cout << "Uniform variable doesn't exist!!!\n";
//		//std::exit(EXIT_FAILURE);
//	}
//	shd_ref->second.UnUse();
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	FT_Library ft;
//	// All functions return a value different than 0 whenever an error occurred
//	if (FT_Init_FreeType(&ft))
//	{
//		throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
//	}
//
//	// find path to font
//	//std::string font_name = "../font/MochiyPopOne-Regular.ttf";
//	if (filepath.empty())
//	{
//		throw std::runtime_error("ERROR::FREETYPE: Failed to load font_name");
//	}
//
//	FT_Face face;
//
//	if (FT_New_Face(ft, filepath.c_str(), 0, &face)) {
//		throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
//	}
//
//	else {
//		// set size to load glyphs as
//		FT_Set_Pixel_Sizes(face, 0, 48);
//
//		// disable byte-alignment restriction
//		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//		// load first 128 characters of ASCII set
//		for (unsigned char c = 0; c < 128; c++)
//		{
//			// Load character glyph 
//			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//			{
//				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//				continue;
//			}
//			// generate texture
//			GLuint texobj_hdl;
//			glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
//			glTextureStorage2D(texobj_hdl, 1, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows);
//			glTextureSubImage2D(texobj_hdl, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows,
//				GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
//
//			glBindTextureUnit(6, texobj_hdl);
//			// set texture options
//			glTexParameteri(texobj_hdl, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//			glTexParameteri(texobj_hdl, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//			glTexParameteri(texobj_hdl, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			glTexParameteri(texobj_hdl, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			// now store character for later use
//			Character character;
//			character.TextureID = texobj_hdl;
//			character.Size = glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
//			character.Bearing = glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
//			character.Advance = static_cast<GLuint>(face->glyph->advance.x);//static_cast<unsigned int>(face->glyph->advance.x)
//
//			Characters.emplace(c, character);
//		}
//		
//	}
//	// destroy FreeType once we're finished
//	FT_Done_Face(face);
//	FT_Done_FreeType(ft);
//}
//
//void GLText::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
//{
//	shd_ref->second.Use();
//
//	GLint uniform_var_loc10 =
//		glGetUniformLocation(shd_ref->second.GetHandle(), "textColor");
//	if (uniform_var_loc10 >= 0) {
//		glUniform3f(uniform_var_loc10, color.x, color.y, color.z);
//	}
//	else {
//		std::cout << "Uniform variable doesn't exist!!!\n";
//		//std::exit(EXIT_FAILURE);
//	}
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindVertexArray(VAO);
//
//	// iterate through all characters
//	std::string::const_iterator c;
//	for (c = text.begin(); c != text.end(); c++)
//	{
//		Character ch = Characters[*c];
//
//		float xpos = x + ch.Bearing.x * scale;
//		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//		float w = ch.Size.x * scale;
//		float h = ch.Size.y * scale;
//		// update VBO for each character
//		float vertices[6][4] = {
//			{ xpos,     ypos + h,   0.0f, 0.0f },
//			{ xpos,     ypos,       0.0f, 1.0f },
//			{ xpos + w, ypos,       1.0f, 1.0f },
//
//			{ xpos,     ypos + h,   0.0f, 0.0f },
//			{ xpos + w, ypos,       1.0f, 1.0f },
//			{ xpos + w, ypos + h,   1.0f, 0.0f }
//		};
//		// render glyph texture over quad
//		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//		// update content of VBO memory
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		// render quad
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
//	}
//	glBindVertexArray(0);
//	shd_ref->second.UnUse();
//}

GLText::GLText()
{
		shd_ref = Engine::GetGLShader().find("Text");
		if (shd_ref == Engine::GetGLShader().end())
		{
			Engine::GetLogger().LogError("Shader not found!");
			std::exit(EXIT_FAILURE);
		}

		shd_ref->second.Use();

	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(Engine::GetWindow().GetSize().x), static_cast<float>(Engine::GetWindow().GetSize().y), 0.0f);

	GLint uniform_var_loc1 =
		glGetUniformLocation(shd_ref->second.GetHandle(), "projection");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix4fv(uniform_var_loc1, 1, GL_FALSE, &proj[0].x);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}

	GLint uniform_var_loc2 =
		glGetUniformLocation(shd_ref->second.GetHandle(), "text");
	if (uniform_var_loc2 >= 0) {
		glUniform1i(uniform_var_loc2, 0);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}

	shd_ref->second.UnUse();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GLText::Load(std::string font, unsigned int fontSize)
{
	this->Characters.clear();

	FT_Library ft_lib;
	
	if (FT_Init_FreeType(&ft_lib)) {
		Engine::GetLogger().LogError("Can't init Font");
	}

	FT_Face ft_face;

	if (FT_New_Face(ft_lib, font.c_str(), 0, &ft_face)) {
		Engine::GetLogger().LogError("Can't Load Font");
	}

	FT_Set_Pixel_Sizes(ft_face, 0, fontSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(ft_face, c, FT_LOAD_RENDER))
		{
			Engine::GetLogger().LogError("Can't Load GLyph");
			continue;
		}

		//GLuint texobj_hdl;
		//glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
		//glTextureStorage2D(texobj_hdl, 1, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		//glTextureSubImage2D(texobj_hdl, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows,
		//	GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		GLuint texobj_hdl;
		glGenTextures(1, &texobj_hdl);
		glBindTexture(GL_TEXTURE_2D, texobj_hdl);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			ft_face->glyph->bitmap.width,
			ft_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			ft_face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texobj_hdl,
			glm::ivec2(ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows),
			glm::ivec2(ft_face->glyph->bitmap_left, ft_face->glyph->bitmap_top),
			static_cast<unsigned int>(ft_face->glyph->advance.x)
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(ft_face);
	FT_Done_FreeType(ft_lib);
}

void GLText::Draw(std::string text, float x, float y, float scale, glm::vec3 color)
{
	shd_ref->second.Use();

	//GLuint texColor_location = glGetUniformLocation(shd_ref->second.GetHandle(), "textColor");
	//glm::vec3 col = glm::vec3(color);
	//glUniform3fv(texColor_location, 1, &color.x);
	//this->shd_ref->second.SetUniform("textColor", color);

	GLint uniform_var_loc1 =
		glGetUniformLocation(shd_ref->second.GetHandle(), "textColor");
	if (uniform_var_loc1 >= 0) {
		glUniform3fv(uniform_var_loc1, 1, &color.x);
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!\n";
		std::exit(EXIT_FAILURE);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character character = Characters[*c];

		float xpos = x + character.Bearing.x * scale;
		float ypos = y + (this->Characters['H'].Bearing.y - character.Bearing.y) * scale;

		float w = character.Size.x * scale;
		float h = character.Size.y * scale;

		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 0.0f },

			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, character.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (character.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	shd_ref->second.UnUse();
}