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

void Texture::setup_texobj(std::string pathname)
{
    GLuint width{ 256 }, height{ 256 }, bytes_per_texel{ 4 };
    char* ptr_texels = nullptr;
    std::ifstream is(pathname, std::ifstream::binary);
    if (is)
    {
        int length = width * height * bytes_per_texel;
        ptr_texels = new char[length];
        is.read(ptr_texels, length);
        is.close();
    }
    glCreateTextures(GL_TEXTURE_2D, 1, &tex_obj);
    // allocate GPU storage for texture image data loaded from file
    glTextureStorage2D(tex_obj, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(tex_obj, 0, 0, 0, width, height,
        GL_RGBA, GL_UNSIGNED_BYTE, ptr_texels);

    // client memory not required since image is buffered in GPU memory
    delete[] ptr_texels;
    // nothing more to do - return handle to texture object
}

GLuint Texture::Get_texture()
{
    return tex_obj;
}
