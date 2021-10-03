/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: Wrapper class for doodle::Image
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/

#include "Texture.h"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Engine.h"
using Image = unsigned char*;


//Texture::Texture(doodle::Image&& doodleImage) {
//    image = std::move(doodleImage);
//}

//void CS230::Texture::Draw(math::TransformMatrix displayMatrix) {
//    doodle::push_settings();
//    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
//    doodle::draw_image(image, 0, 0);
//    doodle::pop_settings();
//}
//
//void CS230::Texture::Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize) {
//    doodle::push_settings();
//    doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
//    doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
//    doodle::pop_settings();
//}
//
//math::ivec2 CS230::Texture::GetSize() { return { image.GetWidth(), image.GetHeight() }; }
//
//unsigned int CS230::Texture::GetPixel(math::ivec2 texel) {
//    int index = texel.y * GetSize().x + texel.x;
//    return (static_cast<int>(image[index].red)) << 24 |
//        (static_cast<int>(image[index].green)) << 16 |
//        (static_cast<int>(image[index].blue)) << 8 |
//        (static_cast<int>(image[index].alpha));
//}

void Texture::setup_texobj(const char* pathname)
{
    int width{ 0 }, height{ 0 }, col_chanel{ 0 };
    Image image = stbi_load(pathname, &width, &height, &col_chanel, 4);

    stbi_set_flip_vertically_on_load(true);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (image)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &tex_obj);
        // allocate GPU storage for texture image data loaded from file
        glTextureStorage2D(tex_obj, 1, GL_RGBA8, width, height);
        glTextureSubImage2D(tex_obj, 0, 0, 0, width, height,
            GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        Engine::GetLogger().LogDebug("Failed to load image");
        std::exit(EXIT_FAILURE);
    }
    stbi_image_free(image);
}

GLuint Texture::Get_texture()
{
    return tex_obj;
}
