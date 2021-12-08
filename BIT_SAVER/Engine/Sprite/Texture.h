/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Purpose: Wrapper class for doodle::Image
Project: BIT_SAVER
Author: 
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include<GL/glew.h>
#include<string>
#include<glm/glm.hpp>
#include<map>
#include"../GLModel/GLModel.h"

enum Texture_Path
{
    DigipenLogo_Splash,
    Gamelogo_Splash,

    Pause,
    Main_Option,
    MAIN_SOUND_BAR,
    Sound_Bigball,
    Sound_Smallball,
    MOUSE_CURSOR,
    OFFSET_X,
    Background_1,
    Parallax1_5, 
    Parallax1_4,
    Parallax1_3,
    Parallax1_2,
    Parallax1_1
    //Total
};

static const char* texture_path[] = {
    "../images/DigiPen_BLACK_1024px.png",
    "../images/LOGO.png",

    "../images/Pause_screen.png",
    "../images/main_option.png",
    "../images/main_option_sound_bar.png",
    "../images/sound_bigball.png",
    "../images/sound_smallball.png",
    "../images/Cursor.png",
    "../images/offset_x.png",

    "../images/background1.png",
    "../images/parallax1-5.png",
    "../images/parallax1-4.png",
    "../images/parallax1-3.png",
    "../images/parallax1-2.png",
    "../images/parallax1-1.png"
};


class Texture
{
public:
    Texture() = default;
    Texture(GLuint obj, glm::vec2 size) : tex_obj(obj), texture_size(size) {};

    void Draw(glm::mat3 displayMatrix);
    void Draw(glm::mat3 displayMatrix, glm::vec2 texel_pos, glm::vec2 texel_size);
    void Draw(glm::vec2 pos, glm::vec2 scale = { 1,1 }, glm::vec2 rotate = { 0,0 });
    glm::vec2 GetSize();

    GLuint tex_obj{ 0 };
    glm::vec2 texture_size{ 0,0 };

    GLModel model;
};
