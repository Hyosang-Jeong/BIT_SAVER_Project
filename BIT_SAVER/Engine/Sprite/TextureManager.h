/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.h
Project: BIT_SAVER
Author: Hyosang Jung
-----------------------------------------------------------------*/
#pragma once
#include <filesystem>
#include <map>
#include<GL/glew.h>
#include<glm/glm.hpp>
class Texture;
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
        Texture* Load(const char* filePath);
        void Unload();
    private:
        
        std::map<std::string, Texture* > images;
    };
