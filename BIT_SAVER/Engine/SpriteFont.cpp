/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpriteFont.cpp
Project: CS230
Author: Kevin Wright, Hyosang Jung
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#include "doodle/drawing.hpp"	//set_tint_color
#include "Engine.h"
#include "SpriteFont.h"
#include "TransformMatrix.h"

CS230::SpriteFont::SpriteFont(const std::filesystem::path& fileName) : texture(fileName) {
	unsigned int white = 0xFFFFFFFF;
	unsigned int color = texture.GetPixel({ 0, 0 });
	if (color != white) {
		Engine::GetLogger().LogError("Sprite font " + fileName.string() + " not setup correctly");
		return;
	}
	SetupCharRects();
}

void CS230::SpriteFont::SetupCharRects() {
	unsigned int testColor = texture.GetPixel({ 0, 0 });
	unsigned int nextColor = testColor;

	int height = texture.GetSize().y;

	int xPos = 1;
	for (int index = 0; index < numOfChars; index++) {
		nextColor = testColor;
		while(nextColor == testColor)
		{
			xPos++;
			nextColor = texture.GetPixel({ xPos,0 });
		}
		testColor = nextColor;
		charTexels[index].point2 = {xPos-1,1};
		if (index > 0)
		{
			charTexels[index].point1 = { charTexels[index-1].Right()+1 , height};
		}
		else if(index==0)
		{
			charTexels[index].point1 = { 0,height };
		}
	}
}

math::irect2& CS230::SpriteFont::GetCharRect(char c) {
	if (c >= ' ' && c <= 'z') {
		return charTexels[c - ' '];
	}
	else {
		Engine::GetLogger().LogError("character '" + std::to_string(c) + "' not found in spriteFont");
		return charTexels[0];
	}
}

math::ivec2 CS230::SpriteFont::MeasureText(std::string text) {
	math::ivec2 size = { 0,0 };
	for (char c : text)
	{
		size.x += GetCharRect(c).Size().x;
		if (GetCharRect(c).Size().y > size.y)
		{
			size.y = GetCharRect(c).Size().y;
		}
	}
	return size;
}

CS230::Texture CS230::SpriteFont::DrawTextToTexture(std::string text, unsigned int color, bool drawShadow) {

	math::ivec2 textSize = MeasureText(text);
	if (drawShadow == true) {
		textSize += math::ivec2{ 3, 3 };
	}
	
	doodle::begin_drawing_to_image(textSize.x, textSize.y, true);

	math::TransformMatrix matrix;
	if (drawShadow == true) {
	
		doodle::set_tint_color(doodle::HexColor(0x000000FF));
		for (char c : text) {
			DrawChar(matrix, c);
		}
		matrix = math::TranslateMatrix(math::ivec2{ 3,3 });
	}


	doodle::set_tint_color(doodle::HexColor(color));
	for (char c : text) {
		DrawChar(matrix, c);
	}

	doodle::set_tint_color(doodle::HexColor(0xFFFFFFFF));
	return CS230::Texture(doodle::end_drawing_to_image());
}

void CS230::SpriteFont::DrawChar(math::TransformMatrix& matrix, char c) {
	math::irect2& displayRect = GetCharRect(c);
	math::ivec2 topLeftTexel = { displayRect.Left(), displayRect.Bottom() };
	if (c != ' ') {
		texture.Draw(matrix, topLeftTexel, displayRect.Size());
	}
	matrix *= math::TranslateMatrix(math::ivec2{ displayRect.Size().x, 0 });
}

