/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Project: BIT_SAVER
Author: Jaewoo.choi, Hyun Kang , Hyosang Jung 

-----------------------------------------------------------------*/
#pragma once
#include<Windows.h>
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
    VOLUME_Option,
    KEY_Option,
    Sound_Bigball,
    Sound_Smallball,
    MOUSE_CURSOR,
    OFFSET_X,
    Background_1,
    Background_1_1,
    Background_1_2,
    Background_1_3,
    Background_1_4,
    Background_1_5,
    Background_1_6,
    Background_1_7,
    Background_1_8,
    Background_1_9,
    Background_1_10,

    Parallax1_5, 
    Parallax1_4,
    Parallax1_3,
    Parallax1_2,
    Parallax1_1,

    Parallax2_8,
    Parallax2_7,
    Parallax2_6,
    Parallax2_5,
    Parallax2_4,
    Parallax2_3,
    Parallax2_2,
    Parallax2_1

    //Total
};

static const char* texture_path[] = {
    "../images/DigiPen_BLACK_1024px.png",
    "../images/LOGO.png",

    "../images/Pause_screen.png",
    "../images/volume_option.png",
    "../images/main_option_sound_bar.png",
    "../images/sound_bigball.png",
    "../images/sound_smallball.png",
    "../images/Cursor.png",
    "../images/offset_x.png",

    "../images/background1.png",

    "../images/background_1_1.png",
    "../images/background_1_2.png",
    "../images/background_1_3.png",
    "../images/background_1_4.png",
    "../images/background_1_5.png",
    "../images/background_1_6.png",
    "../images/background_1_7.png",
    "../images/background_1_8.png",
    "../images/background_1_9.png",
    "../images/background_1_10.png",

    "../images/parallax1-5.png",
    "../images/parallax1-4.png",
    "../images/parallax1-3.png",
    "../images/parallax1-2.png",
    "../images/parallax1-1.png",

    "../images/BACK8.png",
    "../images/BACK7.png",
    "../images/BACK6.png",
    "../images/BACK5.png",
    "../images/BACK4.png",
    "../images/BACK3.png",
    "../images/BACK2.png",
    "../images/BACK1.png"

};


class Texture
{
public:
    Texture() = default;
    Texture(GLuint obj, glm::vec2 size) : tex_obj(obj), texture_size(size) {};

    void Draw(glm::mat3 displayMatrix);

    void Draw(glm::mat3 displayMatrix, glm::vec2 texel_pos, glm::vec2 texel_size);

    void Draw(glm::vec2 pos, glm::vec2 scale = { 1,1 }, glm::vec2 rotate = { 0,0 });

    void Draw(float alpha, glm::mat3 camera , glm::vec2 pos, glm::vec2 scale = { 1,1 }, glm::vec2 rotate = { 0,0 }, glm::vec2 texel_pos = { 0,0 }, glm::vec2 texel_size = { 1,1 });
    glm::vec2 GetSize();

    GLuint tex_obj{ 0 };
    glm::vec2 texture_size{ 0,0 };

    GLModel model;
};
