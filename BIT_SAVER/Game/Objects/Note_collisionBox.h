/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Note_CollisionBox.h
Project: BIT_SAVER
Author: 
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\Input\Input.h" //input key
#include "..\Engine\GameObject\GameObject.h" // GameObject inheritance
#include"GameObjectType.h"

class Note_box : public GameObject
{
public:
    Note_box(glm::vec2 startPos);
    void Update(double dt) override;
    void ResolveCollision(GameObject* test_obj) override;
    const bool GetDestroyed() const;
    GameObjectType GetObjectType() override
    {
        return GameObjectType::Note_collisionBox;
    }
    glm::vec2 Getposition();
    void set_attack_flag(bool attack_flag, GLfloat ypos );
    void Draw(glm::mat3 camera_matrix) override;
private:
    Texture Hit_tex;
    Texture Miss_tex;
    bool Hit[2] = { false };   //Hit check flag
    glm::vec2 Hit_pos[2] = { {-20,-20},{-20,-20} }; //Track1 and Track2  // intial pos -20,-20 => not to draw initail state
    bool attack_pressed{false};
    bool is_destroyed{ true };
    GLfloat attack_ypos{ 0 };
};