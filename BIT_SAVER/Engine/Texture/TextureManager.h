#pragma once
#include <filesystem>
#include <map>
#include<GL/glew.h>
#include<glm/glm.hpp>

    struct texture_info
    {
        unsigned char* img;
        int width;
        int height;
        int col_chanel;
        GLuint tex_objhdl;
    };
    class TextureManager 
    {
    public:
        GLuint Load(const char* filePath, glm::vec2& texture_size);

    private:
        std::map<const char*, GLuint > images;
    };
